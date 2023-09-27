#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int is_zero(s21_decimal);
int execute_division(s21_decimal, s21_decimal, s21_decimal *);

// Главная функция
int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  arithmetic_operation_result status = OK;
  if (is_zero(value2)) {
    status = 3;
  } else if (is_zero(value1)) {
    s21_init_decimal(result);
  } else {
    status = execute_division(value1, value2, result);
  }
  return status;
}

// Проверка на ноль
int is_zero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

// Выполнение деления
int execute_division(s21_decimal value1, s21_decimal value2,
                     s21_decimal *result) {
  s21_big_decimal value_big1 = s21_to_big_decimal(value1);
  s21_big_decimal value_big2 = s21_to_big_decimal(value2);
  s21_big_decimal result_big;
  s21_initialise_big(&result_big);
  while (value_big1.bits[0] == 0 && value_big2.bits[0] == 0) {
    s21_right_shift_big(&value_big1);
    s21_right_shift_big(&value_big2);
  }
  int status = s21_div_big(value_big1, value_big2, &result_big);
  *result = s21_to_std_decimal(result_big);
  return status;
}
