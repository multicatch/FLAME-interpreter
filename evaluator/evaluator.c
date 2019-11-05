#include "evaluator.h"
#include <string.h>
#include <stdio.h>
#include "../symbols/repository.h"
#include "../stdlib/stdlib.h"

literal_t *convert_literal(cst_node_t *node, literal_t *acc) {
    if (node->type == CST_STR) {
        literal_t *literal = create_literal(LT_STRING);
        literal->string_length = strlen(node->value);
        free(literal->string_literal);
        literal->string_literal = malloc(literal->string_length * sizeof(char));
        strcpy(literal->string_literal, node->value);
        free(acc);
        return literal;
    }

    if (node->type == CST_NUM) {
        if (strchr(node->value, '.') != NULL) {
            literal_t *literal = create_literal(LT_DOUBLE);
            literal->double_value = strtold(node->value, (char **) NULL);
            free(acc);
            return literal;
        } else {
            literal_t *literal = create_literal(LT_LONG);
            literal->long_value = strtoll(node->value, (char **) NULL, 10);
            free(acc);
            return literal;
        }
    }

    printf("Warning: \"%s\" not recognized as any literal", node->value);
    return create_literal(LT_LONG);
}

void init_evaluator() {
    init_repo();
    insert_stdlib_using(insert_operator_into_repo);
}

literal_t *evaluate(cst_node_t *root, literal_t *acc) {
    literal_t *result = acc;
    
    for (size_t i = 0; i < root->children_length; i++) {
        literal_t *old_result = result;
        if (root->children[i]->type == CST_STR || root->children[i]->type == CST_NUM) {
            result = convert_literal(root->children[i], old_result);
        }
        if (root->children[i]->type == CST_EXP) {
            result = evaluate(root->children[i], old_result);
        }
        if (root->children[i]->type == CST_OP) {
            char *operator_identifier = root->children[i]->value;
            repository_entry_t *entry = get_operator_from_repo(operator_identifier);
            i += 1;
            if (entry == NULL) {
                insert_into_repo(operator_identifier, root->children[i]);
            } else {
                operator_t *op = entry->op;
                result = op->evaluate(op, old_result, root->children[i]);
            }
        }
    }

    if (result != NULL) {
        literal_t *new_result = lt_clone(result);
        free(result);
        return new_result;
    } else {
        return create_literal(LT_LONG);
    }
}