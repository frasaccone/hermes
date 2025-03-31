#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "socket.h"
#include "utils.h"

#define DIRECTORY_INDEX_MAX_LENGTH 32
#define USER_NAME_MAX_LENGTH 32
#define GROUP_NAME_MAX_LENGTH 32

void
print_usage(char *program_name) {
	print_error("usage: %s [-p port] [-i file] [-u user] [-g group]",
	            program_name);
}

int
main(int argc, char *argv[]) {
	char *program_name = argv[0],
	     user_name[USER_NAME_MAX_LENGTH] = "nobody",
	     group_name[GROUP_NAME_MAX_LENGTH] = "nogroup",
	     directory_index[DIRECTORY_INDEX_MAX_LENGTH] = "index.html";
	int i, port = 80,
	    server_socket_fd;
	struct passwd *user;
	struct group *group;

	for (i = 1; i < argc; i++) {
		char *argument = argv[i];

		if (argument[0] != '-' ||
		    argument[1] == '\0' ||
		    argument[2] != '\0' ||
		    i + 1 >= argc /* Argument value exists */) {
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
				print_error("error: directory index must be less than "
				            "%u characters",
				            DIRECTORY_INDEX_MAX_LENGTH);
			}
			strncpy(directory_index, argv[i + 1], sizeof(directory_index) - 1);
			directory_index[sizeof(directory_index) - 1] = '\0';
			i++;
			break;
		case 'u':
			if (strlen(argv[i + 1]) >= USER_NAME_MAX_LENGTH) {
				print_error("error: the user name must be less than "
				            "%u characters",
				            USER_NAME_MAX_LENGTH);
			}
			strncpy(user_name, argv[i + 1], sizeof(user_name) - 1);
			user_name[sizeof(user_name) - 1] = '\0';
			i++;
			break;
		case 'g':
			if (strlen(argv[i + 1]) >= GROUP_NAME_MAX_LENGTH) {
				print_error("error: the group name must be less than "
				            "%u characters",
				            GROUP_NAME_MAX_LENGTH);
			}
			strncpy(group_name, argv[i + 1], sizeof(group_name) - 1);
			group_name[sizeof(group_name) - 1] = '\0';
			i++;
			break;
		default:
			print_usage(program_name);
			return 1;
		}
	}

	if (port < 1 || port > 65535) {
		print_error("error: port must be between 1 and 65535.");
		return 1;
	};

	user = getpwnam(user_name);
	group = getgrnam(group_name);

	if (user == NULL) {
		print_error("error: user %s does not exist.", user_name);
		return 1;
	}

	if (group == NULL) {
		print_error("error: group %s does not exist.", group_name);
		return 1;
	}

	server_socket_fd = create_socket(port);

	switch (fork()) {
	case -1:
		print_error("error: could not fork process.");
		break;
	case 0:
		/* Child process */

		while (1) {
			int client_socket_fd,
			    buffer_size = 104857600 * sizeof(char); /* i.e. 100 MiB */
			char *buffer = malloc(buffer_size);

			client_socket_fd = accept_client(server_socket_fd);

			if (client_socket_fd == -1) {
				free(buffer);
				close_socket(client_socket_fd);
				continue;
			}

			if (read_client_request(client_socket_fd,
			                        buffer,
			                        buffer_size) == -1) {
				free(buffer);
			}

			free(buffer);
			close_socket(client_socket_fd);
		}

		break;
	default:
	}

	close_socket(server_socket_fd);

	return 0;
}
