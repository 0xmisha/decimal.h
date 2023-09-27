#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_is_less(s21_decimal value1, s21_decimal value_2) {
  comparison_result status;
  if (s21_get_sign(value1) > s21_get_sign(value_2))
    // Первое число положительное
    status = TRUE;
  else if (s21_get_sign(value1) < s21_get_sign(value_2))
    // Первое число отрицательное
    status = FALSE;
  else {
    int sign = s21_get_sign(value1);  // знак числа
    if (!s21_get_exp(value1) || !s21_get_exp(value_2) ||
        s21_get_exp(value1) != s21_get_exp(value_2))
      s21_normalisation(&value1, &value_2);
    int i = 95;
    while (i >= 0 && (s21_get_bit(value1, i) == s21_get_bit(value_2, i))) i--;
    if (i == -1)
      status = FALSE;
    else {
      if (sign ? s21_get_bit(value1, i) == 1
               : s21_get_bit(value1, i) == 1 || i == -1)
        status = sign ? TRUE : FALSE;
      else
        status = sign ? FALSE : TRUE;
    }
  }
  return status;
}