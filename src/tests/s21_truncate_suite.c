#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(simple_truncate) {
  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[0] = 178532910;
  dec.bits[1] = 4081246736;
  dec.bits[2] = 2119837296;
  dec.bits[3] = 2149253120;

  s21_decimal ans;
  s21_init_decimal(&ans);

  // -39
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00100111
  // 10000000 00000000 00000000 00000000
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 39;
  true_ans.bits[3] = MINUS;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(simple_truncate_2) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  // 613478.421
  dec.bits[0] = 613478421;
  dec.bits[3] = 196608;  // точка после третьего знака
  s21_decimal ans;
  s21_init_decimal(&ans);

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 613478;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(zero_truncate) {
  s21_decimal dec;
  s21_init_decimal(&dec);
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 196608;

  s21_decimal ans;
  s21_init_decimal(&ans);

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 0;

  int status = s21_truncate(dec, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* truncate_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("truncate");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, simple_truncate);
  tcase_add_test(tc_core, simple_truncate_2);
  tcase_add_test(tc_core, zero_truncate);
  suite_add_tcase(s, tc_core);

  return s;
}
