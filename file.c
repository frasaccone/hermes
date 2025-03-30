#include "file.h"

int
file_exists(const char *path) {
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}
