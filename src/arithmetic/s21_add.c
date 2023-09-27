#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int handle_different_signs(s21_big_decimal*, s21_decimal*, s21_decimal,
                           s21_decimal*);

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  arithmetic_operation_result status = OK;
  s21_normalisation(&value1, &value2);
  s21_big_decimal value1_big = s21_to_big_decimal(value1);
  s21_big_decimal value2_big = s21_to_big_decimal(value2);
  s21_big_decimal result_big;
  s21_initialise_big(&result_big);

  if (value1_big.sign == value2_big.sign) {
    status = s21_add_big(value1_big, value2_big, &result_big);
    *result = s21_to_std_decimal(result_big);
  } else if (value1_big.sign) {
    status = handle_different_signs(&value1_big, &value1, value2, result);
  } else {
    status = handle_different_signs(&value2_big, &value2, value1, result);
  }

  return status;
}

int handle_different_signs(s21_big_decimal* value_big, s21_decimal* value,
                           s21_decimal other_value, s21_decimal* result) {
  value_big->sign = 0;
  *value = s21_to_std_decimal(*value_big);
  int status = s21_sub(other_value, *value, result);
  s21_big_decimal result_big = s21_to_big_decimal(*result);

  *result = s21_to_std_decimal(result_big);
  return status;
}
