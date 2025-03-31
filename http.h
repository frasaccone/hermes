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

static const struct {
	enum http_response_status status;
	unsigned int code;
	const char *message;
} status_map[] = {
	{ BAD_REQUEST          , 400, "Bad Request" },
	{ FORBIDDEN            , 403, "Forbidden" },
	{ INTERNAL_SERVER_ERROR, 500, "Internal Server Error" },
	{ METHOD_NOT_ALLOWED   , 405, "Method Not Allowed" },
	{ MOVED_PERMANENTLY    , 301, "Moved Permanently" },
	{ NOT_FOUND            , 404, "Not Found" },
	{ NOT_MODIFIED         , 304, "Not Modified" },
	{ OK                   , 200, "OK" },
	{ PARTIAL_CONTENT      , 206, "Partial Content" },
	{ RANGE_NOT_SATISFIABLE, 416, "Range Not Satisfiable" },
	{ REQUEST_TIMEOUT      , 408, "Request Timeout" },
	{ REQUEST_TOO_LARGE    , 413, "Request Entity Too Large" },
	{ VERSION_NOT_SUPPORTED, 505, "HTTP Version Not Supported" },
};

struct http_request {
	enum http_request_method method;
	char path[HTTP_REQUEST_PATH_MAX_LENGTH];
};

struct http_response {
	enum http_response_status status;
	const char *content_type;
	char *body;
	unsigned int body_length;
};

struct http_request *
parse_http_request(char *request);

/*
 * Writes a raw HTTP response to buffer, given a http_response.
 */
void
compose_http_response(struct http_response response,
                      char *buffer,
                      unsigned int buffer_size);

#endif
