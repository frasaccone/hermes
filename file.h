#ifndef FILE_H
#define FILE_H

int
is_file_readable(char *path);

char *
get_normalised_path(char *path);

/*
 * Returns NULL in case of an error and a buffer containing the content of the
 * file at the given path otherwise..
 */
char *
get_file_content(char *path);

#endif
