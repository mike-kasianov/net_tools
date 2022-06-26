#ifndef __NET_TOOLS_HUMANIZE_C__
#define __NET_TOOLS_HUMANIZE_C__

#include <stdint.h>
#include <linux/if_ether.h>

#define MAC_STRING_LENGTH 18
#define IPV4_STRING_LENGTH 16

void humanize_ethernet_procotol(uint16_t protocol, char *result);
void humanize_mac_address(uint8_t mac_address[ETH_ALEN], char *result);
void humanize_ip_address(uint32_t ip_address, char *result);

#endif /* __NET_TOOLS_HUMANIZE_C__ */