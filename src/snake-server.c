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
terminate_handler(int sig);

static void
read_handler(int fd, short what, void *arg);

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void spawn_game(int first_player, int second_player);

int server_sock; 
int game_sock;
struct event read_event;
struct event game_accept_event;

int server_port;
const char *server_host_name;

int 
server_main(const char *host, int port, const char *server_name)
{
	int broadcast = 1;
	int reuse = 1;
    struct sockaddr_in server_addr;
    server_port = port;
    server_host_name = host;
    event_init();
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

//	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse,
//		sizeof(reuse));
//	setsockopt(server_sock, SOL_SOCKET, SO_BROADCAST, &broadcast,
//		sizeof(broadcast));

    SNAKE_DEBUG("Entering event loop. Waiting for clients on port %d", 
		port);
		
	event_set(&read_event, server_sock, EV_READ | EV_PERSIST, 
		read_handler, &read_event);
	
	event_add(&read_event, NULL);
	event_dispatch();
	for(;;);
    close(server_sock);
    return 0;
}

static void 
terminate_handler(int sig)
{
	close(server_sock);
	exit(EXIT_SUCCESS);
}

static void
read_handler(int fd, short what,  void *arg)
{
	int client_sock; 
	struct sockaddr_in client_addr;
	int broadcast = 1;
	int reuse = 1;
	NegotiationPacket *packet;
	int buf;
	int packet_size;
	SNAKE_DEBUG("Received notice from client.");
	read(fd, &buf, sizeof(buf));
	if ((client_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        SNAKE_ERROR("Failed to open socket");
        exit(EXIT_FAILURE);
    }

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(server_port + 1);
    
    setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &reuse,
		sizeof(reuse));
	setsockopt(client_sock, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof(broadcast));
		
	packet = negotiation_packet_create(server_port + 2, 
		strlen(server_host_name) + 1, server_host_name);
	
	sendto(client_sock, packet, GET_NEGOTIATION_PACKET_SIZE(packet), 0, 
		(struct sockaddr *)&client_addr, sizeof(client_addr)); 
		
	close(client_sock);
}

void spawn_game(int first_player, int second_player)
{
	int first_client_socket = 0;
	int second_client_socket = 0;	
	Game *game = game_create(128, 128);
	char nickname_buffer[256];
	// Socket init here
	
	SNAKE_DEBUG("Requesting nickname from first client");
	write(first_client_socket, SNAKE_SERVER_GET_NICK, 
		strlen(SNAKE_SERVER_GET_NICK) + 1);
		
	SNAKE_DEBUG("Reading nickname from first client");	
	read(first_client_socket, nickname_buffer, strlen(nickname_buffer) + 1); 
	
	game_add_player(game, first_client_socket, nickname_buffer);
		
	SNAKE_DEBUG("Requesting nickname from first client");
	write(second_client_socket, 
	SNAKE_SERVER_GET_NICK, strlen(SNAKE_SERVER_GET_NICK) + 1);
		
	SNAKE_DEBUG("Reading nickname from first client");	
	read( second_client_socket, nickname_buffer, 
		strlen(nickname_buffer) + 1); 
		
	game_add_player(game, second_client_socket, nickname_buffer);
	
	pthread_t t;
	
	pthread_create(&t, NULL, game_init, (void*)game);
}
