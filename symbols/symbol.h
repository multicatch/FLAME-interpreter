#ifndef INTERPRETER_SYMBOL_H
#define INTERPRETER_SYMBOL_H

#include <stdlib.h>

typedef struct symbol {
    char *identifier;
    size_t identifier_length;
} symbol_t;

#endif //INTERPRETER_SYMBOL_H
