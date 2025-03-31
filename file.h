#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

struct file_content {
	char *content;
	size_t length;
};

int
is_file_readable(char *path);

char *
get_normalised_path(char *path);

/*
 * It returns the file_content instances of the file at given path.
 *
 * Returns 'struct file_content { NULL, 0 }' in case of an error and a 
 * non-empty file_content instance otherwise.
 */
struct file_content
get_file_content(char *path);

#endif
