#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  comparison_result status;
  if (s21_decimal_is_nul(value_1) && s21_decimal_is_nul(value_2))
    status = TRUE;
  else {
    if (!s21_get_exp(value_1) || !s21_get_exp(value_2) ||
        s21_get_exp(value_1) != s21_get_exp(value_2))
      s21_normalisation(&value_1, &value_2);
    if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
      status = FALSE;
    } else if (s21_get_exp(value_1) != s21_get_exp(value_2)) {
      status = FALSE;
    } else {
      status = s21_mantissa_is_equal(value_1, value_2);
    }
  }
  return status;
}
