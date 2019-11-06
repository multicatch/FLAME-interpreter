#ifndef INTERPRETER_LITERAL_H
#define INTERPRETER_LITERAL_H

#include <stdlib.h>

typedef enum literal_type {
    LT_STRING, LT_LONG, LT_DOUBLE
} literal_type_t;

typedef struct literal {
    char *string_literal;
    size_t string_length;

    long long int long_value;
    long double double_value;

    literal_type_t type;

    void (*set_string)(struct literal *, char *);
    int (*is_same_type)(struct literal *, struct literal *);
} literal_t;

literal_t *lt_clone(literal_t *);
literal_t *create_literal(literal_type_t);

#endif //INTERPRETER_LITERAL_H
