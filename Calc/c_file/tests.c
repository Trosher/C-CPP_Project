#include <string.h>
#include <stdio.h>
#include <check.h>
#include "smartcalc.h"
#define EPS 1e-7

START_TEST(Test1) {
    char *expression = {"(2+3)*5^2"};
    long double result = 0;
    int error_target = 0;
    result = pol(expression, &error_target, 0);
    ck_assert_float_eq(result, 125.0);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(Test2) {
    char *expression = {"1/2+(2+3)/(sin(9-2)^2-6/7)"};
    long double result = 0;
    int error_target = 0;
    result = pol(expression, &error_target, 0);
    ck_assert_float_eq_tol(-11.2505646, result, EPS);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(Test3) {
    char *expression = {"1/2+(2+3"};
    long double result = 0;
    int error_target = 0;
    error_target = prov(expression);
    ck_assert_int_eq(error_target == 0 ? 0 : 1, 1);
}
END_TEST

START_TEST(Test4) {
    char *expression = {"1/2+(2.3.5+3)"};
    long double result = 0;
    int error_target = 0;
    error_target = prov(expression);
    ck_assert_int_eq(error_target == 0 ? 0 : 1, 1);
}
END_TEST

START_TEST(Test5) {
    char *expression = {"**"};
    long double result = 0;
    int error_target = 0;
    error_target = prov(expression);
    ck_assert_int_eq(error_target == 0 ? 0 : 1, 1);
}
END_TEST

START_TEST(Test6) {
    char *expression = {"sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)"};
    long double result = 0;
    int error_target = 0;
    result = pol(expression, &error_target, 0);
    ck_assert_int_eq(error_target, 0);
    ck_assert_float_lt(EPS, fabs(-1.47532 - result));
}
END_TEST

START_TEST(Test7) {
    char *expression = {"123"};
    int error_target = 0;
    error_number(expression, &error_target);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(Test8) {
    char *expression = {"1asd23"};
    int error_target = 0;
    error_number(expression, &error_target);
    ck_assert_int_eq(error_target, 2);
}
END_TEST

START_TEST(Test9) {
    char *expression = {"123.12"};
    int error_target = 0;
    error_number(expression, &error_target);
    ck_assert_int_eq(error_target, 0);
}
END_TEST

START_TEST(Test10) {
    char *expression = {"sin(2)*cos(5)+tan(67^2)/sin(128)-atan(sqrt(9))-(4mod2)*log(5)"};
    long double result = 0;
    int error_target = 0;
    error_target = prov(expression);
    ck_assert_int_eq(error_target == 0 ? 0 : 1, 0);
}
END_TEST

START_TEST(Test11) {
    long double proc_k_num = 13;
    long double data_k_num = 12;
    long double sum_k_num = 20000;
    long double sum_res = 0, proc = 0;
    res_CCD(data_k_num, sum_k_num, proc_k_num, &proc, &sum_res);
    ck_assert_float_eq_tol(2760.65, proc, 1E-1);
    ck_assert_float_eq_tol(22760.7, sum_res, 1E-1);
}
END_TEST

START_TEST(Test12) {
    long double proc_k_num = 13;
    long double data_k_num = 12;
    long double sum_k_num = 20000;
    long double mes_plata = 0, proc = 0, p_sim_d = 0;
    res_CCKDA(data_k_num, sum_k_num, proc_k_num, &mes_plata, &proc, &p_sim_d);
    ck_assert_float_eq_tol(1786.35, mes_plata, 1E-1);
    ck_assert_float_eq_tol(1436.15, proc, 1E-1);
    ck_assert_float_eq_tol(21436.1, p_sim_d, 1E-1);
}
END_TEST

START_TEST(Test13) {
    long double proc_k_num = 13;
    long double data_k_num = 12;
    long double sum_k_num = 20000;
    long double mes_plata_max = 0, mes_plata_min = 0, proc = 0, p_sim_d = 0;
    res_CCKDD(data_k_num, sum_k_num, proc_k_num, &mes_plata_min, &mes_plata_max, &proc, &p_sim_d);
    ck_assert_float_eq_tol(1880.37, mes_plata_max, 1E-1);
    ck_assert_float_eq_tol(1666.67, mes_plata_min, 1E-1);
    ck_assert_float_eq_tol(1389.04, proc, 1E-1);
    ck_assert_float_eq_tol(21389, p_sim_d, 1E-1);
}
END_TEST

Suite *s21_math_tests_create() {
    Suite *s21_math = suite_create("s21_math");
    TCase *s21_math_tests = tcase_create("S21_MATH");
    tcase_add_test(s21_math_tests, Test1);
    tcase_add_test(s21_math_tests, Test2);
    tcase_add_test(s21_math_tests, Test3);
    tcase_add_test(s21_math_tests, Test4);
    tcase_add_test(s21_math_tests, Test5);
    tcase_add_test(s21_math_tests, Test6);
    tcase_add_test(s21_math_tests, Test7);
    tcase_add_test(s21_math_tests, Test8);
    tcase_add_test(s21_math_tests, Test9);
    tcase_add_test(s21_math_tests, Test10);
    tcase_add_test(s21_math_tests, Test11);
    tcase_add_test(s21_math_tests, Test12);
    tcase_add_test(s21_math_tests, Test13);
    suite_add_tcase(s21_math, s21_math_tests);
    return s21_math;
}

int main() {
    Suite *s21_math = s21_math_tests_create();
    SRunner *s21_math_runner = srunner_create(s21_math);
    int number_failed;
    srunner_run_all(s21_math_runner, FP_NORMAL);
    number_failed = srunner_ntests_failed(s21_math_runner);
    srunner_free(s21_math_runner);

    return number_failed == 0 ? 0 : 1;
}
