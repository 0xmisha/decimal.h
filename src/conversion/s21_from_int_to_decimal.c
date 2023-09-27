#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  convertation_result status;
  status = CONVERTATION_OK;
  s21_init_decimal(dst);
  if (src < 0) {
    s21_set_sign(dst, 1);
    src *= -1;
  }
  dst->bits[0] = src;
  return status;
}
