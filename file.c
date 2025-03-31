#include "file.h"

#include <unistd.h>

int
file_exists(char *path) {
	return (access(path, R_OK) == 0);
}
