#include "type.h"

#include <string.h>
#include <stdio.h>

void clear_string(literal_t *result) {
    free(result->string_literal);
    result->string_length = 0;
    result->string_literal = malloc(1);
    result->string_literal[0] = '\0';
}

literal_t *cast(literal_t *literal, literal_type_t type) {
    literal_t *result = lt_clone(literal);

    if (literal->type == type) {
        return result;
    }

    if (literal->type == LT_STRING && type == LT_LONG) {
        result->long_value = strtoll(literal->string_literal, (char **) NULL, 10);
        clear_string(result);
        return result;
    }

    if (literal->type == LT_STRING && type == LT_DOUBLE) {
        result->double_value = strtold(literal->string_literal, (char **) NULL);
        clear_string(result);
        return result;
    }

    if (literal->type == LT_LONG && type == LT_DOUBLE) {
        result->double_value = (long double) 1.0 * result->long_value;
        result->long_value = 0;
        return result;
    }

    if (literal->type == LT_DOUBLE && type == LT_LONG) {
        result->long_value = (long long) 1L * result->double_value;
        result->double_value = 0;
        return result;
    }

    // TODO: Cast into string
    return result;
}