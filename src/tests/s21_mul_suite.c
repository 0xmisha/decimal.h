#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(basic_mul) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 1256;
  dec2.bits[0] = 1000;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 1256000;

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_mul_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // 125236476 * (-364287140) = -45622037665718640
  //          10100010 00010101 00000000
  // 01100100 11111110 10100001 01110000
  dec1.bits[0] = 125236476;
  dec1.bits[3] = 393216;  // точка после шестого знака

  dec2.bits[0] = 364287140;
  // отрицательное число и точка после третьего знака
  dec2.bits[3] = MINUS + 196608;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 1694409072;
  true_ans.bits[1] = 10622208;
  true_ans.bits[3] = 589824 + MINUS;
  // отрицательное число с точкой после девятого знака

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_with_overflow) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000

  dec2.bits[0] = 2;

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 1;

  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_that_still_fits) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 2147483647;
  // 01111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  dec2.bits[0] = 2;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 4294967294;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111110

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(mul_with_overflow_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  // 0.18743623487636123781 * 0.000 0000 4624 6921 =
  // 0.00000000866834874686452293246128301
  // 0.0000000086683487468645229325

  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;  // 20 знаков после запятой
  // 00000000 00000000 00000000 00000001
  // 00000100 00011110 10111010 01000001
  // 00001000 00111000 00110000 10000101
  // 00000000 00010100 00000000 00000000

  dec2.bits[0] = 46246921;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 983040;
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000010 11000001 10101100 00001001
  // 00000000 00001111 00000000 00000000

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2090836749;
  true_ans.bits[1] = 3002702997;
  true_ans.bits[2] = 4;
  true_ans.bits[3] = 1835008;
  // 00000000 00000000 00000000 00000100
  // 10110010 11111001 10011100 10010101
  // 01111100 10011111 10100011 00001101
  // 00000000 00011100 00000000 00000000

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(status, true_status);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(mul_with_overflow_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  // 0.18743623487636123781 * 0.0000000000000001 =
  // 0.00000000000018743623487636123781
  // 0.0000000000001874362348763612

  dec1.bits[0] = 137900165;
  dec1.bits[1] = 69122625;
  dec1.bits[2] = 1;
  dec1.bits[3] = 1310720;  // 20 знаков после запятой
  // 00000000 00000000 00000000 00000001
  // 00000100 00011110 10111010 01000001
  // 00001000 00111000 00110000 10000101
  // 00000000 00010100 00000000 00000000

  dec2.bits[0] = 1;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 1048576;  // 16 знаков после запятой
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00000001
  // 00000000 00001011 00000000 00000000

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2752641148;
  true_ans.bits[1] = 43;
  true_ans.bits[2] = 0;
  true_ans.bits[3] = 1835008;
  // 00000000 00000000 00000000 00000000
  // 00000000 00000000 00000000 00101011
  // 10100100 00010001 11111000 01111100
  // 00000000 00011100 00000000 00000000

  int status = s21_mul(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(status, true_status);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

Suite* mul_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("mul");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_mul);
  tcase_add_test(tc_core, basic_mul_2);
  tcase_add_test(tc_core, mul_with_overflow);
  tcase_add_test(tc_core, mul_that_still_fits);
  tcase_add_test(tc_core, mul_with_overflow_2);
  tcase_add_test(tc_core, mul_with_overflow_3);
  suite_add_tcase(s, tc_core);

  return s;
}
