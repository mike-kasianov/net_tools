#ifndef __NET_TOOLS_SNIFFER_SOCKET_H__
#define __NET_TOOLS_SNIFFER_SOCKET_H__

#include <sys/socket.h>

typedef struct _SnifferSocket SnifferSocket;

SnifferSocket* SnifferSocket_open(char *network_interface);
void SnifferSocket_close(SnifferSocket *sock);
ssize_t SnifferSocket_receive(SnifferSocket *sock, void* buffer, size_t buffer_size);

#endif /* __NET_TOOLS_SNIFFER_SOCKET_H__ */