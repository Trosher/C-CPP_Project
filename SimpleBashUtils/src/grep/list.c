#include "s21_grep.h"

void destroy(struct node* root) {
    while (root != NULL) {
        struct node *p = root;
        root = root -> next;
        free(p);
    }
}

struct node *init() {
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    if (tmp != NULL) {
        tmp -> value = NULL;
        tmp -> next = NULL;
        tmp -> start = tmp;
    }
    return tmp;
}

struct node *add_list(struct node* elem, const char* value1) {
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    if (tmp != NULL) {
        tmp -> value = value1;
        tmp -> next = elem -> next;
        tmp -> start = elem -> start;
        elem -> next = tmp;
    }
    return tmp;
}

