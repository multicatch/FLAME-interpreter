#include "evaluator.h"
#include <string.h>
#include <stdio.h>
#include "../symbols/operator.h"

literal_t *convert_literal(cst_node_t *node) {
    if (node->type == CST_STR) {
        literal_t *literal = create_literal(LT_STRING);
        literal->string_length = strlen(node->value);
        free(literal->string_literal);
        literal->string_literal = malloc(literal->string_length * sizeof(char));
        strcpy(literal->string_literal, node->value);
        return literal;
    }

    if (node->type == CST_NUM) {
        if (strchr(node->value, '.') != NULL) {
            literal_t *literal = create_literal(LT_DOUBLE);
            literal->double_value = strtold(node->value, (char **) NULL);
            return literal;
        } else {
            literal_t *literal = create_literal(LT_LONG);
            literal->long_value = strtoll(node->value, (char **) NULL, 10);
            return literal;
        }
    }

    printf("Warning: \"%s\" not recognized as any literal", node->value);
    return create_literal(LT_LONG);
}

literal_t *evaluate(cst_node_t *root) {
    literal_t *result = create_literal(LT_LONG);

    for (size_t i = 0; i < root->children_length; i++) {
        if (root->children[i]->type == CST_STR || root->children[i]->type == CST_NUM) {
            free(result);
            result = convert_literal(root->children[i]);
        }
        if (root->children[i]->type == CST_EXP) {
            free(result);
            result = evaluate(root->children[i]);
        }
        if (root->children[i]->type == CST_OP) {
            char *operator_identifier = root->children[i]->value;
            operator_t *operator = get_operator(operator_identifier);
            i += 1;
            if (operator == NULL) {
                printf("Error: \"%s\" is an unknown symbol\n", operator_identifier);
            } else {
                literal_t *old_result = result;
                result = operator->evaluate(operator, result, root->children[i]);
                free(old_result);
            }
        }
    }

    return result;
}