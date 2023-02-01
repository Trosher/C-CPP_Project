#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <getopt.h>

#ifndef s21_NULL
#define s21_NULL ((void*)0)
#endif

struct node {
    const char *value;
    struct node *next;
    struct node *start;
};

struct node *init();
struct node *add_list(struct node *elem, const char *value1);
void destroy(struct node *root);

#endif  // SRC_GREP_S21_GREP_H_
