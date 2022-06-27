#include "sniffer_socket.h"
#include "ethernet_frame.h"
#include "ip_v4_packet.h"
#include "humanize.h"

#include <stdio.h>
#include <string.h>

#include <linux/if_ether.h>

void print_packet(void *data, uint16_t size, uint32_t packet_id)
{
    printf("#############################################\n");
    printf("Packet #%d (%d bytes read)\n", packet_id, size);
}

void print_ip_packet(IpV4Packet *ip_packet)
{
    printf("==IP_HEADER==================================\n");
    uint8_t a = ip_packet->header->version;
    printf("IP version            %d\n", a);
    printf("IP header length      %d\n", IpV4Packet_get_header_length(ip_packet));
    printf("TOS                   %d\n", IpV4Packet_get_type_of_service(ip_packet));


    char ip_source_str[IPV4_STRING_LENGTH];
    humanize_ip_v4_address(IpV4Packet_get_source_address(ip_packet), ip_source_str);
    printf("IP source             %s\n", ip_source_str);

    char ip_destination_str[IPV4_STRING_LENGTH];
    humanize_ip_v4_address(IpV4Packet_get_destination_address(ip_packet), ip_destination_str);
    printf("IP destination        %s\n", ip_destination_str);
}

void print_ethernet_frame(EthernetFrame *ethernet_frame)
{
    uint16_t protocol = EthernetFrame_get_protocol(ethernet_frame);
    char protocol_str[10];
    char source_mac[MAC_STRING_LENGTH];
    char destination_mac[MAC_STRING_LENGTH];

    humanize_ethernet_procotol(protocol, protocol_str);
    humanize_mac_address(EthernetFrame_get_source_mac(ethernet_frame), source_mac);
    humanize_mac_address(EthernetFrame_get_destination_mac(ethernet_frame), destination_mac);

    printf("==ETHERNET_HEADER============================\n");
    printf("MAC source            %s\n", source_mac);
    printf("MAC destination       %s\n", destination_mac);
    printf("Packet type ID field  %#x (%s)\n", protocol, protocol_str);

    void *ethernet_payload = NULL;
    uint16_t ethernet_payload_size = EthernetFrame_get_payload(ethernet_frame, &ethernet_payload);

    switch (protocol)
    {
    case ETH_P_IP:
        IpV4Packet ip_packet;
        IpV4Packet_build(&ip_packet, ethernet_payload, ethernet_payload_size);
        print_ip_packet(&ip_packet);
        break;
    default:
     
        break;
    }
}

void sniff()
{
    SnifferSocket *socket = SnifferSocket_open("wlp1s0");
    uint16_t BUFFER_SIZE = 1542;
    uint8_t packet_buf[BUFFER_SIZE];
    uint32_t packet_count = 0;
    uint16_t bytes_count = 0;
    EthernetFrame ethernet_frame;

    while (1)
    {
        memset(packet_buf, 0, BUFFER_SIZE);
        // memset(ethernet_frame, 0, sizeof(EthernetFrame));

        bytes_count = SnifferSocket_receive(socket, packet_buf, BUFFER_SIZE);
        if (bytes_count > 0)
        {
            packet_count++;
            
            // dump_data(packet_count, packet_buf, bytes_count);

            print_packet(packet_buf, bytes_count, packet_count);
            EthernetFrame_build(&ethernet_frame, packet_buf, bytes_count);
            print_ethernet_frame(&ethernet_frame);
        }
    }
}

int main(int argc, char *argv[])
{
    sniff();
}