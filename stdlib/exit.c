#include "exit.h"

#include "../symbols/operator.h"
#include <stdio.h>

literal_t *op_t_exit_evaluate(struct operator *self, literal_t *acc, cst_node_t *argument) {
    if (acc->type == LT_STRING) {
        printf("%s\n", acc->string_literal);
    }
    if (acc->type == LT_LONG) {
        printf("%lld", acc->long_value);
    }
    if (acc->type == LT_DOUBLE) {
        printf("%Lf", acc->double_value);
    }

    return NULL;
}

operator_t *create_exit() {
    operator_t *exit_op = malloc(sizeof(operator_t));
    exit_op->identifier = ";";
    exit_op->representation = NULL;
    exit_op->evaluate = op_t_exit_evaluate;
    return exit_op;
}