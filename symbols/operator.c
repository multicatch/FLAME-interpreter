#include "operator.h"
#include <stdio.h>
#include <string.h>
#include "../evaluator/evaluator.h"

operator_t *create_operator(const char *identifier) {
    operator_t *result = malloc(sizeof(operator_t));
    result->identifier = malloc(strlen(identifier) * sizeof(char));
    strcpy(result->identifier, identifier);
    result->arguments_count = 0;
    return result;
}
