#ifndef SOCKET_H
#define SOCKET_H

/* creates a socket and a local address at the given port, binds them,
   listens for connections and returns the socket file descriptor */
int
create_socket(unsigned int port);

#endif
