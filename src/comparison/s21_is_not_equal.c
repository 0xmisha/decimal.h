#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal value1, s21_decimal value_2) {
  comparison_result status;
  if (s21_is_equal(value1, value_2))
    status = FALSE;
  else
    status = TRUE;
  return status;
}
