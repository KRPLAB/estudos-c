#include <string.h>
#include <sys/socket.h>

#include "../../include/utils.h"
#include "../../include/common.h"

char *tokenize(char *str, const char *delimiters) {
    return strtok(str, delimiters);
}

int identify_method(const char *method_str) {
    if (strcmp(method_str, "GET") == 0) {
        return GET;
    } else if (strcmp(method_str, "POST") == 0) {
        return POST;
    } else if (strcmp(method_str, "PUT") == 0) {
        return PUT;
    } else if (strcmp(method_str, "PATCH") == 0) {
        return PATCH;
    } else if (strcmp(method_str, "DELETE") == 0) {
        return DELETE;
    } else {
        return UNKNOWN;
    }
}

int utils_send_all(int s, char *buf, int *len) {
    int total = 0;
    int bytesleft = *len;
    int n = 0;

    while (total < *len) {
        n = send(s, buf + total, bytesleft, 0);
        if (n == -1)
            break;

        total += n;
        bytesleft -= n;
    }

    *len = total;

    return n == -1 ? -1 : 0;
}
