#ifndef INTERPRETER_PARSE_H
#define INTERPRETER_PARSE_H

#include <stdlib.h>

typedef enum concrete_syntax_type {
    CST_NONE, CST_OP, CST_EXP, CST_NUM, CST_STR
} concrete_syntax_t;

typedef struct cst_node {
    struct cst_node *parent;

    concrete_syntax_t type;
    char *value;

    struct cst_node **children;
    size_t children_length;

    void (*add_child)(struct cst_node*, struct cst_node*);
    struct cst_node *(*remove_last)(struct cst_node*);
} cst_node_t;

cst_node_t *parse(char *);

#endif //INTERPRETER_PARSE_H
