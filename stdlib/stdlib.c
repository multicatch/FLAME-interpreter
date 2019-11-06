#include "stdlib.h"

#include "print.h"
#include "exit.h"
#include "clear.h"
#include "add.h"

void insert_stdlib_using(void (*insert_function)(operator_t *)) {
    insert_function(create_print());
    insert_function(create_exit());
    insert_function(create_clear());
    insert_function(create_add());
}