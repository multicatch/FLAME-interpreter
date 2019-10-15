#include "evaluator.h"

void evaluate(ast_node_t *root) {
    size_t current_index = 0;
    ast_node_t *parent = NULL;
    ast_node_t *current = root;
    statement_t *current_statement = NULL;
    while (current != NULL) {
        if (current->statement != NULL) {
            current_statement = current->statement;
        }
        if (current_statement != NULL && current->literal != NULL) {
            literal_t **arguments = malloc(sizeof(literal_t *));
            arguments[0] = current->literal;
            current_statement->evaluate(arguments, 1);
            current_statement = NULL;
        }

        if (parent != NULL) {
            if ((parent->children_length - 1) > current_index) {
                current_index += 1;
                current = parent->children[current_index];
                continue;
            }
        }

        parent = current;
        if (parent->children_length > 0) {
            current_index = 0;
            current = parent->children[current_index];
        } else {
            current = NULL;
        }
    }
}