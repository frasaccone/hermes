#include "http.h"

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
