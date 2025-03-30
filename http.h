#ifndef HTTP_H
#define HTTP_H

#define HTTP_REQUEST_PATH_MAX_LENGTH 256

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
