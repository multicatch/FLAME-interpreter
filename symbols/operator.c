#include "operator.h"
#include <stdio.h>
#include <string.h>
#include "../evaluator/evaluator.h"
#include "../utils/type.h"

cst_node_t *replace_arguments(cst_node_t *node, char **argument_identifiers, literal_t **arguments, size_t argument_count) {
    cst_node_t *result = create_cst_node(node->type);
    result->value = node->value;
    if (node->type == CST_OP) {
        size_t arg_id = 0;
        for (; arg_id < argument_count && strcmp(node->value, argument_identifiers[arg_id]) != 0; arg_id++);

        if (arg_id < argument_count) {
            if (arguments[arg_id]->type == LT_STRING) {
                result->type = CST_STR;
                result->value = arguments[arg_id]->string_literal;
            } else {
                result->type = CST_NUM;
                result->value = cast(arguments[arg_id], LT_STRING)->string_literal;
            }
        }
    }

    for (size_t child_i = 0; child_i < node->children_length; child_i++) {
        result->add_child(result, replace_arguments(node->children[child_i], argument_identifiers, arguments, argument_count));
    }

    return result;
}

literal_t *generic_operator_t_evaluate(struct operator *operator, literal_t *prefix, cst_node_t **arguments) {
    literal_t **literal_arguments = malloc(operator->arguments_count * sizeof(literal_t));
    char **argument_identifiers = malloc(operator->arguments_count * sizeof(char*));
    for (size_t arg_i = 0; arg_i < operator->arguments_count; arg_i++) {
        literal_arguments[arg_i] = evaluate(arguments[arg_i], prefix);
        argument_identifiers[arg_i] = operator->arguments[arg_i]->value;
    }

    cst_node_t *representation = replace_arguments(operator->representation, argument_identifiers, literal_arguments, operator->arguments_count);

    return evaluate(representation, prefix);
}

operator_t *create_operator(const char *identifier) {
    operator_t *result = malloc(sizeof(operator_t));
    result->identifier = malloc(strlen(identifier) * sizeof(char));
    strcpy(result->identifier, identifier);
    result->arguments_count = 0;
    result->evaluate = generic_operator_t_evaluate;
    return result;
}
