#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void
critical(const char *message, ...) {
	va_list arguments;

	va_start(arguments, message);
	vfprintf(stderr, message, arguments);
	va_end(arguments);

	fprintf(stderr, "\n");

	exit(1);
}
