#ifndef INTERPRETER_LOGGER_H
#define INTERPRETER_LOGGER_H
#include <stdlib.h>

typedef enum message_type {
    MSG_REDECLARATION, MSG_UNDECLARED, MSG_WRONG_TYPE
} message_type_t;

void set_line(char*, size_t);
void suppress(message_type_t);
void warn(message_type_t, char *);

#endif //INTERPRETER_LOGGER_H
