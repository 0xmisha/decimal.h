#include "../helpers/s21_helpers.h"
#include "../s21_decimal.h"

int handle_same_sign_sub(s21_big_decimal*, s21_big_decimal*, s21_decimal,
                         s21_decimal, s21_big_decimal*);
int handle_diff_sign_sub(s21_big_decimal*, s21_decimal, s21_decimal,
                         s21_decimal*, s21_big_decimal*);

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  // Возвращаемый код успешности операции
  arithmetic_operation_result status = OK;

  // Приводим числа к одной scale
  s21_normalisation(&value1, &value2);
  // Преобразуем стандартные числа в большие
  s21_big_decimal value1_big = s21_to_big_decimal(value1);
  s21_big_decimal value2_big = s21_to_big_decimal(value2);
  s21_big_decimal result_big;
  s21_initialise_big(&result_big);

  // Если знаки чисел совпадают
  if (value1_big.sign == value2_big.sign) {
    // Обрабатываем случай одинаковых знаков
    status = handle_same_sign_sub(&value1_big, &value2_big, value1, value2,
                                  &result_big);
  } else {
    // Обрабатываем случай разных знаков
    status =
        handle_diff_sign_sub(&value2_big, value1, value2, result, &result_big);
  }

  // Приводим экспоненту результата к экспоненте исходного числа
  result_big.exp = value1_big.exp;
  // Преобразуем большой результат в стандартный
  *result = s21_to_std_decimal(result_big);

  return status;
}

// Обрабатывает случай, когда выполняется вычитание чисел с одинаковыми знаками
int handle_same_sign_sub(s21_big_decimal* value1_big,
                         s21_big_decimal* value2_big, s21_decimal value1,
                         s21_decimal value2, s21_big_decimal* result_big) {
  int status = 0;

  // Если первое число больше или равно второму и имеет положительный знак, или
  // если первое число меньше или равно второму и имеет отрицательный знак,
  // выполняем вычитание больших десятичных чисел
  if ((s21_is_greater_or_equal(value1, value2) && !value1_big->sign) ||
      (s21_is_less_or_equal(value1, value2) && value1_big->sign)) {
    status = s21_sub_big(*value1_big, *value2_big, result_big);
  } else {
    // В противном случае, инвертируем знаки и выполняем вычитание больших
    // десятичных чисел
    value1_big->sign = value1_big->sign ^ 1;
    value2_big->sign = value2_big->sign ^ 1;
    status = s21_sub_big(*value2_big, *value1_big, result_big);
  }
  // Записываем знак результата
  result_big->sign = value1_big->sign;

  return status;
}

// Обрабатывает случай, когда выполняется вычитание чисел с разными знаками
int handle_diff_sign_sub(s21_big_decimal* value2_big, s21_decimal value1,
                         s21_decimal value2, s21_decimal* result,
                         s21_big_decimal* result_big) {
  // Инвертируем знак второго большого числа
  value2_big->sign = value2_big->sign ^ 1;
  value2 = s21_to_std_decimal(*value2_big);
  int status = s21_add(value1, value2, result);
  // Преобразуем результат в большое десятичное число
  *result_big = s21_to_big_decimal(*result);

  return status;
}
