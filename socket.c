#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "socket.h"

int
create_socket() {
	int socket_fd = socket(AF_INET6, SOCK_STREAM, 0);

	if (socket_fd == -1) {
		printf("error: socket creation\n");
		exit(1);
	}

	return socket_fd;
}
