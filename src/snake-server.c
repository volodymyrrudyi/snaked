/*  
	Copyright (c) 2012 Volodymyr Rudyi <vladimir.rudoy@gmail.com>

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
 
#include "snake-server.h"

static void 
setnblock(int fd);
static void 
terminate_handler(int sig);

static void 
accept_cb(int fd, short ev, void *arg);
static void 
buffer_write_cb(struct bufferevent *event, void *arg);
static void 
buffer_read_cb(struct bufferevent *event, void *arg);
static void 
buffer_error_cb(struct bufferevent *event, short what,
	void *arg);

typedef struct _ClientData ClientData;

static void 
enqueue(ClientData *client);
static int 
dequeue();

static void
spawn_game(int first_player, int second_player);
	
struct _ClientData
{
	struct bufferevent *buffer_event;
	int socket;
};



/* Queue for storing clients that need new game */
ClientData *queue;
int queue_size;
int queue_count;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

int server_sock; 

int 
server_main(const char *host, int port, const char *server_name)
{
	int reuse = 1;
    struct sockaddr_in server_addr;
    struct event accept_event;
    
	SNAKE_DEBUG("Server launched");
	signal(SIGINT, terminate_handler);
	event_init();

    if ((server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        SNAKE_ERROR("Failed to open socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(server_sock, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0)
    {
        SNAKE_ERROR("Can't bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_sock, 5) < 0)
    {
      SNAKE_ERROR("Can't listen");
      return 1;
    }

	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse,
		sizeof(reuse));

	setnblock(server_sock);
	
	event_set(&accept_event, server_sock, EV_READ|EV_PERSIST, accept_cb,
            NULL);
	event_add(&accept_event, NULL);
	event_dispatch();

    SNAKE_DEBUG("Entering event loop. Waiting for clients on port %d", 
		port);
	
    close(server_sock);
    return 0;
}

static void 
accept_cb(int fd, short ev, void *arg)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	ClientData *client;
	SNAKE_DEBUG("Accepted connection");
	


	client_fd = accept(fd, (struct sockaddr *)&client_addr, 
		&client_len);
	if (client_fd < 0)
	{
		SNAKE_WARNING("Accept failed"); 
		return;
	}

	setnblock(client_fd);

	client = calloc(1, sizeof(*client));
	if (client == NULL)
	{
		SNAKE_ERROR("Failed to allocate memory for client data");
		return;
	}
		
	client->socket = client_fd;
	client->buffer_event = bufferevent_new(client_fd,
		buffer_read_cb,
		buffer_write_cb,
		buffer_error_cb,
		client
	);
	int second_player = -1;
	pthread_mutex_lock(&queue_mutex);
	if (queue_count == 0)
	{
		second_player =  dequeue();
	} else
	{
		enqueue(client);
	}	
	pthread_mutex_unlock(&queue_mutex);
	
	if (second_player >= 0)
	{
		spawn_game(client_fd, second_player);
	}

	bufferevent_enable(client->buffer_event, EV_READ);
}

static void 
buffer_read_cb(struct bufferevent *event, void *arg)
{
}

static void 
buffer_write_cb(struct bufferevent *event, void *arg)
{
}

static void buffer_error_cb(struct bufferevent *event, short what,
	void *arg)
{

}

static void 
terminate_handler(int sig)
{
	close(server_sock);
	exit(EXIT_SUCCESS);
}

static void 
setnblock(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

static void 
enqueue(ClientData *client)
{
	if (queue_size == queue_count)
	{
		queue_size *= 2;
		queue = realloc(queue, sizeof(ClientData) * queue_size);
	}
	
	queue_count++;
	memcpy(&queue[queue_count-1], client, sizeof(ClientData));
}

static int 
dequeue()
{
	int sock;
	if (queue_count == 0)
	{
		SNAKE_ERROR("Attempt to extract element from empty queue");
		sock = -1;
	} else
	{
		sock = queue[0].socket;
		for(int i = 0; i < queue_count - 1; i++)
		{
			queue[i] = queue[i + 1];
		}
		
		queue_count--;
	}
	
	return sock;
	
}

static void
spawn_game(int first_player, int second_player)
{
}
