#ifndef INTERPRETER_EVALUATOR_H
#define INTERPRETER_EVALUATOR_H

#include "../parse/parse.h"
#include "../symbols/literal.h"

literal_t *evaluate(cst_node_t *);

#endif //INTERPRETER_EVALUATOR_H
