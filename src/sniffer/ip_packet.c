#include "ip_packet.h"
#include <string.h>
#include <netinet/in.h>

void IpPacket_build(IpPacket *packet, void *data, uint16_t size)
{
    memset(packet, 0, sizeof(IpPacket));
    packet->header = (struct iphdr *) data;
    packet->payload_size = size - sizeof(struct iphdr);
    packet->payload = (char *)data + sizeof(struct iphdr);
}

uint8_t IpPacket_get_version(IpPacket *packet)
{
    return packet->header->version;
}

uint32_t IpPacket_get_source_ip(IpPacket *packet)
{
    if (packet->source_ip == 0)
    {
        packet->source_ip = ntohl(packet->header->saddr);
    }

    return packet->source_ip;
}

uint32_t IpPacket_get_destination_ip(IpPacket *packet)
{
    if (packet->destination_ip == 0)
    {
        packet->destination_ip = ntohl(packet->header->daddr);
    }

    return packet->destination_ip;
}