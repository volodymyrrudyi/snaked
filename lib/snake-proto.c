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

typedef struct _BasePacket BasePacket;

#define CLEAR_PACKET(x) memset(x, 0, sizeof(*x))

#define NEGOTIATION_PACKET_GET_SIZE(x) \
	sizeof(NegotiationPacket) + strlen(x->host_name) + 1

#define CLIENT_INFO_PACKET_GET_SIZE(x) \
	sizeof(ClientInfoPacket) + strlen(x->nickname)  + 1

void
base_packet_fill(BasePacket *packet, uint32_t type, 
	uint64_t packet_size);
	
char*
base_packet_read(int fd, struct sockaddr_in *sender_addr);

void
base_packet_write(int fd, BasePacket *packet, char *data,
struct sockaddr_in *receiver_addr);


/* Base data packet */
struct _BasePacket
{
	uint32_t magic; 	/* Magic number to identify Snaked packets */
	uint32_t version;	/* Version of protocol */
	uint32_t type; 		/* Packet type */
	uint64_t crc; 		/* Control summ of packet including data */
	uint64_t data_size; /* Data size in bytes */
};

void
base_packet_fill(BasePacket *packet, uint32_t type, 
	uint64_t packet_size)
{
	packet->magic 		= SNAKE_MAGIC;
	packet->version 	= SNAKE_VERSION;
	packet->type 		= type;
	packet->crc 		= 0;
	packet->data_size 	= packet_size;

}

char*
base_packet_read(int fd, struct sockaddr_in *sender_addr)
{
	char *data;
	uint32_t addr_len;
	BasePacket *packet;
	char *real_data;
	
	data = (char*)malloc(SNAKE_PACKET_MAX);
	if (sender_addr == NULL)
	{
		read(fd,data, SNAKE_PACKET_MAX);
	} else
	{
		recvfrom(fd, data, SNAKE_PACKET_MAX, 0, 
			(struct sockaddr*)sender_addr, &addr_len);
	}
	
	packet = (BasePacket*)data;
	real_data = (char*)malloc(packet->data_size);
	memcpy(real_data, data + sizeof(BasePacket), packet->data_size);
	free(data);
	
	return real_data;
}

void
base_packet_write(int fd, BasePacket *packet, char *data,
struct sockaddr_in *receiver_addr)
{
	uint32_t data_amount = sizeof(BasePacket) + packet->data_size;
	char *data_to_send = malloc(data_amount);
	memcpy(data_to_send, packet, sizeof(BasePacket));
	memcpy(data_to_send + sizeof(BasePacket),data, packet->data_size);
	
	if (receiver_addr == NULL)
	{
		write(fd, data_to_send, data_amount);
	} else
	{
		sendto(fd, data_to_send, data_amount, 0, 
			(struct sockaddr*)receiver_addr, sizeof(struct sockaddr_in));
	}
	
	free(data_to_send);
}

NegotiationPacket*
negotiation_packet_create(uint32_t port, const char *host_name)
{
	NegotiationPacket *packet = 
		(NegotiationPacket*)malloc(sizeof(NegotiationPacket));
	
	packet->host_name = (char*)malloc(strlen(host_name) + 1);
	strcpy(packet->host_name, host_name);
	packet->port = port;
		
	return packet;	
}

NegotiationPacket*
negotiation_packet_read(int fd, struct sockaddr_in *sender_addr)
{
	char *data;
	NegotiationPacket* received_packet;
	char *host_name;
	
	data = base_packet_read(fd, sender_addr);
	received_packet = (NegotiationPacket*)data;
	host_name = data + sizeof(NegotiationPacket);
	
	NegotiationPacket *result_packet = 
		negotiation_packet_create(received_packet->port, host_name);
	
	free(data);
	
	return result_packet;
}

void
negotiation_packet_write(int fd, NegotiationPacket* packet, 
	struct sockaddr_in *receiver_addr)
{
	BasePacket base_packet;
	uint32_t packet_size;
	
	packet_size = NEGOTIATION_PACKET_GET_SIZE(packet);
	
	base_packet_fill(&base_packet, PACKET_NEGOTIATION, 
		packet_size);
		
	char *data = (char*)malloc(packet_size);
	memcpy(data, packet, sizeof(NegotiationPacket));
	strcpy(data + sizeof(NegotiationPacket), packet->host_name);
	
	base_packet_write(fd, &base_packet, data, receiver_addr);
	free(data);
}

void
negotiation_packet_destroy(NegotiationPacket *packet)
{
	free(packet->host_name);
	free(packet);
}

ClientInfoPacket*
client_info_packet_create(uint32_t color, const char *nickname)
{
	ClientInfoPacket *packet = 
		(ClientInfoPacket*)malloc(sizeof(ClientInfoPacket));
	packet->nickname = (char*)malloc(strlen(nickname) + 1);
	strcpy(packet->nickname, nickname);
	packet->color = color;	
	
	return packet;
}

ClientInfoPacket*
client_info_packet_read(int fd, struct sockaddr_in *sender_addr)
{
	char *data;
	ClientInfoPacket* received_packet;
	char *nickname;
	
	data = base_packet_read(fd, sender_addr);
	received_packet = (ClientInfoPacket*)data;
	nickname = data + sizeof(ClientInfoPacket);
	
	ClientInfoPacket *result_packet = 
		client_info_packet_create(received_packet->color, nickname);
	
	free(data);
	return result_packet;
}

void
client_info_packet_write(int fd, ClientInfoPacket* packet, 
	struct sockaddr_in *receiver_addr)
{
	BasePacket base_packet;
	uint32_t packet_size;
	
	packet_size = CLIENT_INFO_PACKET_GET_SIZE(packet);
	
	base_packet_fill(&base_packet, PACKET_CLIENT_INFO, 
		packet_size);
		
	char *data = (char*)malloc(packet_size);
	memcpy(data, packet, sizeof(ClientInfoPacket));
	strcpy(data + sizeof(ClientInfoPacket), packet->nickname);
	
	base_packet_write(fd, &base_packet, data, receiver_addr);
	free(data);
}

void
client_info_packet_destroy(ClientInfoPacket *packet)
{
	free(packet);
}
