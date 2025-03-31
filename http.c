#include "http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct http_request *
parse_http_request(char *request) {
	struct http_request *result = malloc(sizeof(struct http_request));
	
	if (result == NULL) {
		return NULL;
	}

	char *method_string = strtok(request, " "),
	     *path_string = strtok(NULL, " ");

	if (method_string != NULL) {
		if (strcmp(method_string, "GET") == 0) {
			result->method = GET;
		} else if (strcmp(method_string, "HEAD") == 0) {
			result->method = HEAD;
		} else {
			/* only GET and HEAD are supported */
			free(result);
			return NULL;
		}
	}

	if (path_string != NULL) {
		strncpy(result->path, path_string, HTTP_REQUEST_PATH_MAX_LENGTH - 1);
		result->path[HTTP_REQUEST_PATH_MAX_LENGTH - 1] = '\0';
	}

	return result;
}

unsigned int
get_length_of_integer(unsigned int integer) {
	unsigned int result = 0;

	while (integer > 1) {
		integer /= 10;
		result++;
	}

	return result;
}

void
compose_http_response(struct http_response response, char *buffer) {
	size_t size;
	unsigned int status_code = status_map[response.status].code,
	             body_length = response.body_length;
	const char *template = "HTTP/1.1 %u %s\r\n"
	                       "Content-Type: %s; charset=UTF-8\r\n"
	                       "Content-Length: %u\r\n"
	                       "\r\n"
	                       "%s",
	           *status_message = status_map[response.status].message,
	           *content_type = response.content_type,
	           *body = response.body;

	/*
	 * This is actually a bit inelegant: it adds the length of 'template'
	 * with the length of each component of http_response; it then removes
	 * the number of characters occupied by template patterns of the form
	 * '%x', that is, 2 times the number of template patterns used.
	 */
	size = strlen(template)
	       + get_length_of_integer(status_code)
	       + strlen(status_message)
	       + strlen(content_type)
	       + get_length_of_integer(body_length)
	       + strlen(body)
	       - 2 * 5;

	snprintf(buffer, size, template,
	         status_code,
	         status_message,
	         content_type,
	         body_length,
	         body);
}
