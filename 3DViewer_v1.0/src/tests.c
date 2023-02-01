#include <check.h>
#include "3d_viever/C_file/struct.h"
#include "3d_viever/C_file/Afina/afina.h"
#include "3d_viever/C_file/pars_obj/pars_obj.h"

START_TEST(Test1) {
    data_t obj = init_struct();
    obj.count_of_facets = 6;
    obj.count_of_vertexes = 6;
    int error_target = 0;
    malloc_struct(&obj, &error_target);
    ck_assert_int_eq(error_target, 0);
    free_struct(&obj);
}
END_TEST

START_TEST(Test2) {
    data_t obj = init_struct();
    obj.count_of_facets = 0;
    obj.count_of_vertexes = 6;
    int error_target = 0;
    malloc_struct(&obj, &error_target);
    ck_assert_int_eq(error_target, 2);
}
END_TEST

START_TEST(Test3) {
    data_t obj = init_struct();
    obj.count_of_facets = 6;
    obj.count_of_vertexes = 0;
    int error_target = 0;
    malloc_struct(&obj, &error_target);
    ck_assert_int_eq(error_target, 2);
    free_struct(&obj);
}
END_TEST

START_TEST(Test4) {
    data_t obj = init_struct();
    obj.count_of_facets = 0;
    obj.count_of_vertexes = 0;
    int error_target = 0;
    malloc_struct(&obj, &error_target);
    ck_assert_int_eq(error_target, 2);
}
END_TEST

START_TEST(Test5) {
    data_t obj = init_struct();
    int error_target = pars_control("human.obj", &obj);
    ck_assert_int_eq(error_target, 0);
    free_struct(&obj);
}
END_TEST

START_TEST(Test6) {
    data_t obj = init_struct();
    int error_target = pars_control("jbajnokafnasvn", &obj);
    ck_assert_int_eq(error_target, 1);
}
END_TEST

START_TEST(Test7) {
    data_t obj = init_struct();
    int error_target = pars_control("false.obj", &obj);
    ck_assert_int_eq(error_target, 1);
}
END_TEST

START_TEST(Test8) {
    data_t obj = init_struct();
    int error_target = pars_control("human.obj", &obj);
    normalization(&obj);
    ck_assert_int_eq(error_target, 0);
    free_struct(&obj);
}
END_TEST

START_TEST(Test9) {
    data_t obj = init_struct();
    double angle_i = 12;
    int error_target = pars_control("human.obj", &obj);
    rotation_by_ox(&obj, angle_i);
    rotation_by_oy(&obj, angle_i);
    rotation_by_oz(&obj, angle_i);
    copy_state(&obj);
    ck_assert_int_eq(error_target, 0);
    free_struct(&obj);
}
END_TEST

Suite *s21_calck_tests_create() {
    Suite *s21_calck = suite_create("s21_calck");
    TCase *s21_calck_tests = tcase_create("S21_CALCK");
    tcase_add_test(s21_calck_tests, Test1);
    tcase_add_test(s21_calck_tests, Test2);
    tcase_add_test(s21_calck_tests, Test3);
    tcase_add_test(s21_calck_tests, Test4);
    tcase_add_test(s21_calck_tests, Test5);
    tcase_add_test(s21_calck_tests, Test6);
    tcase_add_test(s21_calck_tests, Test7);
    tcase_add_test(s21_calck_tests, Test8);
    tcase_add_test(s21_calck_tests, Test9);
    suite_add_tcase(s21_calck, s21_calck_tests);
    return s21_calck;
}

int main() {
    Suite *s21_calck = s21_calck_tests_create();
    SRunner *s21_calck_runner = srunner_create(s21_calck);
    int number_failed;
    srunner_run_all(s21_calck_runner, FP_NORMAL);
    number_failed = srunner_ntests_failed(s21_calck_runner);
    srunner_free(s21_calck_runner);

    return number_failed == 0 ? 0 : 1;
}