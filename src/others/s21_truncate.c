#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *res) {
  other_operations_result status = OPERATION_ERROR;
  if (res) {
    s21_big_decimal value_big;
    value_big = s21_to_big_decimal(value);
    s21_truncate_big(&value_big);
    *res = s21_to_std_decimal(value_big);
    status = OPERATION_OK;
  }
  return status;
}
