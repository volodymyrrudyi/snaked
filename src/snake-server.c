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

typedef int ClientData;


struct _DataPacket
{
	int snaked_magic;
	int port;
	char host[256];
};
typedef struct _DataPacket DataPacket;

static void 
setnblock(int fd);
static void 
terminate_handler(int sig);

static void 
client_discovered_cb(int fd);

static void 
enqueue(ClientData client);
static int 
dequeue();

static void
spawn_game(int first_player, int second_player);


/* Queue for storing clients that need new game */
ClientData *queue;
int queue_size;
int queue_count;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

int server_sock; 

int 
server_main(const char *host, int port, const char *server_name)
{
	int broadcast = 1;
	int reuse = 1;
	size_t client_addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    
	SNAKE_DEBUG("Server launched");
	signal(SIGINT, terminate_handler);

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
	setsockopt(server_sock, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof(broadcast));

    SNAKE_DEBUG("Entering event loop. Waiting for clients on port %d", 
		port);
		
	DataPacket packet;
	for(;;)
	{
		int amount  = recvfrom(server_sock, &packet, sizeof(packet),
			0, (struct sockaddr*)&client_addr, &client_addr_len);
			
		SNAKE_DEBUG("Received packet");
		if (amount < sizeof(packet))
		{
			SNAKE_ERROR("Received partial packet");
			continue;
		} else
		{
			if (packet.snaked_magic != SNAKED_MAGIC)
			{
				SNAKE_ERROR("Magic number not found");
				continue;
			} else
			{
				client_discovered_cb(0);
				packet.port = port;
				strcpy(packet.host, host);
				sendto(server_sock, &packet, sizeof(packet), 0,(struct sockaddr*) &client_addr,
					client_addr_len);
			}
		}
	}
	
    close(server_sock);
    return 0;
}

static void 
client_discovered_cb(int fd)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	SNAKE_DEBUG("Accepted connection");
	


	client_fd = accept(fd, (struct sockaddr *)&client_addr, 
		&client_len);
	if (client_fd < 0)
	{
		SNAKE_WARNING("Accept failed"); 
		return;
	}

	setnblock(client_fd);

	int second_player = -1;
	pthread_mutex_lock(&queue_mutex);
	if (queue_count == 0)
	{
		second_player =  dequeue();
	} else
	{
		enqueue(client_fd);
	}	
	pthread_mutex_unlock(&queue_mutex);
	
	if (second_player >= 0)
	{
		spawn_game(client_fd, second_player);
	}
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
enqueue(ClientData client)
{
	if (queue_size == queue_count)
	{
		queue_size *= 2;
		queue = realloc(queue, sizeof(ClientData) * queue_size);
	}
	
	queue_count++;
	queue[queue_count - 1] = client;
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
		sock = queue[0];
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
