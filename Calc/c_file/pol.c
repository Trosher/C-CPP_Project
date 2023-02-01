#include "smartcalc.h"

int get_priority(int op) {
    int ret_v = 0;
    if (op == 1 || op == 2) {
        ret_v = 1;
    } else if (op == 3 || op == 4 || op == 6) {
        ret_v = 2;
    } else if (op == 5) {
        ret_v = 3;
    } else if (op == 16 || (op >= 7 && op <= 15))  {
        ret_v = 4;
    } else if (op == 17) {
        ret_v = 5;
    } else if (op == 19 || op == 20) {
        ret_v = 6;
    }
    return ret_v;
}

long double get_unary_op(int op, long double a, int *error_target) {
    long double result = 0;
    if (op == 7) {
        result = cosl(a);
    } else if (op == 8) {
        result = sinl(a);
    } else if (op == 9) {
        result = tanl(a);
    } else if (op == 10) {
        result = acosl(a);
    } else if (op == 11) {
        result = asinl(a);
    } else if (op == 12) {
        result = atanl(a);
    } else if (op == 13) {
        if (a < 0) {
            *error_target = 11;
        } else {
            result = sqrtl(a);
        }
    } else if (op == 14) {
        result = logl(a);
    } else if (op == 15) {
        result = log10l(a);
    } else if (op == 19) {
        result = a * -1;
    } else if (op == 20) {
        if (a < 0) {
            result = a * -1;
        } else {
            result = a;
        }
    }
    return result;
}

long double get_binary_op(int op, long double a, long double b, int *error_target) {
    long double result = 0;
    if (op == 1) {
        result = a + b;
    } else if (op == 2) {
        result = a - b;
    } else if (op == 4) {
        result = a * b;
    } else if (op == 3) {
        if (b == 0) {
            *error_target = 12;
        } else {
            result = a / b;
        }
    } else if (op == 5) {
        result = pow(a, b);
    } else if (op == 6) {
        result = fmodl(a, b);
    }
    return result;
}

int check_prior(int *i, const char *input) {
    int res = 0;
    if (input[*i] == '+') { *i += 1;
        res = 1;
    } else if (input[*i] == '-') { *i += 1;
        res = 2;
    } else if (input[*i] == '/') { *i += 1;
        res = 3;
    } else if (input[*i] == '*') { *i += 1;
        res = 4;
    } else if (input[*i] == '^') { *i += 1;
        res = 5;
    } else if (input[*i] == 'X') { *i += 1;
        res = 18;
    } else if (!strncmp(input + *i, "sin(", 4)) { *i += 4;
        res = 8;
    } else if (!strncmp(input + *i, "cos(", 4)) { *i += 4;
        res = 7;
    } else if (!strncmp(input + *i, "tan(", 4)) { *i += 4;
        res = 9;
    } else if (!strncmp(input + *i, "acos(", 5)) { *i += 5;
        res = 10;
    } else if (!strncmp(input + *i, "asin(", 5)) { *i += 5;
        res = 11;
    } else if (!strncmp(input + *i, "atan(", 5)) { *i += 5;
        res = 12;
    } else if (!strncmp(input + *i, "sqrt(", 5)) { *i += 5;
        res = 13;
    } else if (!strncmp(input + *i, "ln(", 3)) { *i += 3;
        res = 14;
    } else if (!strncmp(input + *i, "log(", 4)) { *i += 4;
        res = 15;
    } else if (!strncmp(input + *i, "mod", 3)) { *i += 3;
        res = 6;
    } else if (input[*i] == '(') { *i += 1;
        res = 16;
    } else if (input[*i] == ')') { *i += 1;
        res = 17;
    } else { res = 0; }
    return res;
}

long double pol(const char *mas, int *error_target, long double X) {
    long double res = 0;
    stack_s *buf_stack = NULL, *pol_stack = NULL;
    buf_stack = create_stack(buf_stack);
    pol_stack = create_stack(pol_stack);
    pol_transform(buf_stack, pol_stack, mas, X);
    res = pol_calc(buf_stack, pol_stack, error_target);
    destroy_stack(buf_stack);
    destroy_stack(pol_stack);
    return res;
}

