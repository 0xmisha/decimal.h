#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  convertation_result status;
  status = CONVERTATION_OK;
  if (s21_get_exp(src)) s21_truncate(src, &src);
  if (s21_get_sign(src) == 1)
    *dst = src.bits[0] * -1;
  else
    *dst = src.bits[0];
  return status;
}