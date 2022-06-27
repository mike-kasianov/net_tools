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
} IpV4Packet;

void IpPacket_build(IpV4Packet *packet, void *data, uint16_t size);
uint8_t IpPacket_get_version(IpV4Packet *packet);
uint32_t IpPacket_get_source_address(IpV4Packet *packet);
uint32_t IpPacket_get_destination_address(IpV4Packet *packet);
uint8_t IpPacket_get_header_length(IpV4Packet *packet);
uint8_t IpPacket_get_type_of_service(IpV4Packet *packet);

#endif /* __NET_TOOLS_IP_PACKET_H__ */