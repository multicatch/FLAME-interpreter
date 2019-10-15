#ifndef INTERPRETER_STATEMENT_H
#define INTERPRETER_STATEMENT_H

#include "../symbols/symbol.h"
#include "../symbols/literal.h"

typedef struct statement {
    symbol_t *symbol;
    size_t argument_count;

    void (*evaluate)(literal_t **, size_t);
} statement_t;

statement_t *parse_statement(char *);

#endif //INTERPRETER_STATEMENT_H
