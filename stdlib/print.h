#ifndef INTERPRETER_PRINT_H
#define INTERPRETER_PRINT_H

#include "../symbols/operator.h"
#include "../symbols/literal.h"

void print_lt(literal_t *);
operator_t *create_print();

#endif //INTERPRETER_PRINT_H
