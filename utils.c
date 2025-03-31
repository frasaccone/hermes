#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void
critical(const char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
