#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

static const struct {
	const char *extension;
	const char *type;
} mime_types[] = {
	{ "css",   "text/css" },
	{ "gif",   "image/gif" },
	{ "gz",    "application/gzip" },
	{ "html",  "text/html" },
	{ "htm",   "text/html" },
	{ "ico",   "image/x-icon" },
	{ "jpeg",  "image/jpeg" },
	{ "jpg",   "image/jpeg" },
	{ "js",    "application/javascript" },
	{ "json",  "application/json" },
	{ "mp3",   "audio/mpeg" },
	{ "mp4",   "video/mp4" },
	{ "pdf",   "application/pdf" },
	{ "png",   "image/png" },
	{ "tar",   "application/x-tar" },
	{ "txt",   "text/plain" },
	{ "wav",   "audio/wav" },
	{ "xml",   "application/xml" },
	{ "zip",   "application/zip" },
};

struct file_content {
	char *content;
	size_t length;
};

int
is_file_readable(char *path);

char *
get_normalised_path(char *path);

char *
get_file_name(char *path);

char *
get_file_extension(char *path);

/*
 * It returns the file_content instances of the file at given path.
 *
 * Returns 'struct file_content { NULL, 0 }' in case of an error and a 
 * non-empty file_content instance otherwise.
 */
struct file_content
get_file_content(char *path);

#endif
