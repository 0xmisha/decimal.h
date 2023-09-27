#ifndef DECIMAL_H
#define DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define BIG_DECIMAL_SIZE 192

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[BIG_DECIMAL_SIZE];
  unsigned int sign;
  int exp;
} s21_big_decimal;

typedef enum {
  OK,
  NUMBER_TOO_BIG,
  NUMBER_TOO_SMALL,
  DIVISION_BY_ZERO
} arithmetic_operation_result;

typedef enum { CONVERTATION_OK, CONVERTATION_ERROR } convertation_result;

typedef enum { OPERATION_OK, OPERATION_ERROR } other_operations_result;

typedef enum { FALSE, TRUE } comparison_result;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

// Conversion
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Others
int s21_floor(s21_decimal value, s21_decimal *res);
int s21_round(s21_decimal value, s21_decimal *res);
int s21_truncate(s21_decimal value, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *res);

#endif
