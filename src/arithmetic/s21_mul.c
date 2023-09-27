#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  arithmetic_operation_result status = OK;
  s21_big_decimal result_big;
  s21_initialise_big(&result_big);

  s21_big_decimal value_big1 = s21_to_big_decimal(value1);
  s21_big_decimal value_big2 = s21_to_big_decimal(value2);

  status = s21_mul_big(value_big1, value_big2, &result_big);
  *result = s21_to_std_decimal(result_big);
  return status;
}
