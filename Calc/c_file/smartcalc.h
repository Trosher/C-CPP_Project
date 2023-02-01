#ifndef SRC_C_FILE_SMARTCALC_H_
#define SRC_C_FILE_SMARTCALC_H_

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define isinf(x)                                                         \
    ( sizeof(x) == sizeof(float)  ? __inline_isinff((float)(x))          \
    : sizeof(x) == sizeof(double) ? __inline_isinfd((double)(x))         \
                                  : __inline_isinfl((long double)(x)))

/*
    Мдифицированый стек

    next - Указатель на следующий жлемент
    back - Указатель на предидущий элемент
    first - Указатаель на первый элемент
    value - Хранимиое значение (Если op не равен 0)
    op - Хранимый оператор
        Индексы операторов:
        1 - '+'; 2 - '-'; 3 - '/'; 4 - '*';
        5 - '^'; 6 - 'cos(x)'; 7 - 'sin(x)';
        8 - 'tan(x)'; 9 - 'acos(x)'; 10 - 'asin(x)';
        11 - 'atan(x)'; 12 - 'sqrt(x)'; 13 - 'ln(x)';
        14 - 'log(x)'; 15 - 'mod'; 16 - '('; 17 - ')';
        18 - 'x'
*/
typedef struct stack_s {
    struct stack_s *next;
    struct stack_s *back;
    struct stack_s *first;
    long double value;
    int op;
}  stack_s;


// Работа с стеком

// Создание стека
stack_s *create_stack(stack_s *res);
// Очищение стека
void destroy_stack(stack_s *stack);
// Добавление элемента в стек
stack_s *push_stack(long double value, int op, stack_s *last);
// Удаление верхнего элемента из стека
stack_s *pop(stack_s *stack);


// Вычисления

// Бинарные операторы
long double get_binary_op(int op, long double a, long double b, int *error_target);
// Унарные операторы
long double get_unary_op(int op, long double a, int *error_target);
// Я забыл что оно делает, но вроде это расчет месечного платежа
long double mes_p(long double data_k, long double sum_k, long double proc_k);
// Вычисление деференцированных платяжей
void res_CCKDD(long double data_k, long double sum_k, long double proc_k, \
                    long double *mes_plata_min, long double *mes_plata_max, long double *proc, \
                    long double *p_sim_d);
// Вычисление Аннуетентных плятжей
void res_CCKDA(long double data_k, long double sum_k, long double proc_k, \
                    long double *mes_plata, long double *proc, long double *p_sim_d);
// Вычисления по вкладам
void res_CCD(long double data_v, long double sum_v, long double proc_v, \
                    long double *proc_res, long double *sum_res);

// Проверка строки

// Пропуск и анализ функции во время проверки
void skip_fun(const char *input, int *i);
// Пропуск и анализ символа
int check_sim(const char *mas, int *i, int *breket);
// Пропуск и анализ числа
void skip_number(const char *input, int *x_pm, int *i);
// Получение длины строки
int len_mas(const char *mas);
// Проверка строки на валидность
int prov(const char *mas);
// Проверка валидности ввода суммы кредита и процента
void error_number(const char *input, int *error_target);
// Проверка валидности ввода времени кредитования
void error_number_data(const char *input, int *error_target);

// Проверка приоритета операции
int check_prior(int *i, const char *mas);
// Трансформер и расчет по польской нотации
long double pol(const char *mas, int *error_target, long double X);
// Трансформер в польскую запись
void pol_transform(stack_s *buf_stack, stack_s *pol_stack, const char *mas, long double X);
// Определение приоритета
int get_priority(int op);
// Расчет по польской натации
long double pol_calc(stack_s *buf_stack, stack_s *pol_stack, int *error_target);

#endif  // SRC_C_FILE_SMARTCALC_H_
