#ifndef SOCKET_H
#define SOCKET_H

/* creates a socket and a local address at the given port, binds them,
   listens for connections and returns the socket file descriptor */
int
create_socket(unsigned int port);

/* closes a socket */
void
close_socket(int socket_fd);

/* accepts a connection from the server socket and returns the client socket
   file descriptor */
int
accept_client(int server_socket_fd);

/* writes the client request to a buffer, returns -1 in case of an error and 0
   otherwise */
int
read_client_request(int client_socket_fd,
                    char *buffer,
                    unsigned int buffer_size);

#endif
