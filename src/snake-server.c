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
game_accept_handler(int fd, short what, void *arg);

static void 
game_thread(void *param);

int game_sock;
struct event game_accept_event;

void
init_game_socket(const char *host, uint32_t port)
{
    struct sockaddr_in game_addr;
    struct hostent* host_info_ptr; 
    long host_address;
    int reuse  = 1;
    
	SNAKE_DEBUG("Creating game socket");
    if ((game_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        SNAKE_ERROR("Failed to open socket");
        exit(EXIT_FAILURE);
    }
        
    host_info_ptr = gethostbyname(host);
    memcpy(&host_address, host_info_ptr->h_addr, 
		host_info_ptr->h_length);
		
    memset(&game_addr, 0, sizeof(game_addr));
    game_addr.sin_family = AF_INET;
    game_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    game_addr.sin_port = htons(port);
   
    if (bind(game_sock, (struct sockaddr *)&game_addr,
		sizeof(game_addr)) < 0)
    {
        SNAKE_ERROR("Can't bind");
        exit(EXIT_FAILURE);
    }
    
     if (listen(game_sock, 5) < 0)
    {
        SNAKE_ERROR("Can't bind");
        exit(EXIT_FAILURE);
    }
    
    setsockopt(game_sock, SOL_SOCKET, SO_REUSEADDR, &reuse,
		sizeof(reuse));
		 
    setnonblock(game_sock);
    SNAKE_DEBUG("Waiting for game connections on %s:%d",  host, port);
    event_set(&game_accept_event, game_sock, 
		EV_READ | EV_PERSIST, game_accept_handler, 
		&game_accept_event);
		
	event_add(&game_accept_event, NULL);
}


static void
game_accept_handler(int fd, short what, void *arg)
{
	struct sockaddr_in client_addr;
	uint32_t addr_len;
	SNAKE_DEBUG("Client connected");
	accept(fd, (struct sockaddr*)&client_addr, 
		&addr_len);
		
	game_thread(NULL);
}

void game_thread(void *param)
{
	
}

