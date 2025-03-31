#include "file.h"

#include <unistd.h>

int
file_exists(const char *path) {
	return (access(path, R_OK) == 0);
}
