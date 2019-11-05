#ifndef INTERPRETER_REPOSITORY_H
#define INTERPRETER_REPOSITORY_H

#include "../parse/parse.h"
#include "operator.h"

typedef struct repository_entry {
    operator_t *op;

    struct repository_entry *previous;
    struct repository_entry *next;
} repository_entry_t;

void init_repo();
repository_entry_t *get_operator_from_repo(const char *);
void insert_into_repo(const char *, cst_node_t *);
void insert_operator_into_repo(operator_t *);

#endif //INTERPRETER_REPOSITORY_H
