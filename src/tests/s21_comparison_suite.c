#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(is_equal_simple) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(A, &second_decimal);
  ck_assert_int_eq(1, s21_is_equal(decimal, second_decimal));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_equal_0_decimal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 5123;
  s21_from_int_to_decimal(A, &decimal);
  ck_assert_int_eq(0, s21_is_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 5123;
  int B = 5122;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_EQ) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  s21_from_int_to_decimal(A, &second_decimal);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(0, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_not_equal_SIGN) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = -5123;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_not_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_le) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 5123;
  int B = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_stand) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = -5123;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_greater(second_decimal, decimal));
}
END_TEST

START_TEST(is_greater_eq) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_greater_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_greater_0) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 0;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_greater(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_ne) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = -5124;
  int B = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_equal) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_Classic) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 0;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less1) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = -5;
  int B = 5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less2) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int A = 5;
  int B = -5123;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_less(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Classic) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int B = 5123;
  int A = B;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(1, s21_is_less_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(is_less_or_equal_Norm) {
  s21_decimal decimal;
  s21_decimal second_decimal;
  s21_init_decimal(&decimal);
  s21_init_decimal(&second_decimal);
  int B = 5123;
  int A = 51240;
  convertation_result status = s21_from_int_to_decimal(A, &decimal);
  convertation_result second_status =
      s21_from_int_to_decimal(B, &second_decimal);
  ck_assert_int_eq(status, second_status);
  ck_assert_int_eq(0, s21_is_less_or_equal(decimal, second_decimal));
}
END_TEST

START_TEST(equal_1) {
  float num1 = 1.375342323523;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_2) {
  float num1 = 1.39;
  float num2 = 1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(equal_3) {
  float num1 = 1.39;
  float num2 = -1.39;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_4) {
  int num1 = 0;
  int num2 = 0;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(equal_5) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(equal_6) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_equal(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_1) {
  int num1 = 3;
  int num2 = 9;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_2) {
  int num1 = -3;
  int num2 = -3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_3) {
  int num1 = -3;
  int num2 = 3;
  s21_decimal dec1, dec2;
  s21_from_int_to_decimal(num1, &dec1);
  s21_from_int_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_4) {
  float num1 = -3.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_5) {
  float num1 = -345.232446546;
  float num2 = -3.2;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(greater_6) {
  float num1 = -3.232323233232323233;
  float num2 = -34545124.232446543232446543;
  s21_decimal dec1, dec2;
  s21_from_float_to_decimal(num1, &dec1);
  s21_from_float_to_decimal(num2, &dec2);
  int res = s21_is_greater(dec1, dec2);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(greater_7) {
  s21_decimal dec5 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec6 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //  -1.2;
  ck_assert_int_eq(s21_is_greater(dec5, dec6), 1);
  ck_assert_int_eq(s21_is_greater(dec6, dec5), 0);

  s21_decimal dec7 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec8 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2;
  ck_assert_int_eq(s21_is_greater(dec7, dec8), 0);
  ck_assert_int_eq(s21_is_greater(dec8, dec7), 1);

  s21_decimal dec1 = {
      {12345, 0, 0, 0b00000000000001000000000000000000}};  //  1.2345
  s21_decimal dec2 = {{12, 0, 0, 0b00000000000000010000000000000000}};  //  1.2
  ck_assert_int_eq(s21_is_greater(dec1, dec2), 1);
  ck_assert_int_eq(s21_is_greater(dec2, dec1), 0);

  s21_decimal dec3 = {
      {12345, 0, 0, 0b10000000000001000000000000000000}};  // -1.2345
  s21_decimal dec4 = {
      {12, 0, 0, 0b10000000000000010000000000000000}};  //   -1.2
  ck_assert_int_eq(s21_is_greater(dec3, dec4), 0);
  ck_assert_int_eq(s21_is_greater(dec4, dec3), 1);
}
END_TEST

Suite* comparsion_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("equal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, greater_1);
  tcase_add_test(tc_core, greater_2);
  tcase_add_test(tc_core, greater_3);
  tcase_add_test(tc_core, greater_4);
  tcase_add_test(tc_core, greater_5);
  tcase_add_test(tc_core, greater_6);
  tcase_add_test(tc_core, greater_7);
  tcase_add_test(tc_core, equal_1);
  tcase_add_test(tc_core, equal_2);
  tcase_add_test(tc_core, equal_3);
  tcase_add_test(tc_core, equal_4);
  tcase_add_test(tc_core, equal_5);
  tcase_add_test(tc_core, equal_6);
  tcase_add_test(tc_core, is_equal_simple);
  tcase_add_test(tc_core, is_equal_0_decimal);
  tcase_add_test(tc_core, is_not_equal);
  tcase_add_test(tc_core, is_not_equal_SIGN);
  tcase_add_test(tc_core, is_not_equal_EQ);
  tcase_add_test(tc_core, is_greater_stand);
  tcase_add_test(tc_core, is_greater_le);
  tcase_add_test(tc_core, is_greater_0);
  tcase_add_test(tc_core, is_greater_eq);
  tcase_add_test(tc_core, is_less1);
  tcase_add_test(tc_core, is_less2);
  tcase_add_test(tc_core, is_less_Classic);
  tcase_add_test(tc_core, is_less_equal);
  tcase_add_test(tc_core, is_less_ne);
  tcase_add_test(tc_core, is_less_or_equal_Classic);
  tcase_add_test(tc_core, is_less_or_equal_Norm);
  suite_add_tcase(s, tc_core);

  return s;
}
