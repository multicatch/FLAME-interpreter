#include "evaluator.h"
#include <string.h>
#include <stdio.h>
#include "../symbols/repository.h"
#include "../stdlib/stdlib.h"
#include "../utils/logger.h"

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

    warn(MSG_WRONG_TYPE, node->value);
    return create_literal(LT_LONG);
}

void init_evaluator() {
    init_repo();
    insert_stdlib_using(insert_operator_into_repo);
}

int is_equals(cst_node_t *node) {
    return node != NULL && node->type == CST_OP && strcmp(node->value, "=") == 0;
}

size_t collect_and_define(char *operator_identifier, cst_node_t *node, size_t current_child_i) {
    size_t arguments_count = 0;
    cst_node_t **arguments = malloc(arguments_count * sizeof(cst_node_t *));
    for (size_t j = 1; current_child_i + j < node->children_length && !is_equals(node->children[current_child_i + j]); j++) {
        arguments_count += 1;
        cst_node_t **tmp = malloc(arguments_count * sizeof(cst_node_t *));
        for (size_t old_arg = 0; old_arg < arguments_count - 1; old_arg++) {
            tmp[old_arg] = arguments[old_arg];
        }
        tmp[arguments_count - 1] = node->children[current_child_i + j];
        free(arguments);
        arguments = tmp;
    }
    current_child_i += arguments_count + 2;
    if (!is_equals(node->children[current_child_i - 1])) {
        warn(MSG_UNDECLARED, operator_identifier);
    } else {
        cst_node_t *representation = node->children[current_child_i];
        insert_into_repo(operator_identifier, arguments, arguments_count, representation);
    }

    return current_child_i;
}

// TODO: refactor
literal_t *evaluate(cst_node_t *root, literal_t *acc) {
    literal_t *result = lt_clone(acc);
    cst_node_t *node = clone_cst(root);

    if (node->children_length == 0 && node->type != CST_EXP) {
        node->add_child(node, root);
    }
    
    for (size_t i = 0; i < node->children_length; i++) {
        literal_t *old_result = result;
        if (node->children[i]->type == CST_STR || node->children[i]->type == CST_NUM) {
            result = convert_literal(node->children[i], old_result);
        }
        if (node->children[i]->type == CST_EXP) {
            result = evaluate(node->children[i], old_result);
        }
        if (node->children[i]->type == CST_OP) {
            char *operator_identifier = node->children[i]->value;
            repository_entry_t *entry = get_operator_from_repo(operator_identifier);
            if (entry == NULL) {
                i = collect_and_define(operator_identifier, node, i);
            } else {
                operator_t *op = entry->op;
                cst_node_t **arguments = malloc(op->arguments_count * sizeof(cst_node_t*));
                for (size_t j = 0; j < op->arguments_count; j++) {
                    arguments[j] = node->children[i + j + 1];
                }
                if (node->children_length > (i + op->arguments_count + 1) && is_equals(node->children[i + op->arguments_count + 1])) {
                    warn(MSG_REDECLARATION, operator_identifier);
                    i = collect_and_define(operator_identifier, node, i);
                } else {
                    i += op->arguments_count;
                    result = op->evaluate(op, old_result, arguments);
                }
            }
        }
    }

    free_cst(node);

    if (result != NULL) {
        return result;
    } else {
        return NULL;
    }
}