#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  other_operations_result status = OPERATION_OK;
  s21_init_decimal(result);
  *result = s21_copy_decimal(value);
  s21_set_sign(result, !(s21_get_sign(value)));
  return status;
}