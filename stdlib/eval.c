#include "eval.h"

#include "../evaluator/evaluator.h"
#include "../utils/type.h"
#include <stdio.h>

literal_t *op_t_eval_evaluate(struct operator *self, literal_t *acc, cst_node_t **argument) {
    literal_t *result = create_literal(LT_LONG);

    literal_t *zero = create_literal(LT_STRING);
    literal_t *file_path = cast(evaluate(argument[0], zero), LT_STRING);
    free(zero);

    FILE *file = fopen(file_path->string_literal, "r");
    char *line = NULL;
    size_t len = 0;

    if (file == NULL) {
        printf("ERROR: Cannot read %s\n", file_path->string_literal);
        return result;
    }

    while ((getline(&line, &len, file)) != -1) {
        cst_node_t *tree = parse(line);
        literal_t *new_result = evaluate(tree, result);
        free(result);
        result = new_result;
        free(line);
        line = NULL;
    }

    fclose(file);

    return result;
}

operator_t *create_eval() {
    operator_t *clear_op = malloc(sizeof(operator_t));
    clear_op->identifier = "eval";
    clear_op->representation = NULL;
    clear_op->arguments_count = 1;
    clear_op->evaluate = op_t_eval_evaluate;
    return clear_op;
}
