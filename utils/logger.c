#include "logger.h"
#include <stdio.h>

char *file_name = "stdin";
size_t line_number = 0;
size_t suppressed_size = 0;
message_type_t *suppressed = NULL;

void set_line(char *name, size_t number) {
    file_name = name;
    line_number = number;
}

void suppress(message_type_t type) {
    message_type_t *tmp = malloc((suppressed_size + 1) * sizeof(message_type_t));
    for (size_t i = 0; i < suppressed_size; i++) {
        tmp[i] = suppressed[i];
    }
    tmp[suppressed_size + 1] = type;
    suppressed_size += 1;
    if (suppressed != NULL) {
        free(suppressed);
    }
    suppressed = tmp;
}

int is_suppressed(message_type_t type) {
    for (size_t i = 0; i < suppressed_size; i++) {
        if (suppressed[i] == type) {
            return 1;
        }
    }
    return 0;
}

char *create_message(message_type_t type) {
    if (type == MSG_REDECLARATION) {
        return "\"%s\" is already defined and will be changed.";
    }

    if (type == MSG_UNDECLARED) {
        return "Operator \"%s\" is undefined and will be ignored.";
    }

    if (type == MSG_WRONG_TYPE) {
        return "\"%s\" not recognized as any literal";
    }

    return "%s";
}

void warn(message_type_t type, char *argument) {
    if (is_suppressed(type)) {
        return;
    }
    printf("[%s: line %zu] WARNING: ", file_name, line_number);
    printf(create_message(type), argument);
    printf("\n");
}