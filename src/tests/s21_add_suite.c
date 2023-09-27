#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(basic_add) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 123456;
  dec2.bits[0] = 532167;
  // 123456 + 532167 = 655623

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 655623;

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_add_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 38321;
  dec2.bits[0] = 13282;
  dec1.bits[3] = MINUS;
  dec2.bits[3] = MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 51603;
  true_ans.bits[3] = MINUS;

  int status = s21_add(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_add) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[0] = 4238529012;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 0;

  dec2.bits[0] = 56438283;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967294;

  // 4238529012 + 56438283 = 4294967295 (максимальный int)
  // 4294967295 + 4294967295 = 8589934590 =
  // 2^33 - 2 = 1 11111111 11111111 11111111 11111110
  // единица переносится в следующий бит
  // 4294967294 + 1 = 4294967295

  // практически максимальный децимал
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967294;
  true_ans.bits[2] = 4294967295;

  int status = s21_add(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_overflow) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[0] = 4238529012;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 56438283;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967294;

  int status = s21_add(dec1, dec2, &ans);

  int true_status = 1;  // произошло переполнение
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_add_dot) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  // 613478.421 + 2634871.723814 = 3248350.144814
  // 613478.421
  dec1.bits[0] = 613478421;
  dec1.bits[3] = 196608;  // точка после третьего знака

  // 2634871.723814  10 01100101   01111010 10010111 11010111 00100110
  dec2.bits[0] = 2056771366;
  dec2.bits[1] = 613;
  dec2.bits[3] = 393216;  // точка после шестого знака

  //  3248350.144814 10 11110100   01010000 11000001 10101001 00101110

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 1354869038;
  true_ans.bits[1] = 756;

  true_ans.bits[3] = 393216;  // точка после шестого знака

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_add_dot_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  // 613478.421 + 2634871.723814 = 3248350.144814
  // 613478.421
  dec1.bits[0] = 613478421;
  dec1.bits[3] = 196608;  // точка после третьего знака

  // 2634871.723814  10 01100101   01111010 10010111 11010111 00100110
  dec2.bits[0] = 0;
  dec2.bits[3] = 393216;  // точка после шестого знака

  //  3248350.144814 10 11110100   01010000 11000001 10101001 00101110

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 613478421;

  true_ans.bits[3] = 196608;  // точка после шестого знака

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_dot_overflow) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111
  // 11111111 11111111 11111111 11111111 =
  // 2^96 - 1 = 79228162514264337593543950335
  // 79228162514264337593543950335
  dec1.bits[3] = 196608;  // точка после третьего знака

  dec2.bits[0] = 1;
  dec2.bits[3] = 196608;  // точка после третьего знака

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2576980378;
  true_ans.bits[1] = 2576980377;
  true_ans.bits[2] = 429496729;
  true_ans.bits[3] = 131072;
  // 79228162514264337593543950.335 + 0.01 = 79228162514264337593543950.336 =
  // 2^96 = 1 00000000 00000000 00000000 00000000
  // переполнение
  // 79228162514264337593543950.335 = 79228162514264337593543950.34
  // 79228162514264337593543950.34 =
  //    11001 10011001 10011001 10011001
  // 10011001 10011001 10011001 10011001
  // 10011001 10011001 10011001 10011010

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(return_to_sub) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // 23784103 + (-721398) = 23784103 - 721398 = 23062705

  dec1.bits[0] = 23784103;

  dec2.bits[0] = 721398;
  dec2.bits[3] = MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 23062705;

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(return_to_sub_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // -74563556 + 24567653 = 24567653 - 74563556 = -49995903
  dec1.bits[0] = 74563556;
  dec1.bits[3] = MINUS;

  dec2.bits[0] = 24567653;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 49995903;
  true_ans.bits[3] = MINUS;

  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_add_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 1;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 1835008;  // точка на 28 месте

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 4294967294;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  // число не изменилось
  int status = s21_add(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(add_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  dec1.bits[0] = 723947;
  dec1.bits[1] = 839204;
  dec1.bits[2] = 8239;

  dec2.bits[3] = 1835008;

  s21_decimal ans;
  s21_init_decimal(&ans);

  int status = s21_add(dec1, dec2, &ans);

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 723947;
  true_ans.bits[1] = 839204;
  true_ans.bits[2] = 8239;

  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* add_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("add");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_add);
  tcase_add_test(tc_core, basic_add_2);
  tcase_add_test(tc_core, big_values_add);
  tcase_add_test(tc_core, big_values_add_2);
  tcase_add_test(tc_core, big_values_overflow);
  tcase_add_test(tc_core, basic_add_dot);
  tcase_add_test(tc_core, basic_add_dot_2);
  tcase_add_test(tc_core, big_values_dot_overflow);
  tcase_add_test(tc_core, return_to_sub);
  tcase_add_test(tc_core, return_to_sub_2);
  tcase_add_test(tc_core, add_zero);
  suite_add_tcase(s, tc_core);

  return s;
}