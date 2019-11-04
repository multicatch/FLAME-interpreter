#include "operator.h"
#include <stdio.h>
#include <string.h>
#include "../evaluator/evaluator.h"

operator_t *create_operator(char *identifier) {
    operator_t *result = malloc(sizeof(operator_t));
    result->identifier = malloc(strlen(identifier) * sizeof(char));
    strcpy(result->identifier, identifier);
    return result;
}

literal_t *print_evaluate(struct operator *self, literal_t *suffix, cst_node_t *argument) {
    literal_t *result = evaluate(argument);
    if (result->type == LT_STRING) {
        printf("%s\n", result->string_literal);
    }
    if (result->type == LT_LONG) {
        printf("%lld", result->long_value);
    }
    if (result->type == LT_DOUBLE) {
        printf("%Lf", result->double_value);
    }
    return result;
}

operator_t *get_operator(char *identifier) {
    if (strcmp(identifier, "print") == 0) {
        operator_t *result = create_operator("print");
        result->evaluate = print_evaluate;
        return result;
    }

    return NULL;
}