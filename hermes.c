#include <stdio.h>

void
print_usage(char *program_name) {
	printf("usage: %s", program_name);
}

int
main(int argc, char *argv[]) {
	char *program_name = argv[0];
	int i;

	for (i = 1; i < argc; i++) {
		char *argument = argv[i];

		if (argument[0] != '-') {
			print_usage(program_name);
			return 1;
		}

		switch (argument[1]) {
		default:
			print_usage(program_name);
			return 1;
		}
	}

	return 0;
}
