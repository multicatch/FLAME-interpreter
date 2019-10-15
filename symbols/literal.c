#include "literal.h"
#include <string.h>

literal_t *create_string(char *literal) {
    literal_t *result = malloc(sizeof(literal_t));
    result->type = STRING_T;
    result->double_value = 0;
    result->long_value = 0;

    size_t literal_length = 0;
    for (literal_length = 0; literal[literal_length] != '\0'; literal_length++);
    char *literal_value = malloc((literal_length + 1) * sizeof(char));

    strcpy(literal_value, literal);

    result->string_value = literal_value;
    result->string_length = literal_length;

    return result;
}