#include <stdio.h>
#include <stdlib.h>

void
print_usage(char *program_name) {
	printf("usage: %s [-p port]", program_name);
}

int
main(int argc, char *argv[]) {
	char *program_name = argv[0];
	int i, port = 80;

	for (i = 1; i < argc; i++) {
		char *argument = argv[i];
		int value_exists = i + 1 < argc;

		if (argument[0] != '-') {
			print_usage(program_name);
			return 1;
		}

		switch (argument[1]) {
		case 'p':
			if (!value_exists) {
				print_usage(program_name);
				return 1;
			}
			port = atoi(argv[i + 1]);
			i++;
			break;
		default:
			print_usage(program_name);
			return 1;
		}
	}

	return 0;
}
