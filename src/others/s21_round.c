#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *res) {
  other_operations_result status = OPERATION_ERROR;
  if (res) {
    s21_big_decimal value_big = s21_to_big_decimal(value);
    int mod = 0;
    while (value_big.exp > 0) mod = s21_div_by_ten_big(&value_big);
    if (mod >= 5) {
      s21_big_decimal one;
      s21_initialise_big(&one);
      one.bits[0] = 1;
      one.sign = value_big.sign;
      s21_add_big(one, value_big, &value_big);
    }
    *res = s21_to_std_decimal(value_big);
    status = OPERATION_OK;
  }
  return status;
}
