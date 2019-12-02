#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const size_t OP_T_SLICES = 256;
repository_entry_t **op_t_repository;

unsigned long int djb2(const char *str) {
    unsigned long int hash = 5381;

    for (size_t i = 0; str[i] != 0; i++) {
        hash = ((hash << 5) + hash) + str[i];
    }

    return hash;
}

repository_entry_t *create_repository_entry(operator_t *operator) {
    repository_entry_t *result = malloc(sizeof(repository_entry_t));
    result->op = operator;
    result->next = NULL;
    result->previous = NULL;
    return result;
}

void init_repo() {
    op_t_repository = malloc(OP_T_SLICES * sizeof(repository_entry_t *));
    for (size_t i = 0; i < OP_T_SLICES; i++) {
        op_t_repository[i] = NULL;
    }
}

repository_entry_t *get_operator_from_repo(const char *identifier) {
    unsigned long slot_index = djb2(identifier) % OP_T_SLICES;

    if (op_t_repository[slot_index] == NULL) {
        return NULL;
    }

    repository_entry_t *result = op_t_repository[slot_index];
    while (result->next != NULL && strcmp(identifier, result->op->identifier) != 0) {
        result = result->next;
    }

    if (strcmp(identifier, result->op->identifier) == 0) {
        return result;
    }
    return NULL;
}

void
insert_into_repo(const char *identifier, cst_node_t **arguments, size_t argument_count, cst_node_t *representation) {
    operator_t *result = create_operator(identifier);
    result->representation = representation;
    result->arguments_count = argument_count;
    result->arguments = arguments;

    insert_operator_into_repo(result);
}

void insert_operator_into_repo(operator_t *operator) {
    repository_entry_t *entry = get_operator_from_repo(operator->identifier);
    if (entry != NULL) {
        entry->op = operator;
    } else {
        entry = create_repository_entry(operator);

        unsigned long slot_index = djb2(operator->identifier) % OP_T_SLICES;
        if (op_t_repository[slot_index] == NULL) {
            op_t_repository[slot_index] = entry;
        } else {
            repository_entry_t *last = op_t_repository[slot_index];
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = entry;
            entry->previous = last;
        }
    }
}