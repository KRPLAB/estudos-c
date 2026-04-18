#include <string.h>        // Para strlen

#include "../../include/utils.h"
#include "../../include/common.h"

char *tokenize(char *str, const char *delimiters) {
    return strtok(str, delimiters);
}

int identify_method(const char *first_line) {
    if (strncmp(first_line, "GET ", 4) == 0) {
        return GET;
    } else if (strncmp(first_line, "POST ", 5) == 0) {
        return POST;
    } else if (strncmp(first_line, "PUT ", 4) == 0) {
        return PUT;
    } else if (strncmp(first_line, "PATCH ", 6) == 0) {
        return PATCH;
    } else if (strncmp(first_line, "DELETE ", 7) == 0) {
        return DELETE;
    } else {
        return UNKNOWN;
    }
}
