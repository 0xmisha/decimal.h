#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(short_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 65536;
  dec2.bits[0] = 2;
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 32768;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 9;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 6;
  dec2.bits[3] = 65536;
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 15;
  true_ans.bits[3] = 65536;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536;
  // 14/9 = 1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 14;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 9;
  dec2.bits[3] = 65536 + MINUS;
  // 14/(-9) = -1.5555555555 5555555555 55555556
  // 00110010 01000011 01000001 00000100
  // 01100000 10101011 01011001 00001000
  // 11000011 10001110 00111000 11100100
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 3280877796;
  true_ans.bits[1] = 1621842184;
  true_ans.bits[2] = 843268356;
  true_ans.bits[3] = 1835008 + MINUS;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 2814903;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 0;
  dec2.bits[3] = 65536 + MINUS;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 3;  // не надо делить на ноль
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(div_zero) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 0;
  dec1.bits[3] = 65536;
  dec2.bits[0] = 4578783;
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 0;
  true_ans.bits[1] = 0;
  true_ans.bits[2] = 0;
  true_ans.bits[3] = 0;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;  // операция прошла успешно
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(result_too_big) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 4294967294;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 1;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(result_too_small) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec2.bits[0] = 4294967294;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967295;
  dec1.bits[0] = 1;
  dec1.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 2;
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec1.bits[3] = 1179648;
  dec2.bits[0] = 1;
  dec2.bits[3] = 1179648;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 4294967295;
  true_ans.bits[1] = 4294967295;
  true_ans.bits[2] = 4294967295;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_2) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 4294967295;
  dec2.bits[1] = 4294967295;
  dec2.bits[2] = 4294967295;

  int status = s21_div(dec1, dec2, &ans);
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 1;
  true_ans.bits[1] = 0;
  true_ans.bits[2] = 0;
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_3) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);
  // -278576982813512.8359044835908 / 7123984713482.41253 =
  // -39.104096094745301845239149102

  // -278576982813512.8359044835908
  // 00001001 00000000 01010101 10110100
  // 11111100 01000101 01100100 00011110
  // 01110111 00000010 11101010 01000100
  // 10000000 00001101 00000000 00000000
  dec1.bits[0] = 1996679748;
  dec1.bits[1] = 4232406046;
  dec1.bits[2] = 151016884;
  dec1.bits[3] = 2148335616;

  // 7123984713482.41253
  // 00000000 00000000 00000000 00000000
  // 00001001 11100010 11110010 10100010
  // 10011111 00111110 01000011 01100101
  // 00000000 00000101 00000000 00000000
  dec2.bits[0] = 2671657829;
  dec2.bits[1] = 165868194;
  dec2.bits[2] = 0;
  dec2.bits[3] = 327680;

  // -39.104096094745301845239149102
  // 01111110 01011010 00100110 01110000
  // 11110011 01000010 11100010 00010000
  // 00001010 10100100 00110010 00101110
  // 10000000 00011011 00000000 00000000
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 178532910;
  true_ans.bits[1] = 4081246736;
  true_ans.bits[2] = 2119837296;
  true_ans.bits[3] = 2149253120;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(big_values_div_4) {
  s21_decimal dec1;
  s21_decimal dec2;
  s21_decimal ans;
  s21_init_decimal(&dec1);
  s21_init_decimal(&dec2);
  s21_init_decimal(&ans);
  // 7813912341.293481290382 / 1236128761234.217489792347 =
  // 0.0063212770273961190138049477

  // 7813912341.293481290382
  // 00000000 00000000 00000001 10100111
  // 10010111 11010001 01000010 10000110
  // 01000110 11010011 01101010 10001110
  // 00000000 00001100 00000000 00000000
  dec1.bits[0] = 1188260494;
  dec1.bits[1] = 2547073670;
  dec1.bits[2] = 423;
  dec1.bits[3] = 786432;

  // 1236128761234.217489792347
  // 00000000 00000001 00000101 11000010
  // 10101100 10100110 11001011 10100111
  // 01100010 11011001 11111101 01011011
  // 00000000 00001100 00000000 00000000
  dec2.bits[0] = 1658453339;
  dec2.bits[1] = 2896612263;
  dec2.bits[2] = 67010;
  dec2.bits[3] = 786432;

  // 0.0063212770273961190138049477
  // 00000000 00110100 01001001 11010011
  // 00100100 10011011 00101100 11110100
  // 10110010 10110011 11110011 11000101
  // 00000000 00011100 00000000 00000000
  s21_decimal true_ans;
  s21_init_decimal(&true_ans);
  true_ans.bits[0] = 2998137797;
  true_ans.bits[1] = 614149364;
  true_ans.bits[2] = 3426771;
  true_ans.bits[3] = 1835008;

  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

Suite* div_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("div");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, short_div);
  tcase_add_test(tc_core, basic_div);
  tcase_add_test(tc_core, basic_div_2);
  tcase_add_test(tc_core, basic_div_3);
  tcase_add_test(tc_core, div_by_zero);
  tcase_add_test(tc_core, div_zero);
  tcase_add_test(tc_core, result_too_small);
  tcase_add_test(tc_core, result_too_big);
  tcase_add_test(tc_core, big_values_div);
  tcase_add_test(tc_core, big_values_div_2);
  tcase_add_test(tc_core, big_values_div_3);
  tcase_add_test(tc_core, big_values_div_4);
  suite_add_tcase(s, tc_core);

  return s;
}
