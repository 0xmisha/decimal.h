#ifndef HELPERS_H
#define HELPERS_H
#include "../s21_decimal.h"

//////// BIG DECIMALS

// arithmetic
int s21_sub_big(s21_big_decimal, s21_big_decimal, s21_big_decimal *);
int s21_add_big(s21_big_decimal, s21_big_decimal, s21_big_decimal *);
int s21_mul_big(s21_big_decimal, s21_big_decimal, s21_big_decimal *);
int s21_div_big(s21_big_decimal, s21_big_decimal, s21_big_decimal *);

// getters & setters
int s21_get_last_bit_big(s21_big_decimal);
void s21_set_scale_to_zero_big(s21_big_decimal *, s21_big_decimal *);

// converters
s21_decimal s21_to_std_decimal(s21_big_decimal);
s21_big_decimal s21_to_big_decimal(s21_decimal);

// other
void s21_right_shift_big(s21_big_decimal *);
void s21_left_shift_big(s21_big_decimal *);
void s21_initialise_big(s21_big_decimal *);
void s21_normalisation_big(s21_big_decimal *, s21_big_decimal *);
void s21_do_smaller_big(s21_big_decimal *, s21_big_decimal *);
bool s21_compare_bits_big(s21_big_decimal, s21_big_decimal);
int s21_div_by_ten_big(s21_big_decimal *);
bool s21_is_null_big(s21_big_decimal);
void s21_padding_big(s21_big_decimal *, s21_big_decimal *);
s21_big_decimal s21_div_with_remainder(s21_big_decimal, s21_big_decimal,
                                       s21_big_decimal *);
void s21_truncate_big(s21_big_decimal *);
void s21_bank_rounding(s21_big_decimal *, int);

//////// STD DECIMALS

// getters
bool s21_get_sign(s21_decimal);
int s21_get_exp(s21_decimal);
bool s21_get_bit_int(unsigned int, int);
int s21_get_bit(s21_decimal, unsigned int);
int s21_get_float_exp(float);

// setters
void s21_set_sign(s21_decimal *, int);
void s21_set_bit(s21_decimal *, unsigned int, bool);
void s21_set_exp(s21_decimal *, int);

// other
void s21_normalisation(s21_decimal *, s21_decimal *);
void s21_rescale_bit(unsigned int *, unsigned int *);
long int s21_to_integer(s21_decimal);
s21_decimal s21_copy_decimal(s21_decimal);
void s21_init_decimal(s21_decimal *);

int s21_decimal_is_nul(s21_decimal);
int s21_mantissa_is_equal(s21_decimal, s21_decimal);
#endif
