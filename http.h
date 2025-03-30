#ifndef HTTP_H
#define HTTP_H

#define HTTP_REQUEST_PATH_MAX_LENGTH 256

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

enum http_request_method {
	GET,
	HEAD,
};

enum http_response_status {
	BAD_REQUEST,
	FORBIDDEN,
	INTERNAL_SERVER_ERROR,
	METHOD_NOT_ALLOWED,
	MOVED_PERMANENTLY,
	NOT_FOUND,
	NOT_MODIFIED,
	OK,
	PARTIAL_CONTENT,
	RANGE_NOT_SATISFIABLE,
	REQUEST_TIMEOUT,
	REQUEST_TOO_LARGE,
	VERSION_NOT_SUPPORTED,
};

struct http_request {
	enum http_request_method method;
	char path[HTTP_REQUEST_PATH_MAX_LENGTH];
};

#endif
