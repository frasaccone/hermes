#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

static const struct {
	char *extension;
	char *type;
} mime_types[] = {
	{ "aac",   "audio/aac" },
	{ "abw",   "application/x-abiword" },
	{ "acng",  "image/apng" },
	{ "arc",   "application/x-freearc" },
	{ "avif",  "image/avif" },
	{ "avi",   "video/x-msvideo" },
	{ "azw",   "application/vnd.amazon.ebook" },
	{ "bmp",   "image/bmp" },
	{ "bz",    "application/x-bzip" },
	{ "bz2",   "application/x-bzip2" },
	{ "cda",   "application/x-cdf" },
	{ "csh",   "application/x-csh" },
	{ "css",   "text/css" },
	{ "csv",   "text/csv" },
	{ "doc",   "application/msword" },
	{ "docx",  "application/vnd.openxmlformats-officedocument."
	           "wordprocessingml.document" },
	{ "eot",   "application/vnd.ms-fontobject" },
	{ "epub",  "application/epub+zip" },
	{ "gif",   "image/gif" },
	{ "gz",    "application/gzip" },
	{ "html",  "text/html" },
	{ "htm",   "text/html" },
	{ "ico",   "image/vnd.microsoft.icon" },
	{ "ics",   "text/calendar" },
	{ "jar",   "application/java-archive" },
	{ "jpeg",  "image/jpeg" },
	{ "jpg",   "image/jpeg" },
	{ "json",  "application/json" },
	{ "jsonld", "application/ld+json" },
	{ "js",    "application/javascript" },
	{ "mid",   "audio/midi" },
	{ "midi",  "audio/x-midi" },
	{ "mjs",   "text/javascript" },
	{ "mp3",   "audio/mpeg" },
	{ "mp4",   "video/mp4" },
	{ "mpkg",  "application/vnd.apple.installer+xml" },
	{ "mpeg",  "video/mpeg" },
	{ "odp",   "application/vnd.oasis.opendocument.presentation" },
	{ "ods",   "application/vnd.oasis.opendocument.spreadsheet" },
	{ "odt",   "application/vnd.oasis.opendocument.text" },
	{ "oga",   "audio/ogg" },
	{ "ogv",   "video/ogg" },
	{ "ogx",   "application/ogg" },
	{ "opus",  "audio/ogg" },
	{ "otf",   "font/otf" },
	{ "pdf",   "application/pdf" },
	{ "php",   "application/x-httpd-php" },
	{ "png",   "image/png" },
	{ "ppt",   "application/vnd.ms-powerpoint" },
	{ "pptx",  "application/vnd.openxmlformats-officedocument."
	           "presentationml.presentation" },
	{ "rar",   "application/vnd.rar" },
	{ "rtf",   "application/rtf" },
	{ "sh",    "application/x-sh" },
	{ "svg",   "image/svg+xml" },
	{ "tar",   "application/x-tar" },
	{ "tif",   "image/tiff" },
	{ "tiff",  "image/tiff" },
	{ "txt",   "text/plain" },
	{ "ts",    "video/mp2t" },
	{ "ttf",   "font/ttf" },
	{ "vsd",   "application/vnd.visio" },
	{ "weba",  "audio/webm" },
	{ "webm",  "video/webm" },
	{ "webp",  "image/webp" },
	{ "woff",  "font/woff" },
	{ "woff2", "font/woff2" },
	{ "xhtml", "application/xhtml+xml" },
	{ "xls",   "application/vnd.ms-excel" },
	{ "xlsx",  "application/vnd.openxmlformats-officedocument."
	           "spreadsheetml.sheet" },
	{ "xml",   "application/xml" },
	{ "xul",   "application/vnd.mozilla.xul+xml" },
	{ "zip",   "application/zip" },
	{ "3gp",   "video/3gpp" },
	{ "3g2",   "video/3gpp2" },
	{ "7z",    "application/x-7z-compressed" },
};

struct file_content {
	char *content;
	size_t length;
};

char *
get_mime_type_from_extension(char *extension);

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
