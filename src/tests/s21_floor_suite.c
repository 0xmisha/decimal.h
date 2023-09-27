#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(s21_floor_1) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  d1.bits[0] = 7684355;
  s21_set_exp(&d1, 5);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 76;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  d1.bits[0] = 7684355;
  s21_set_exp(&d1, 7);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  d1.bits[0] = 4294967295;
  s21_set_exp(&d1, 2);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 42949672;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 184467440.73709551615
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  s21_set_exp(&d1, 11);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 184467440;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 1.8446744073709551615
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  s21_set_exp(&d1, 19);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 1;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 0.18446744073709551615
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  s21_set_exp(&d1, 20);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 120.8925819614629174706175
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 65535;
  s21_set_exp(&d1, 22);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;
  real_res.bits[0] = 120;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 0.1208925819614629174706175
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 65535;
  s21_set_exp(&d1, 25);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_9) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 49.51760157141521099596496895
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 268435455;
  s21_set_exp(&d1, 26);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 49;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_10) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 7922816251426433759.3543950335
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 4294967295;
  s21_set_exp(&d1, 10);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  // 7922816251426433759
  real_res.bits[0] = 1593240287;
  real_res.bits[1] = 1844674407;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_11) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 79228162.514264337593543950335
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 4294967295;
  s21_set_exp(&d1, 21);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  // 79228162
  real_res.bits[0] = 79228162;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_12) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 7.9228162514264337593543950335
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 4294967295;
  s21_set_exp(&d1, 28);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 7;

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_13) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 0.920892581961462917470617
  d1.bits[0] = 1301911961;
  d1.bits[1] = 2950210545;
  d1.bits[2] = 49921;
  s21_set_exp(&d1, 24);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_14) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  d1.bits[0] = 5;
  s21_set_exp(&d1, 1);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_15) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 0.9208925819614629174706171
  d1.bits[0] = 134217723;
  d1.bits[1] = 3732301677;
  d1.bits[2] = 499216;
  s21_set_exp(&d1, 25);

  s21_decimal real_res;
  s21_init_decimal(&real_res);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_16) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  d1.bits[0] = 5675;
  s21_set_exp(&d1, 2);
  s21_set_sign(&d1, 1);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 57;
  s21_set_sign(&real_res, 1);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

START_TEST(s21_floor_17) {
  s21_decimal d1;
  s21_decimal res;
  s21_init_decimal(&d1);

  // d1 = 49.51760157141521099596496895
  d1.bits[0] = 4294967295;
  d1.bits[1] = 4294967295;
  d1.bits[2] = 268435455;
  s21_set_exp(&d1, 26);
  s21_set_sign(&d1, 1);

  s21_decimal real_res;
  s21_init_decimal(&real_res);
  real_res.bits[0] = 50;
  s21_set_sign(&real_res, 1);

  int status = s21_floor(d1, &res);
  int real_status = 0;

  ck_assert_int_eq(1, s21_is_equal(res, real_res));
  ck_assert_int_eq(status, real_status);
}
END_TEST

Suite* floor_suite(void) {
  Suite* s;
  TCase* tc_core;

  s = suite_create("floor");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_floor_1);
  tcase_add_test(tc_core, s21_floor_2);
  tcase_add_test(tc_core, s21_floor_3);
  tcase_add_test(tc_core, s21_floor_4);
  tcase_add_test(tc_core, s21_floor_5);
  tcase_add_test(tc_core, s21_floor_6);
  tcase_add_test(tc_core, s21_floor_7);
  tcase_add_test(tc_core, s21_floor_8);
  tcase_add_test(tc_core, s21_floor_9);
  tcase_add_test(tc_core, s21_floor_10);
  tcase_add_test(tc_core, s21_floor_11);
  tcase_add_test(tc_core, s21_floor_12);
  tcase_add_test(tc_core, s21_floor_13);
  tcase_add_test(tc_core, s21_floor_14);
  tcase_add_test(tc_core, s21_floor_15);
  tcase_add_test(tc_core, s21_floor_16);
  tcase_add_test(tc_core, s21_floor_17);
  suite_add_tcase(s, tc_core);

  return s;
}
