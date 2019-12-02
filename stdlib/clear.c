#include "clear.h"

#include "../symbols/operator.h"
#include "../evaluator/evaluator.h"
#include "print.h"
#include <stdio.h>

literal_t *op_t_clear_evaluate(struct operator *self, literal_t *acc, cst_node_t **argument) {
    print_lt(acc);
    return create_literal(LT_LONG);
}

operator_t *create_clear() {
    operator_t *clear_op = malloc(sizeof(operator_t));
    clear_op->identifier = ".";
    clear_op->representation = NULL;
    clear_op->arguments_count = 0;
    clear_op->evaluate = op_t_clear_evaluate;
    return clear_op;
}