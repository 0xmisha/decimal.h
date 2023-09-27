#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  convertation_result status;
  if (src != INFINITY && src != -INFINITY && !isnan(src)) {
    status = CONVERTATION_OK;
    s21_init_decimal(dst);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src *= -1;
    }
    if (src > 0 && src < 1e-28)
      status = CONVERTATION_ERROR;
    else if (src != 0) {
      int exp = s21_get_float_exp(src);
      if (exp > 95)
        status = CONVERTATION_ERROR;
      else {
        long int scale = 0;
        long int new = (long int)src;
        while (src - ((float)new / (long int)pow(10, scale)) != 0) {
          scale++;
          new = src *(long int)pow(10, scale);
        }
        s21_from_int_to_decimal(new, dst);
        if (sign) s21_set_sign(dst, 1);
        s21_set_exp(dst, scale);
      }
    }
  } else {
    status = CONVERTATION_ERROR;
  }
  return status;
}
