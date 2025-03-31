#include "file.h"

#include <stdio.h>
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

struct file_content
get_file_content(char *path) {
	struct file_content result = { NULL, 0 };
	FILE *file = fopen(path, "rb");
	long file_size;
	size_t bytes_read;

	if (file == NULL) {
		return result;
	}

	/* Move the file pointer to the end of the file */
	fseek(file, 0, SEEK_END);
	/* Get the size */
	file_size = ftell(file);
	/* Come back at the start of the file */
	fseek(file, 0, SEEK_SET);

	result.content = malloc(file_size + 1);

	if (!result.content) {
		fclose(file);
		return result;
	}

	bytes_read = fread(result.content, 1, file_size, file);

	/* 'result' gets written here. Before this, it remained { NULL, 0 }. */
	result.content[bytes_read] = '\0';
	result.length = bytes_read;

	fclose(file);

	return result;
}
