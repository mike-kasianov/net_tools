#ifndef __NET_TOOLS_IP_PACKET_H__
#define __NET_TOOLS_IP_PACKET_H__

#include <stdint.h>
#include <linux/ip.h>

typedef struct
{
    struct iphdr *header;
    void* payload;
    uint16_t payload_size;
    uint32_t source_ip;
    uint32_t destination_ip;
} IpPacket;

void IpPacket_build(IpPacket *packet, void *data, uint16_t size);
uint8_t IpPacket_get_version(IpPacket *packet);
uint32_t IpPacket_get_source_ip(IpPacket *packet);
uint32_t IpPacket_get_destination_ip(IpPacket *packet);

#endif /* __NET_TOOLS_IP_PACKET_H__ */