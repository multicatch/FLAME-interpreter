#ifndef INTERPRETER_AST_H
#define INTERPRETER_AST_H

#include <stdlib.h>
#include "statements/statement.h"
#include "symbols/literal.h"
#include "symbols/symbol.h"

typedef struct ast_node {
    statement_t *statement;
    literal_t *literal;

    struct ast_node **children;
    size_t children_length;

    void (*add_child)(struct ast_node *, struct ast_node *);
} ast_node_t;

ast_node_t *parse(const char *, size_t);

#endif //INTERPRETER_AST_H
