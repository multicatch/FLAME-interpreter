#include "literal.h"
#include <string.h>

void literal_t_set_string(struct literal *self, char *value) {
    size_t length = strlen(value);
    free(self->string_literal);
    self->string_literal = malloc(length * sizeof(char));
    strcpy(self->string_literal, value);
    self->string_length = length;
}

literal_t *lt_clone(literal_t *result) {
    literal_t *new_result = create_literal(result->type);
    new_result->double_value = result->double_value;
    new_result->long_value = result->long_value;
    new_result->string_literal = result->string_literal;
    new_result->string_length = result->string_length;
    return new_result;
}

literal_t *create_literal(literal_type_t type) {
    literal_t *result = malloc(sizeof(literal_t));
    result->type = type;
    result->double_value = .0;
    result->long_value = 0;
    result->string_length = 0;
    result->string_literal = malloc((result->string_length + 1) * sizeof(char));
    result->string_literal[0] = '\0';
    result->set_string = literal_t_set_string;

    return result;
}