#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(s21_negate_1) {
  s21_decimal dec;
  s21_decimal ans;
  s21_init_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[3] = 65536 + MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[3] = 65536;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal dec;
  s21_decimal ans;
  s21_init_decimal(&dec);
  dec.bits[0] = 2814903;
  dec.bits[1] = 2384901;
  dec.bits[2] = 27498;
  dec.bits[3] = 0;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2814903;
  true_ans.bits[1] = 2384901;
  true_ans.bits[2] = 27498;
  true_ans.bits[3] = MINUS;

  int status = s21_negate(dec, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* negate_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("negate");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_negate_1);
  tcase_add_test(tc_core, s21_negate_2);
  suite_add_tcase(s, tc_core);

  return s;
}
