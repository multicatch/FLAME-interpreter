#include "print.h"

#include "../symbols/operator.h"
#include "../evaluator/evaluator.h"
#include <stdio.h>

literal_t *op_t_print_evaluate(struct operator *self, literal_t *acc, cst_node_t *argument) {
    literal_t *result = evaluate(argument, acc);
    if (result->type == LT_STRING) {
        printf("%s\n", result->string_literal);
    }
    if (result->type == LT_LONG) {
        printf("%lld\n", result->long_value);
    }
    if (result->type == LT_DOUBLE) {
        printf("%Lf\n", result->double_value);
    }
    return result;
}

operator_t *create_print() {
    operator_t *print_op = malloc(sizeof(operator_t));
    print_op->identifier = "print";
    print_op->representation = NULL;
    print_op->evaluate = op_t_print_evaluate;
    return print_op;
}