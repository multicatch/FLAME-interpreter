#include "cst.h"

#include <string.h>

void cst_t_add_child(struct cst_node *self, struct cst_node *node) {
    if (node == NULL) {
        return;
    }

    const size_t length = self->children_length;
    cst_node_t **children = malloc((length + 1) * sizeof(cst_node_t *));
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

cst_node_t *create_cst_node(concrete_syntax_t type) {
    cst_node_t *result = malloc(sizeof(cst_node_t));
    result->parent = NULL;
    result->value = NULL;
    result->type = type;
    result->children_length = 0;
    result->children = malloc(result->children_length * sizeof(cst_node_t *));
    result->add_child = cst_t_add_child;
    result->remove_last = cst_t_remove_last;
    return result;
}

cst_node_t *clone_cst(cst_node_t *original) {
    cst_node_t *node = create_cst_node(original->type);
    node->parent = original->parent;
    if (node->value != NULL) {
        node->value = malloc((strlen(original->value) + 1) * sizeof(char));
        strcpy(node->value, original->value);
    }
    node->children_length = original->children_length;
    node->children = malloc(node->children_length * sizeof(cst_node_t *));
    for (size_t i = 0; i < node->children_length; i++) {
        node->children[i] = original->children[i];
    }
    return node;
}

void *free_cst(cst_node_t *node) {
    if (node->value != NULL) {
        free(node->value);
    }
    free(node->children);
    free(node);

    return 0;
}