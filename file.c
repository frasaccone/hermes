#include "file.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
is_file_readable(char *path) {
	return (access(path, R_OK) == 0);
}

char *
get_normalised_path(char *path) {
	char *normalised;
	int i,
	    j;

	if (path == NULL) {
		return path;
	}

	normalised = malloc(strlen(path) + 1);

	if (normalised == NULL) {
		return normalised;
	}

	j = 0;
	for (i = 0; path[i] != '\0'; i++) {
		if (path[i] != '/' ||
		    i == 0 ||
		    path[i - 1] != '/') {
			normalised[j] = path[i];
			j++;
		}
	}

	normalised[j] = '\0';

	return normalised;
}
