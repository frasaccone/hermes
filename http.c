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
			result->method = UNSUPPORTED;
		}
	}

	if (path_string != NULL) {
		strncpy(result->path,
		        path_string,
		        HTTP_REQUEST_PATH_MAX_LENGTH - 1);
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

char *
compose_http_response_head(struct http_response response) {
	size_t size;
	unsigned int status_code = status_map[response.status].code;
	const char *template = "HTTP/1.1 %u %s\r\n"
	                       "Content-Type: %s; charset=UTF-8\r\n"
	                       "Content-Length: %u\r\n",
	           *status_message = status_map[response.status].message,
	           *content_type = response.content_type,
	           *body = response.body;
	char *buffer;

	/*
	 * This is actually a bit inelegant: it adds the length of 'template'
	 * with the length of each component of http_response; it will result
	 * in something bigger than the actual size of the response due to 
	 * the template patterns in %, but that is just a few bytes and nobody
	 * really minds it.
	 */
	size = strlen(template)
	       + get_length_of_integer(status_code)
	       + strlen(status_message)
	       + strlen(content_type)
	       + get_length_of_integer(strlen(body));

	buffer = malloc(size);

	snprintf(buffer, size, template,
	         status_code,
	         status_message,
	         content_type,
	         strlen(body));

	buffer[size] = '\0';

	return buffer;
}

char *
compose_http_response_full(struct http_response response) {
	size_t size;
	const char *template = "%s"
	                       "\r\n"
	                       "%s\n",
	           *head = compose_http_response_head(response),
	           *body = response.body;
	char *buffer;

	/*
	 * Read the comment inside the compose_http_response_head function in
	 * this same file.
	 */
	size = strlen(template)
	       + strlen(head)
	       + strlen(body);

	buffer = malloc(size);

	snprintf(buffer, size, template,
	         head,
	         body);

	buffer[size] = '\0';

	return buffer;
}
