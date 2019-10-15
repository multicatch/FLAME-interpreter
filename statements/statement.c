#include "statement.h"
#include <string.h>
#include "print.h"

statement_t *parse_statement(char *raw) {
    size_t statements_length = 1;
    statement_t **statements = malloc(statements_length * sizeof(statement_t));
    statements[0] = create_print_statement();

    size_t result = -1;

    for (size_t i = 0; i < statements_length; i++) {
        if (strcmp(raw, statements[i]->symbol->identifier) == 0) {
            result = i;
        } else {
            free(statements[i]);
        }
    }

    if (result != -1) {
        for (size_t i = result + 1; i < statements_length; i++) {
            free(statements[i]);
        }

        return statements[result];
    } else {
        return NULL;
    }
}