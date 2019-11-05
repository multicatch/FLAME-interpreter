#ifndef INTERPRETER_OPERATOR_H
#define INTERPRETER_OPERATOR_H

#include "../parse/parse.h"
#include "literal.h"

typedef struct operator {
    char *identifier;

    cst_node_t *representation;
    literal_t *(*evaluate)(struct operator *, literal_t *, cst_node_t *);
} operator_t;

operator_t *create_operator(const char *);

#endif //INTERPRETER_OPERATOR_H
