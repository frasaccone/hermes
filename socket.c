#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "socket.h"
#include "utils.h"

int
create_socket(unsigned int port) {
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;

	if (socket_fd == -1) {
		print_error("error: socket creation");
		exit(1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
		print_error("error: bind socket to address");
		exit(1);
	}

	if (listen(socket_fd, 3) == -1) {
		print_error("error: listen on socket");
		close(socket_fd);
		exit(1);
	}

	return socket_fd;
}

void
close_socket(int socket_fd) {
	close(socket_fd);
}

int
accept_client(int server_socket_fd) {
	struct sockaddr_in client_address;
	socklen_t client_address_length = sizeof(client_address);
	int client_socket_fd = accept(server_socket_fd,
	                              (struct sockaddr *)&client_address,
	                              &client_address_length);

	return client_socket_fd;
}

int
read_client_request(int client_socket_fd,
                    char *buffer,
                    unsigned int buffer_size) {
	if (buffer == NULL || buffer_size == 0) {
		print_error("error: invalid buffer provided in read_client_request");
		return -1;
	}

	memset(buffer, 0, buffer_size);

	ssize_t bytes_received = recv(client_socket_fd,
	                              buffer,
	                              buffer_size - 1,
	                              0);

	if (bytes_received <= 0) {
		return -1;
	}

	if (bytes_received < buffer_size) {
		buffer[bytes_received] = '\0';
		return -1;
	}

	buffer[buffer_size - 1] = '\0';

	return 0;
}
