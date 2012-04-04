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

void setnblock(int fd);
void terminate_handler(int sig);

void accept_cb(int fd, short ev, void *arg);
void buffer_write_cb(struct bufferevent *event, void *arg);
void buffer_read_cb(struct bufferevent *event, void *arg);
void buffer_error_cb(struct bufferevent *event, short what,
	void *arg);
	
struct ClientData
{
	struct bufferevent *buffer_event;
	int socket;
};

int sock; 
int server_main(const char *host, int port, const char *server_name)
{
	int reuse = 1;
    struct sockaddr_in server_addr;
    struct event accept_event;
    
	SNAKE_DEBUG("Server launched");
	event_init();

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        SNAKE_ERROR("Failed to open socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server_addr,
		sizeof(server_addr)) < 0)
    {
        SNAKE_ERROR("Can't bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(sock, 5) < 0)
    {
      SNAKE_ERROR("Can't listen");
      return 1;
    }

	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse,
		sizeof(reuse));

	setnblock(sock);
	
	event_set(&accept_event, sock, EV_READ|EV_PERSIST, accept_cb,
            NULL);
	event_add(&accept_event, NULL);
	event_dispatch();

    SNAKE_DEBUG("Entering event loop. Waiting for clients on port %d", 
		port);
	
    close(sock);
    return 0;
}

void accept_cb(int fd, short ev, void *arg)
{
	int client_fd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct ClientData *client;
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

	bufferevent_enable(client->buffer_event, EV_READ);
}

void buffer_read_cb(struct bufferevent *event, void *arg)
{
}

void buffer_write_cb(struct bufferevent *event, void *arg)
{
}

void buffer_error_cb(struct bufferevent *event, short what,
	void *arg)
{

}

void terminate_handler(int sig)
{
	close(sock);
	exit(EXIT_SUCCESS);
}

void setnblock(int fd)
{
	int flags;
	flags = fcntl(fd, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

