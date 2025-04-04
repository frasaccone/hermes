#ifndef HTTP_H
#define HTTP_H

#define HTTP_REQUEST_PATH_MAX_LENGTH 256

enum http_request_method {
	GET,
	HEAD,
	UNSUPPORTED,
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
};

/*
 * Returns the http_request from a raw client request string.
 */
struct http_request *
parse_http_request(char *request);

/*
 * Returns the head of the raw HTTP response from a given a http_response.
 */
char *
compose_http_response_head(struct http_response response);

/*
 * Returns the raw HTTP response, composed of both head and body, from a
 * given a http_response.
 */
char *
compose_http_response_full(struct http_response response);

#endif
