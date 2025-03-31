#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "socket.h"

#define DIRECTORY_INDEX_MAX_LENGTH 32
#define USER_MAX_LENGTH 32

void
print_usage(char *program_name) {
	printf("usage: %s [-p port] [-i file] [-u user]\n",
	       program_name);
}

int
main(int argc, char *argv[]) {
	char *program_name = argv[0],
	     user[USER_MAX_LENGTH] = "nobody",
	     directory_index[DIRECTORY_INDEX_MAX_LENGTH] = "index.html";
	int i, port = 80,
	    server_socket_fd;

	for (i = 1; i < argc; i++) {
		char *argument = argv[i];
		int value_exists = i + 1 < argc;

		if (argument[0] != '-') {
			print_usage(program_name);
			return 1;
		}

		/* if argument[2] is a non-null character */
		if (argument[2]) {
			print_usage(program_name);
			return 1;
		}

		if (!value_exists) {
			print_usage(program_name);
			return 1;
		}

		switch (argument[1]) {
		case 'p':
			port = atoi(argv[i + 1]);
			i++;
			break;
		case 'i':
			if (strlen(argv[i + 1]) >= DIRECTORY_INDEX_MAX_LENGTH) {
				printf("error: directory index must be less than "
				       "%u characters",
				       DIRECTORY_INDEX_MAX_LENGTH);
				return 1;
			}
			strncpy(directory_index, argv[i + 1], sizeof(directory_index) - 1);
			directory_index[sizeof(directory_index) - 1] = '\0';
			i++;
			break;
		case 'u':
			if (strlen(argv[i + 1]) >= USER_MAX_LENGTH) {
				printf("error: the user length must be less than "
				       "%u characters",
				       USER_MAX_LENGTH);
				return 1;
			}
			strncpy(user, argv[i + 1], sizeof(user) - 1);
			user[sizeof(user) - 1] = '\0';
			i++;
			break;
		default:
			print_usage(program_name);
			return 1;
		}
	}

	if (port < 1 || port > 65535) {
		printf("error: port must be between 1 and 65535.");
		return 1;
	};

	server_socket_fd = create_socket(port);

	while (1) {
		int client_socket_fd = accept_client(server_socket_fd),
		    buffer_size = 104857600 * sizeof(char); /* i.e. 100 MiB */
		char *buffer = malloc(buffer_size);

		read_client_request(client_socket_fd, buffer, buffer_size);
	}

	return 0;
}
