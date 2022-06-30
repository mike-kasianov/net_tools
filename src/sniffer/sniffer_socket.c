#include "sniffer_socket.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <unistd.h>

#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

struct _SnifferSocket
{
    int fd;
};

SnifferSocket* SnifferSocket_open(char *network_interface)
{
    int fd;
    struct ifreq interface_request;

    fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    strcpy(interface_request.ifr_ifrn.ifrn_name, network_interface);
    if (ioctl(fd, SIOCGIFFLAGS, &interface_request) < 0)
    {
        perror("ioctl() failed");
        close(fd);
        exit(-1);
    }

    interface_request.ifr_flags |= IFF_PROMISC;

    if (ioctl(fd, SIOCSIFFLAGS, &interface_request) < 0) {
        perror("ioctl() failed");
        close(fd);
        exit(-1);
    }

    int ifindex = if_nametoindex(network_interface);
    struct sockaddr_ll sock_addr = {.sll_family = AF_PACKET, .sll_protocol = ETH_P_ALL, .sll_ifindex = ifindex };
    bind(fd, (struct sockaddr *) &sock_addr, sizeof(struct sockaddr_ll));

// TODO remove calloc
    SnifferSocket *sock = calloc(1, sizeof(SnifferSocket));
    sock->fd = fd;

    return sock;
}

ssize_t SnifferSocket_receive(SnifferSocket *sock, void* buffer, size_t buffer_size)
{
    ssize_t result = recvfrom(sock->fd, buffer, buffer_size, 0, 0, 0);

    if (result == -1)
    {
        perror("recvfrom() failed");
    }
    
    return result;
}

// ssize_t Socket_receive_fun(Socket *socket, void* buffer) {}

void SnifferSocket_close(SnifferSocket *sock)
{
    // TODO put flags back
    close(sock->fd);
    free(sock);
}