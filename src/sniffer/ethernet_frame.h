#ifndef __NET_TOOLS_ETHERNET_FRAME_H__
#define __NET_TOOLS_ETHERNET_FRAME_H__

#include <stdint.h>

typedef struct
{
    struct ethhdr *header;
    uint16_t protocol;
    void* payload;
    uint16_t payload_size;
} EthernetFrame;

// EthernetFrame* EthernetFrame_new(void *data);
void EthernetFrame_build(EthernetFrame *frame, void *data, uint16_t size);
uint16_t EthernetFrame_get_protocol(EthernetFrame *frame);
uint8_t* EthernetFrame_get_source_mac(EthernetFrame *frame);
uint8_t* EthernetFrame_get_destination_mac(EthernetFrame *frame);
uint16_t EthernetFrame_get_payload(EthernetFrame *frame, void **result);

#endif /* __NET_TOOLS_ETHERNET_FRAME_H__ */