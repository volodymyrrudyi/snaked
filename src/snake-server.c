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
 
void sigio_handler(int sig_no);
 
int server_main(const char *host, int port, const char *server_name)
{
	int sock;
    struct sockaddr_in server_addr;
    
	SNAKE_DEBUG("Server launched");

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

    SNAKE_DEBUG("Entering event loop. Waiting for clients on port %d", 
		port);
		
    close(sock);
    
    return 0;
}

void sigio_handler(int sig_no)
{
    SNAKE_DEBUG("Hi there! Accepted data from client");
}

