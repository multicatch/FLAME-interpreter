#ifndef INTERPRETER_PARSE_H
#define INTERPRETER_PARSE_H

#include <stdlib.h>

enum ConcreteSyntaxType {
    CST_NONE, CST_OP, CST_EXP, CST_NUM, CST_STR
};

typedef struct cst_node {
    struct cst_node *parent;

    enum ConcreteSyntaxType type;
    char *value;

    struct cst_node **children;
    size_t children_length;

    void (*add_child)(struct cst_node*, struct cst_node*);
    struct cst_node *(*remove_last)(struct cst_node*);
} cst_node_t;

cst_node_t *parse(char *);

#endif //INTERPRETER_PARSE_H
