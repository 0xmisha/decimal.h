#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  convertation_result status;
  status = CONVERTATION_OK;
  *dst = 0.0;
  int scale = s21_get_exp(src);
  *dst = (float)(src.bits[0] * pow(10, -scale));
  if (s21_get_sign(src) == 1) *dst *= -1;
  return status;
}