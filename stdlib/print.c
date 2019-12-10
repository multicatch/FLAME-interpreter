#include "print.h"

#include "../evaluator/evaluator.h"
#include <stdio.h>

void print_lt(literal_t *result) {
    if (result->type == LT_STRING) {
        printf("%s\n", result->string_literal);
    }
    if (result->type == LT_LONG) {
        printf("%lld\n", result->long_value);
    }
    if (result->type == LT_DOUBLE) {
        printf("%Lf\n", result->double_value);
    }
}

literal_t *op_t_print_evaluate(struct operator *self, literal_t *acc, cst_node_t **argument) {
    literal_t *result = evaluate(argument[0], acc);
    print_lt(result);
    return result;
}

operator_t *create_print() {
    operator_t *print_op = malloc(sizeof(operator_t));
    print_op->identifier = "print";
    print_op->representation = NULL;
    print_op->arguments_count = 1;
    print_op->evaluate = op_t_print_evaluate;
    return print_op;
}