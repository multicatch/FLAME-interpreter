#include "stdlib.h"

#include "print.h"
#include "exit.h"

void insert_stdlib_using(void (*insert_function)(operator_t *)) {
    insert_function(create_print());
    insert_function(create_exit());
}