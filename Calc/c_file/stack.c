#include "smartcalc.h"

void destroy_stack(stack_s *stack) {
    stack = stack -> first;
    while (stack != NULL) {
        stack_s *p = stack;
        stack =  stack->next;
        free(p);
    }
}

stack_s *create_stack(stack_s *res) {
    res = (stack_s*)malloc(sizeof(stack_s));
    if (res != NULL) {
        res->back = NULL;
        res->next = NULL;
        res->first = res;
        res->value = 0;
        res->op = -1;
    }
    return res;
}

stack_s *push_stack(long double value, int op, stack_s *last) {
    stack_s *res = (stack_s*)malloc(sizeof(stack_s));
    if (res != NULL) {
        res->back = last;
        res->first = last->first;
        res->next = NULL;
        res->value = value;
        res->op = op;
        last->next = res;
    }
    return res;
}

stack_s *pop(stack_s *stack) {
    if (stack->back == NULL) {
        destroy_stack(stack);
        return NULL;
    } else {
        stack_s *p = stack;
        stack = stack->back;
        stack->next = NULL;
        free(p);
    }
    return stack;
}
