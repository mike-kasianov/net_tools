#include "ip_v4_packet.h"
#include <string.h>
#include <netinet/in.h>

void IpV4Packet_build(IpV4Packet *packet, void *data, uint16_t size)
{
    memset(packet, 0, sizeof(IpV4Packet));
    packet->header = (struct iphdr *) data;
    packet->payload_size = size - sizeof(struct iphdr);  // TODO use ihl
    packet->payload = (char *)data + sizeof(struct iphdr);
}

uint8_t IpV4Packet_get_version(IpV4Packet *packet)
{
    return packet->header->version;
}

uint32_t IpV4Packet_get_source_address(IpV4Packet *packet)
{
    if (packet->source_ip == 0)
    {
        packet->source_ip = ntohl(packet->header->saddr);
    }

    return packet->source_ip;
}

uint32_t IpV4Packet_get_destination_address(IpV4Packet *packet)
{
    if (packet->destination_ip == 0)
    {
        packet->destination_ip = ntohl(packet->header->daddr);
    }

    return packet->destination_ip;
}

uint8_t IpV4Packet_get_header_length(IpV4Packet *packet)
{
    return packet->header->ihl;
}

uint8_t IpV4Packet_get_type_of_service(IpV4Packet *packet)
{
    return packet->header->tos;
}