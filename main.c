#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parse.h"

int main() {
    int current_length = 0;
    char *line = malloc((size_t) current_length);
    int c;

    while ((c = getchar()) != '\n') {
        char *statement = malloc((size_t) current_length + 1);
        strcpy(statement, line);
        statement[current_length] = (char) c;
        statement[current_length + 1] = '\0';
        current_length += 1;
        free(line);
        line = statement;
    }

    cst_node_t *pNode = parse(line);

    return 0;
}