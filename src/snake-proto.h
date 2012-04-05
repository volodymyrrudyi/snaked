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

#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "snake-types.h"

#define SNAKE_MAGIC 0xDEADBEAF

/* Packet types */
#define PACKET_NEGOTIATION 	1
#define PACKET_CONTROL 		2

/* Side types */
#define SIDE_SERVER 0x01010101
#define SIDE_CLIENT 0x10101010


/* Base data packet */
struct _BasePacket
{
	uint32_t magic; 	/* Magic number to identify Snaked packets */
	uint32_t version;	/* Version of protocol */
	uint32_t type; 		/* Packet type */
	uint64_t crc; 		/* Control summ of packet including data */
	uint64_t data_size; /* Data size in bytes */
};

struct _NegotiationPacket
{
	BasePacket packet;
	uint32_t side;
	uint32_t port;
	uint32_t host_name_length;
};

BasePacket*
base_packet_create(const char *data, uint64_t data_size);

BOOL 
base_packet_parse(BasePacket *packet, char *data,
	uint64_t *data_size);

NegotiationPacket*
negotiation_packet_create(uint32_t port, uint32_t host_name_length,
	char *host_name);
	
BOOL 
negotiation_packet_parse(NegotiationPacket *packet, uint32_t *port,
	uint32_t *host_name_length, char *host_name);

#endif