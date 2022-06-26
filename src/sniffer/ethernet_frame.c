#include "ethernet_frame.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <netinet/in.h>

#define MAC_OCTETS_COUNT 6
// #define MAC_STRING_REPREZENTATION_SIZE 18

// struct _EthernetFrame
// {
//     struct ethhdr *header;
//     // uint16_t protocol;
//     // uint8_t source_mac;
//     // uint8_t destination_mac;
//     char source_mac_str[MAC_STRING_REPREZENTATION_SIZE];
//     char destination_mac_str[MAC_STRING_REPREZENTATION_SIZE];
//     void* payload;
//     uint16_t payload_size;
// };

// Internal

// Public

// EthernetFrame* EthernetFrame_new(void *data)
// {
//     struct ethhdr *header = data;

//     EthernetFrame *frame = calloc(1, sizeof(EthernetFrame));
//     frame->header = header;
    
    
//     return frame;
// }

void EthernetFrame_build(EthernetFrame *frame, void *data, uint16_t size)
{
    memset(frame, 0, sizeof(EthernetFrame));
    frame->header = (struct ethhdr *) data;
    frame->payload_size = size - sizeof(struct ethhdr);
    frame->payload = (char *)data + sizeof(struct ethhdr);

    // printf("E            %d\n", frame->payload_size);
}

uint16_t EthernetFrame_get_protocol(EthernetFrame *frame)
{
    if (frame->protocol == 0)
    {
        frame->protocol = ntohs(frame->header->h_proto);
    }

    return frame->protocol;
}

uint8_t* EthernetFrame_get_source_mac(EthernetFrame *frame)
{
    return frame->header->h_source;
}

uint8_t* EthernetFrame_get_destination_mac(EthernetFrame *frame)
{
    return frame->header->h_dest;
}

uint16_t EthernetFrame_get_payload(EthernetFrame *frame, void *result)
{
    result = frame->payload;
    return frame->payload_size;
}
