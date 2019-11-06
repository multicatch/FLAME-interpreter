#include "exit.h"

#include "../symbols/operator.h"
#include "print.h"
#include <stdio.h>

literal_t *op_t_exit_evaluate(struct operator *self, literal_t *acc, cst_node_t **argument) {
    print_lt(acc);
    return NULL;
}

operator_t *create_exit() {
    operator_t *exit_op = malloc(sizeof(operator_t));
    exit_op->identifier = ".";
    exit_op->representation = NULL;
    exit_op->arguments_count = 0;
    exit_op->evaluate = op_t_exit_evaluate;
    return exit_op;
}