long double pol_calc(stack_s *buf_stack, stack_s *pol_stack, \
                     int *error_target) {
    long double value = 0, next_p = 0;
    pol_stack = pol_stack->first;
    pol_stack = pol_stack->next;
    while (!next_p && (!*error_target || *error_target == -1)) {
        if (pol_stack->op == 0) {
            buf_stack = push_stack(pol_stack->value, 0, buf_stack);
            if (pol_stack->next != NULL) {
                pol_stack = pol_stack->next;
            } else {
                next_p = 1;
            }
        } else {
            if (pol_stack->op <= 6 || pol_stack->op == 15) {
                value = buf_stack->value;
                buf_stack = pop(buf_stack);
                buf_stack->value = get_binary_op(pol_stack->op, buf_stack->value, value, error_target);
                if (pol_stack->next != NULL) {
                    pol_stack = pol_stack->next;
                } else {
                    next_p = 1;
                }
            } else {
                buf_stack->value = get_unary_op(pol_stack->op, buf_stack->value, error_target);
                if (pol_stack->next != NULL) {
                    pol_stack = pol_stack->next;
                } else {
                    next_p = 1;
                }
            }
        }
    }
    if (!(buf_stack->value == buf_stack->value)\
       && (!*error_target || *error_target == -1)) *error_target = 13;
    if (isinf(buf_stack->value)) *error_target = 12;
    return buf_stack->value;
}

void pol_transform(stack_s *buf_stack, stack_s *pol_stack, const char *mas, long double X) {
    int i = 0, len = len_mas(mas), unar = 1;
    while (i < len) {
        int op = check_prior(&i, mas), prior = get_priority(op);
        if (prior == 1) {
            if (unar == 1) {
                buf_stack = push_stack(0, (op == 1 ? 20 : 19), buf_stack);
            } else {
                while (get_priority(buf_stack->op) >= prior && get_priority(buf_stack->op) != 4) {
                    pol_stack = push_stack(0, buf_stack->op, pol_stack);
                    buf_stack = pop(buf_stack);
                }
                buf_stack = push_stack(0, op, buf_stack);
            }
            unar = 0;
        } else if (prior == 2) {
            while (get_priority(buf_stack->op) >= prior && get_priority(buf_stack->op) != 4) {
                pol_stack = push_stack(0, buf_stack->op, pol_stack);
                buf_stack = pop(buf_stack);
            }
            buf_stack = push_stack(0, op, buf_stack);
            unar = 0;
        } else if (prior == 3) {
            while (get_priority(buf_stack->op) > prior && get_priority(buf_stack->op) != 4) {
                pol_stack = push_stack(0, buf_stack->op, pol_stack);
                buf_stack = pop(buf_stack);
            }
            buf_stack = push_stack(0, op, buf_stack);
            unar = 0;
        } else if (prior == 4) {
            buf_stack = push_stack(0, op, buf_stack);
            unar = 1;
        } else if (prior == 5) {
            while (get_priority(buf_stack->op) != 4) {
                pol_stack = push_stack(0, buf_stack->op, pol_stack);
                buf_stack = pop(buf_stack);
            }
            if ((buf_stack->op >= 7 && buf_stack->op <= 15) || buf_stack->op == 18) {
               pol_stack = push_stack(0, buf_stack->op, pol_stack);
            }
            buf_stack = pop(buf_stack);
            unar = 0;
        } else if (prior == 6) {
            buf_stack = push_stack(0, op, buf_stack);
            unar = 0;
        } else if (op == 18) {
            pol_stack = push_stack(X, 0, pol_stack);
            unar = 0;
        } else if (mas[i] >= '0' && mas[i] <= '9') {
            long double value = 0;
            value = atof(mas + i);
            pol_stack = push_stack(value, 0, pol_stack);
            while ((mas[i] >= '0' && mas[i] <= '9') || (mas[i] == '.'))
                i++;
            unar = 0;
        }
    }
    while (buf_stack->back) { pol_stack = push_stack(0, buf_stack->op, pol_stack);
        buf_stack = pop(buf_stack);
    }
}
