#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  other_operations_result status = OPERATION_OK;
  s21_init_decimal(result);
  s21_truncate(value, result);
  if (s21_get_sign(value)) {
    s21_decimal one;
    s21_init_decimal(&one);
    one.bits[0] = 1;
    s21_sub(*result, one, result);
  }
  return status;
}