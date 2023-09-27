
#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

// два положительных числа, первое больше второго
START_TEST(basic_sub) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);

  // 532167 - 123456 = 408711;
  dec1.bits[0] = 532167;

  dec2.bits[0] = 123456;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 408711;

  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

// два положительных числа, второе больше первого
START_TEST(basic_sub_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 123456;
  dec2.bits[0] = 532167;
  // 123456 - 532167 = -408711;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 408711;
  true_ans.bits[3] = MINUS;

  int status = s21_sub(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

// два отрицательных числа, первое по модулю больше второго
START_TEST(basic_sub_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);

  // -532167 - (-123456) = -408711;
  dec1.bits[0] = 532167;
  dec1.bits[3] = MINUS;

  dec2.bits[0] = 123456;
  dec2.bits[3] = MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 408711;
  true_ans.bits[3] = MINUS;
  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

// два отрицательных числа, второе по модулю больше первого
START_TEST(basic_sub_4) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // -61287 - (-234787) = 173500
  dec1.bits[0] = 61287;
  dec1.bits[3] = MINUS;

  dec2.bits[0] = 234787;
  dec2.bits[3] = MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 173500;

  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(sub_with_dot) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);

  // 532.167 - 0.000000000001236 = 532.166999999998764 =
  // 111 01100010 10100011 00010001 00100100 00101111 01101011 00101100

  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;  // 3 знака после запятой

  dec2.bits[0] = 1236;
  dec2.bits[3] = 983040;  // 15 знаков после запятой

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 607087404;
  true_ans.bits[1] = 123904785;
  true_ans.bits[3] = 983040;  // 18 знаков после запятой
  int status = s21_sub(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(sub_with_dot_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);

  dec1.bits[0] = 532167;
  dec1.bits[3] = 196608;  // 3 знака после запятой

  dec2.bits[0] = 0;
  dec2.bits[3] = 0;  // 15 знаков после запятой

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 532167;
  true_ans.bits[3] = 196608;

  int status = s21_sub(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

// если знаки у чисел не совпадают, вычитание признается сложением
START_TEST(return_to_add) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // -2361234 - 48695 = -2361234 + (-48695) = 2409929
  dec1.bits[0] = 2361234;
  dec1.bits[3] = MINUS;

  dec2.bits[0] = 48695;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2409929;
  true_ans.bits[3] = MINUS;

  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(return_to_add_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  // 6347852 - (-723184) = 6347852 + 723184 = 7071036
  dec1.bits[0] = 6347852;

  dec2.bits[0] = 723184;
  dec2.bits[3] = MINUS;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 7071036;

  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_sub) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);

  // пример из README
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 6;
  dec2.bits[1] = 0;
  dec2.bits[2] = 0;
  dec2.bits[3] = 65536;

  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 4294967294;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int status = s21_sub(dec1, dec2, &ans);

  int true_status = 0;  // операция прошла успешно

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* sub_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("sub_suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_sub);
  tcase_add_test(tc_core, basic_sub_2);
  tcase_add_test(tc_core, basic_sub_3);
  tcase_add_test(tc_core, basic_sub_4);
  tcase_add_test(tc_core, sub_with_dot);
  tcase_add_test(tc_core, sub_with_dot_2);
  tcase_add_test(tc_core, return_to_add);
  tcase_add_test(tc_core, return_to_add_2);
  tcase_add_test(tc_core, big_values_sub);
  suite_add_tcase(s, tc_core);

  return s;
}
