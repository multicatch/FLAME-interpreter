#include "print.h"
#include <stdio.h>
#include <stdlib.h>

void print_statement_t_evaluate(literal_t **arguments, size_t count) {
    if (count < 1) {
        return;
    }

    literal_t *literal = arguments[0];
    if (literal->type == STRING_T) {
        printf("%s", literal->string_value);
    }

    if (literal->type == LONG_INTEGER_T) {
        printf("%ld", literal->long_value);
    }

    if (literal->type == FLOAT_T) {
        printf("%f", literal->double_value);
    }
}

statement_t *create_print_statement() {
    symbol_t *symbol = malloc(sizeof(symbol_t));
    symbol->identifier = "print";
    symbol->identifier_length = 5;
    
    statement_t *result = malloc(sizeof(statement_t));
    result->symbol = symbol;
    result->argument_count = 1;
    result->evaluate = print_statement_t_evaluate;
    
    return result;
}
