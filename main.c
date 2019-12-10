#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parse.h"
#include "evaluator/evaluator.h"
#include "utils/logger.h"

int main() {
    init_evaluator();
    literal_t *result = create_literal(LT_LONG);
    size_t line_number = 1;

    while (result != NULL) {
        size_t current_length = 0;
        char *line = malloc(current_length);
        int c;

        while ((c = getchar()) != '\n') {
            char *statement = malloc(current_length + 2);
            strcpy(statement, line);
            statement[current_length] = (char) c;
            statement[current_length + 1] = '\0';
            current_length += 1;
            free(line);
            line = statement;
        }

        set_line("stdin", line_number);
        cst_node_t *tree = parse(line);
        literal_t *new_result = evaluate(tree, result);
        free(result);
        result = new_result;
        line_number += 1;
    }

    return 0;
}