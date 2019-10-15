#include <string.h>
#include "ast.h"

void ast_node_t_add_child(struct ast_node *self, struct ast_node *ast_node) {
    size_t length = self->children_length;
    ast_node_t **children = malloc((length + 1) * sizeof(ast_node_t *));
    for (size_t i = 0; i < length; i++) {
        children[i] = self->children[i];
    }
    children[length] = ast_node;
    self->children = children;
    self->children_length += 1;
}

ast_node_t *create_ast_node() {
    ast_node_t *result = malloc(sizeof(ast_node_t));
    result->statement = NULL;
    result->literal = NULL;
    result->children_length = 0;
    result->children = malloc(result->children_length * sizeof(ast_node_t *));
    result->add_child = ast_node_t_add_child;
    return result;
}

ast_node_t *parse(const char *line, size_t line_length) {
    size_t current_length = 1;
    char *result = malloc(current_length);
    result[0] = '\0';
    char is_literal = 0;
    char string_literal = 0;

    ast_node_t *root = create_ast_node();
    ast_node_t *current = root;

    for (size_t i = 0; i < line_length; i++) {
        if (current_length == 1 && ((line[i] >= '0' && line[i] <= '9') || line[i] == '"')) {
            is_literal = 1;
            string_literal = line[i] == '"';
            continue;
        }

        if ((line[i] != ' ' || (is_literal && string_literal)) && !(is_literal && line[i] == '"')) {
            char *statement = malloc(current_length + 1);
            strcpy(statement, result);
            statement[current_length - 1] = (char) line[i];
            statement[current_length] = '\0';
            current_length += 1;
            free(result);
            result = statement;
        } else {
            ast_node_t *node = create_ast_node();

            if (is_literal) {
                literal_t *literal = create_string(result);
                node->literal = literal;
                current->add_child(current, node);
            } else {
                statement_t *statement = parse_statement(result);
                node->statement = statement;
                current->add_child(current, node);
                current = node;
            }

            free(result);
            is_literal = 0;
            string_literal = 0;
            current_length = 1;
            result = malloc(current_length);
            result[0] = '\0';
        }
    }

    return root;
}