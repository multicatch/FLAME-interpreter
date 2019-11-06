#include "add.h"

#include "../symbols/operator.h"
#include "../evaluator/evaluator.h"
#include "../utils/type.h"
#include <stdio.h>
#include <string.h>

literal_t *lt_add(literal_t *a, literal_t *b) {
    literal_t *result = lt_clone(a);
    literal_t *casted_b = cast(b, a->type);

    result->long_value += casted_b->long_value;
    result->double_value += casted_b->double_value;

    char *original = result->string_literal;
    result->string_literal = malloc((a->string_length + b->string_length) * sizeof(char));
    strcpy(result->string_literal, original);
    strcpy(result->string_literal + a->string_length, b->string_literal);
    result->string_length = a->string_length + b->string_length;

    return result;
}

literal_t *op_t_add_evaluate(struct operator *self, literal_t *acc, cst_node_t **argument) {
    literal_t *result = lt_clone(acc);

    literal_t *old = result;
    literal_t *zero = create_literal(LT_LONG);
    literal_t *b = evaluate(argument[0], zero);
    free(zero);
    result = lt_add(result, b);
    free(old);
    
    return result;
}

operator_t *create_add() {
    operator_t *add_op = malloc(sizeof(operator_t));
    add_op->identifier = "+";
    add_op->representation = NULL;
    add_op->arguments_count = 1;
    add_op->evaluate = op_t_add_evaluate;
    return add_op;
}