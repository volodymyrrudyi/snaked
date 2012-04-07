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
#ifndef __SNAKE_PROTO_H
#define __SNAKE_PROTO_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "snake-log.h"

#define SNAKE_MAGIC 0xDEADBEAF
#define SNAKE_VERSION 1

/* Packet types */
#define PACKET_NEGOTIATION 	1
#define PACKET_CONTROL 		2
#define PACKET_CLIENT_INFO 	4

/* Side types */
#define SIDE_SERVER 0x01010101
#define SIDE_CLIENT 0x10101010

#define BOOL uint32_t 
#define TRUE 1
#define FALSE 0

#define SNAKE_HOST_MAX 256
#define SNAKE_PACKET_MAX 1024

typedef struct _NegotiationPacket NegotiationPacket;
typedef struct _ClientInfoPacket ClientInfoPacket;

struct _NegotiationPacket
{
	uint32_t port;
	char *host_name;
};

struct _ClientInfoPacket
{
	uint32_t color;
	char *nickname;
};

NegotiationPacket*
negotiation_packet_create(uint32_t port, const char *host_name);

NegotiationPacket*
negotiation_packet_read(int fd, struct sockaddr_in *sender_addr);

void
negotiation_packet_write(int fd, NegotiationPacket* packet, 
	struct sockaddr_in *receiver_addr);

void
negotiation_packet_destroy(NegotiationPacket *packet);

ClientInfoPacket*
client_info_packet_create(uint32_t color, const char *nickname);

ClientInfoPacket*
client_info_packet_read(int fd, struct sockaddr_in *sender_addr);

void
client_info_packet_write(int fd, ClientInfoPacket* packet, 
	struct sockaddr_in *receiver_addr);

void
client_info_packet_destroy(ClientInfoPacket *packet);

#endif
