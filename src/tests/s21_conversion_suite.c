#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(from_float_to_decimal_simple) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float number = 100.5;
  s21_from_float_to_decimal(number, &decimal);
}
END_TEST

START_TEST(float_eq_float) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float A = 100.5;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(float_eq_float_minus) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float A = -100.5;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(float_eq_float_hard_test) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float A = -1000.201;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(int_decimal_int_1) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = INT32_MAX, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_2) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = INT32_MIN, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_3) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = 0, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_4) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = -123456, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_5) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = 987654, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_6) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = -1, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_decimal_int_7) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  int i = 2, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(float_decimal_float_1) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float f = 0.0000000001, res = 0;
  s21_from_float_to_decimal(f, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_2) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float f = -3.0, res = 0;
  s21_from_float_to_decimal(f, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

START_TEST(float_decimal_float_3) {
  s21_decimal decimal;
  s21_init_decimal(&decimal);
  float f = 0, res = 0;
  s21_from_float_to_decimal(f, &decimal);
  s21_from_decimal_to_float(decimal, &res);
  ck_assert_float_eq(f, res);
}
END_TEST

Suite* conversion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("conversion");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, int_decimal_int_1);
  tcase_add_test(tc_core, int_decimal_int_2);
  tcase_add_test(tc_core, int_decimal_int_3);
  tcase_add_test(tc_core, int_decimal_int_4);
  tcase_add_test(tc_core, int_decimal_int_5);
  tcase_add_test(tc_core, int_decimal_int_6);
  tcase_add_test(tc_core, int_decimal_int_7);

  tcase_add_test(tc_core, float_decimal_float_1);
  tcase_add_test(tc_core, float_decimal_float_2);
  tcase_add_test(tc_core, float_decimal_float_3);

  tcase_add_test(tc_core, from_float_to_decimal_simple);
  tcase_add_test(tc_core, float_eq_float);
  tcase_add_test(tc_core, float_eq_float_minus);
  tcase_add_test(tc_core, float_eq_float_hard_test);

  suite_add_tcase(s, tc_core);

  return s;
}
