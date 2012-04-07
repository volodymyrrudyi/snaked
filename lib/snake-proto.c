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
#include "snake-proto.h"

#define CLEAR_PACKET(x) memset(x, 0, sizeof(*x))

void
base_packet_fill(BasePacket *packet, uint32_t type, uint64_t data_size)
{
	packet->magic 		= SNAKE_MAGIC;
	packet->version 	= SNAKE_VERSION;
	packet->type 		= type;
	packet->crc 		= 0;
	packet->data_size 	= data_size;

}

BOOL base_packet_parse(BasePacket *packet, char *buffer,
	uint64_t *buffer_size)
{
	BOOL res = FALSE;
	
	return res;
}

NegotiationPacket*
negotiation_packet_create(uint32_t port, uint32_t host_name_length,
	const char *host_name)
{
	NegotiationPacket *packet = 
		(NegotiationPacket*)malloc(sizeof(NegotiationPacket));
		
	CLEAR_PACKET(packet);
	packet->host_name_length = host_name_length;
	base_packet_fill(&packet->base_packet, PACKET_NEGOTIATION,
		GET_NEGOTIATION_PACKET_SIZE(packet) - sizeof(BasePacket));

	strcpy((char*)(packet) + sizeof(NegotiationPacket), host_name);
	
	return packet;	
}

BOOL 
negotiation_packet_parse(NegotiationPacket* packet, uint32_t *port, 
	char *host_name)
{
	*port = packet->port;
	strcpy(host_name, (char*)(packet) + sizeof(NegotiationPacket));
	return TRUE;
}
