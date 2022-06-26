#include "humanize.h"
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void humanize_ethernet_procotol(uint16_t protocol, char *result)
{
    char *protocol_str;

    switch (protocol)
    {
    case ETH_P_IP:
        protocol_str = "IP";
        break;
    
    default:
        protocol_str = "Unknown";
        break;
    }

    strcpy(result, protocol_str);
}

void humanize_mac_address(uint8_t mac_address[ETH_ALEN], char *result)
{
    char mac[MAC_STRING_LENGTH];

    snprintf(mac, MAC_STRING_LENGTH, "%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
        mac_address[0],
        mac_address[1],
        mac_address[2],
        mac_address[3],
        mac_address[4],
        mac_address[5]);

    strcpy(result, mac);
}

void humanize_ip_address(uint32_t ip_address, char *result)
{
    struct in_addr source_address = {.s_addr = ip_address};
    strcpy(result, inet_ntoa(source_address));
}