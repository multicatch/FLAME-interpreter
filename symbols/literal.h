#ifndef INTERPRETER_LITERAL_H
#define INTERPRETER_LITERAL_H

#include <stdlib.h>

enum LiteralType {
    LONG_INTEGER_T, STRING_T, FLOAT_T
};

typedef struct literal {
    enum LiteralType type;

    long long_value;
    double double_value;
    char *string_value;
    size_t string_length;
} literal_t;

literal_t *create_string(char *);

#endif //INTERPRETER_LITERAL_H
