#include "parse.h"
#include <string.h>
#include <stdio.h>

void cst_t_add_child(struct cst_node *self, struct cst_node *node) {
    if (node == NULL) {
        return;
    }

    const size_t length = self->children_length;
    cst_node_t **children = malloc((length + 1) * sizeof(cst_node_t*));
    for (size_t i = 0; i < length; i++) {
        children[i] = self->children[i];
    }
    children[length] = node;
    free(self->children);
    self->children = children;
    self->children_length = length + 1;
}

struct cst_node *cst_t_remove_last(struct cst_node *self) {
    if (self->children_length == 0) {
        return NULL;
    }

    self->children_length = self->children_length - 1;
    return self->children[self->children_length];
}

cst_node_t *create_cst_node(enum ConcreteSyntaxType type) {
    cst_node_t *result = malloc(sizeof(cst_node_t));
    result->parent = NULL;
    result->value = NULL;
    result->type = type;
    result->children_length = 0;
    result->children = malloc(result->children_length * sizeof(cst_node_t*));
    result->add_child = cst_t_add_child;
    result->remove_last = cst_t_remove_last;
    return result;
}

int is_blank(char c) {
    return c <= ' ';
}

int is_numeric(char c) {
    return c >= '0' && c <= '9';
}

int is_buf_complete(char *buffer, char c) {
    return strlen(buffer) > 0 && is_blank(c);
}

enum ConcreteSyntaxType type_of(char *raw) {
    if (is_blank(raw[0])) {
        return CST_NONE;
    }

    if (is_numeric(raw[0])) {
        return CST_NUM;
    }
    
    if (raw[0] == '"') {
        return CST_STR;
    }

    return CST_OP;
}

int is_starting_bound(char raw) {
    return raw == '(';
}

int is_ending_bound(char raw) {
    return raw == ')';
}

cst_node_t *start_subexp(cst_node_t *current) {
    cst_node_t *node = create_cst_node(CST_EXP);
    node->parent = current;
    current->add_child(current, node);
    return node;
}

int is_last_op(cst_node_t *current) {
    return current->children_length > 1 && current->children[current->children_length - 1]->type == CST_OP;
}

cst_node_t *parse(char *s_raw) {
    size_t length = strlen(s_raw);
    
    cst_node_t *root = create_cst_node(CST_EXP);
    cst_node_t *current = root;
    size_t buffer_length = 1;
    char *buffer = malloc(buffer_length * sizeof(char));
    buffer[0] = '\0';
    
    for (size_t i = 0; i <= length; i++) {
        char c = s_raw[i];
        
        if (is_starting_bound(c)) {
            current = start_subexp(current);
        } else if (is_ending_bound(c)) {
            if (current->parent != NULL) {
                current = current->parent;
            } else {
                printf("ERROR: Redundant end of expression at %zu\n", i);
                return NULL;
            }
        } else if (is_buf_complete(buffer, c) && type_of(buffer) != CST_NONE) {
            enum ConcreteSyntaxType type = type_of(buffer);

            cst_node_t *current_parent = current;

            if (type == CST_OP && is_last_op(current_parent)) {
                current = start_subexp(current);
                current_parent = current;
            } else if (type == CST_OP) {
                cst_node_t *last = current->remove_last(current);
                current = start_subexp(current);
                current_parent = current;
                current_parent->add_child(current_parent, last);
            } else if (type == CST_EXP && is_last_op(current)) {
                current = current->parent;
            }

            cst_node_t *node = create_cst_node(type);
            node->parent = current_parent;
            node->value = malloc(buffer_length * sizeof(char));
            strcpy(node->value, buffer);
            current_parent->add_child(current_parent, node);

            free(buffer);
            buffer_length = 1;
            buffer = malloc(buffer_length * sizeof(char));
            buffer[0] = '\0';

        } else if (!is_blank(c)) {
            char *tmp = malloc((buffer_length + 1) * sizeof(char));
            strcpy(tmp, buffer);
            tmp[buffer_length - 1] = c;
            tmp[buffer_length] = '\0';
            free(buffer);
            buffer = tmp;
            buffer_length += 1;
        }
    }

    return root;
}