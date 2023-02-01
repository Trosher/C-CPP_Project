#include "smartcalc.h"

void error_number(const char *input, int *error_target) {
    int dot_readed = 0, dot_caunt = -1, i = 0;
    while ((input[i] >= '0' && input[i] <= '9') || (input[i] == '.' && !dot_readed)) {
        if (input[i] == '.') dot_readed = 1;
        if (dot_readed) dot_caunt += 1;
        i += 1;
    }
    if (!input[0]) *error_target = 4;
    if ((dot_readed && input[i] == '.') || dot_caunt > 2) *error_target = 1;
    if (!(*error_target) && input[i]) *error_target = 2;
}

void error_number_data(const char *input, int *error_target) {
    int i = 0;
    while (input[i] >= '0' && input[i] <= '9') {
        i += 1;
    }
    if (!input[0]) *error_target = 4;
    if (input[i])* error_target = 3;
}

void skip_fun(const char *mas, int *i) {
    if (!strncmp(mas + *i, "sin(", 4)) { *i += 2;
    } else if (!strncmp(mas + *i, "cos(", 4)) { *i += 2;
    } else if (!strncmp(mas + *i, "tan(", 4)) { *i += 2;
    } else if (!strncmp(mas + *i, "acos(", 5)) { *i += 3;
    } else if (!strncmp(mas + *i, "asin(", 5)) { *i += 3;
    } else if (!strncmp(mas + *i, "atan(", 5)) { *i += 3;
    } else if (!strncmp(mas + *i, "sqrt(", 5)) { *i += 3;
    } else if (!strncmp(mas + *i, "ln(", 3)) { *i += 1;
    } else if (!strncmp(mas + *i, "log(", 4)) { *i += 2;
    } else if (!strncmp(mas + *i, "mod", 3)) { *i += 2;
    } else { *i = -1; }
}

int check_sim(const char *mas, int *i, int *breket) {
    int error_target = 0;
    if (mas[*i] == '.') { error_target = 1;
    } else if (mas[*i] == '(') {
        *i += 1;
        if (mas[*i] == ')') {
            error_target = 2;
        } else { *breket += 1; }
    } else if (mas[*i] == ')') {
        *i += 1;
        if (mas[*i] == '(' || mas[*i] == 'c' || mas[*i] == 's' || mas[*i] == 't'\
            || mas[*i] == 'a' || mas[*i] == 'l') {
            error_target = 2;
        } else { *breket -= 1; }
    } else if (mas[*i] == '+' || mas[*i] == '-') {
        *i += 1;
        if (!(mas[*i] >= '0' && mas[*i] <= '9') && mas[*i] != 'X' && mas[*i] != '(') {
            if (mas[*i] != 'c' && mas[*i] != 's' && mas[*i] != 't'\
                && mas[*i] != 'a' && mas[*i] != 'l') {
                    error_target = 3;
            }
        }
    } else if (mas[*i] == '*' || mas[*i] == '/') {
        *i += 1;
        if (!(mas[*i] >= '0' && mas[*i] <= '9') && mas[*i] != 'X' && mas[*i] != '(') {
            if (mas[*i] != 'c' && mas[*i] != 's' && mas[*i] != 't'\
                && mas[*i] != 'a' && mas[*i] != 'l') {
                   error_target = 4;
            }
        }
    } else if (mas[*i] == '^') {
        *i += 1;
        if (!(mas[*i] >= '0' && mas[*i] <= '9') && mas[*i] != 'X' && mas[*i] != '(') {
            if (mas[*i] != 'c' && mas[*i] != 's' && mas[*i] != 't'\
                && mas[*i] != 'a' && mas[*i] != 'l') {
                   error_target = 5;
                }
        }
    } else { error_target = 6; }
    *i -= 1;
    return error_target;
}

void skip_number(const char *input, int *x_p, int *i) {
    int dot_readed = 0;
    if (input[*i] != 'X') {
        while ((input[*i] >= '0' && input[*i] <= '9') || (input[*i] == '.' && !dot_readed)) {
            if (input[*i] == '.') dot_readed = 1;
            *i += 1;
        }
    } else {
        *x_p = 1;
        *i += 1;
        if (input[*i] == '.' || (input[*i] >= '0' && input[*i] <= '9')) dot_readed = -1;
    }
    if (dot_readed != -1 && (dot_readed && input[*i] == '.'))  *i = -1;
    if (input[*i] == '(' || input[*i] == 'X' || dot_readed == -1) *i = -1;
    if (input[*i] == 'c' || input[*i] == 's' || input[*i] == 't'\
        || input[*i] == 'a' || input[*i] == 'l') *i = -1;
    *i -= 1;
}

int len_mas(const char *mas) {
    int len = 0;
    for (int i = 1; mas[i - 1] != '\0'; i++)
        len = i;
    return len;
}

int prov(const char *mas) {
    int error_target = 0, len = len_mas(mas), breket = 0, x_p = 0;
    if (!mas[0]) error_target = 14;
    for (int i = 0; i < len && !error_target; i++) {
        if ((mas[i] >= '0' && mas[i] <= '9') || mas[i] == 'X') {
            skip_number(mas, &x_p, &i);
            if (i < 0) error_target = 7;
        } else if ((mas[i] >= '(' && mas[i] <= '/') || mas[i] == '^') {
            error_target = check_sim(mas, &i, &breket);
        } else if (mas[i] == 'c' || mas[i] == 's' || mas[i] == 't'\
                || mas[i] == 'a' || mas[i] == 'l' || mas[i] == 'm') {
            skip_fun(mas, &i);
            if (i < 0) error_target = 8;
        } else {
            error_target = 9;
        }
    }
    if (breket != 0 && !error_target) error_target = 10;
    if (!error_target && x_p == 1) error_target = -1;
    return error_target;
}
