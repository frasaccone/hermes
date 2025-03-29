#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "socket.h"

int
create_socket(unsigned int port) {
	int socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
	struct sockaddr_in address;

	if (socket_fd == -1) {
		printf("error: socket creation\n");
		exit(1);
	}

	address.sin_family = AF_INET6;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
		printf("error: bind socket to address\n");
		exit(1);
	}

	return socket_fd;
}
