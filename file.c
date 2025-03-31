#include "file.h"

#include <unistd.h>

int
is_file_readable(char *path) {
	return (access(path, R_OK) == 0);
}
