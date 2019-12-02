#include "parse.h"
#include <string.h>
#include <stdio.h>

int is_blank(char c) {
    return c <= ' ';
}

int is_numeric(char c) {
    return c >= '0' && c <= '9';
}

int is_buf_string(char *buffer) {
    return strlen(buffer) > 0 && buffer[0] == '"';
}

int is_buf_complete(char *buffer, char c) {
    size_t buf_length = strlen(buffer);

    if (is_buf_string(buffer)) {
        return buffer[buf_length - 1] == '"' && is_blank(c);
    } else {
        return buf_length > 0 && is_blank(c);
    }
}

concrete_syntax_t type_of(char *raw) {
    if (is_blank(raw[0])) {
        return CST_NONE;
    }

    if (is_numeric(raw[0])) {
        return CST_NUM;
    }

    if (raw[0] == '"') {
        return CST_STR;
    }

    return CST_OP;
}

int is_starting_bound(char raw) {
    return raw == '(';
}

int is_ending_bound(char raw) {
    return raw == ')';
}

cst_node_t *start_subexp(cst_node_t *current) {
    cst_node_t *node = create_cst_node(CST_EXP);
    node->parent = current;
    current->add_child(current, node);
    return node;
}

char *strip_str(char *str) {
    size_t str_length = strlen(str);
    size_t start_at = 0;
    
    if (str[0] == '"') {
        str_length -= 1;
        start_at = 1;
    }
    
    if (str[str_length + start_at - 1] == '"') {
        str_length -= 1;
    }
    
    char *result = malloc((str_length + 1) * sizeof(char));
    size_t escaped_count = 0;

    for (size_t i = 0; i < str_length; i++) {
        char current_char = str[start_at + i];
        if (current_char == '\\' && i < str_length - 1 && str[start_at + i + 1] == '"') {
            current_char = '"';
            i += 1;
            escaped_count += 1;
        }
        result[i - escaped_count] = current_char;
    }
    result[str_length - escaped_count] = '\0';

    return result;
}

cst_node_t *parse(char *s_raw) {
    size_t length = strlen(s_raw);

    cst_node_t *root = create_cst_node(CST_EXP);
    cst_node_t *current = root;
    size_t buffer_length = 1;
    char *buffer = malloc(buffer_length * sizeof(char));
    buffer[0] = '\0';

    for (size_t i = 0; i <= length; i++) {
        char c = s_raw[i];

        if (is_starting_bound(c)) {
            current = start_subexp(current);
        } else if (is_ending_bound(c)) {
            if (current->parent != NULL) {
                current = current->parent;
            } else {
                printf("ERROR: Redundant end of expression at %zu\n", i);
                return NULL;
            }
        } else if (is_buf_complete(buffer, c) && type_of(buffer) != CST_NONE) {
            concrete_syntax_t type = type_of(buffer);

            cst_node_t *node = create_cst_node(type);
            node->parent = current;
            node->value = malloc(buffer_length * sizeof(char));
            strcpy(node->value, strip_str(buffer));
            current->add_child(current, node);

            free(buffer);
            buffer_length = 1;
            buffer = malloc(buffer_length * sizeof(char));
            buffer[0] = '\0';

            if (strcmp(node->value, "=") == 0) {
                current = start_subexp(current);
            }
        } else if (!is_blank(c) || is_buf_string(buffer)) {
            char *tmp = malloc((buffer_length + 1) * sizeof(char));
            strcpy(tmp, buffer);
            tmp[buffer_length - 1] = c;
            tmp[buffer_length] = '\0';
            free(buffer);
            buffer = tmp;
            buffer_length += 1;
        }
    }

    return root;
}