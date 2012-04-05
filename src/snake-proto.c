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

BasePacket *base_packet_create(const char *data, uint64_t data_size)
{
	BasePacket *packet = (BasePacket*)
		malloc(sizeof(BasePacket) + data_size);
		
	memcpy(packet + sizeof(BasePacket), data, data_size);
	
	return packet;
}

BOOL base_packet_parse(BasePacket *packet, char *buffer,
	uint64_t *buffer_size)
{
	BOOL res = FALSE;
	
	return res;
}

NegotiationPacket*
negotiation_packet_create(uint32_t port, uint32_t host_name_length,
	char *host_name)
{
	return NULL;
}

BOOL 
negotiation_packet_parse(NegotiationPacket* packet, uint32_t *port,
	uint32_t *host_name_length, char *host_name)
{
	return FALSE;
}
