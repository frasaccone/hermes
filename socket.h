#ifndef SOCKET_H
#define SOCKET_H

/*
 * Creates a socket and a local address at the given port, binds them,
 * listens for connections and returns the socket file descriptor.
 *
 * Returns -1 in case of an error and the socket file descriptor otherwise.
 */
int
create_socket(unsigned int port);

/*
 * Closes a socket.
 */
void
close_socket(int socket_fd);

/*
 * Returns -1 in case of an error and the length of a socket (actually a
 * generic file descriptor) otherwise.
 */
int
get_socket_size(int socket_fd);

/* 
 * Accepts a connection from the server socket and returns the client socket
 * file descriptor.
 *
 * Returns -1 in case of an error and the socket file descriptor otherwise.
 */
int
accept_client(int server_socket_fd);

/*
 * Writes the client request to a buffer.
 *
 * Returns -1 in case of an error and 0 otherwise.
 */
int
read_client_request(int client_socket_fd,
                    char *buffer,
                    unsigned int buffer_size);

#endif
