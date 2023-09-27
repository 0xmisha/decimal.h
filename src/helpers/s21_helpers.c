#include "s21_helpers.h"

/**
 * @brief Проверяет, равен ли переданный децимал нулю.
 *
 * @param d Децимал для проверки.
 * @return Возвращает 1 если децимал равен нулю, иначе возвращает 0.
 */
int s21_decimal_is_nul(s21_decimal d) {
  int result = 0;
  if (d.bits[0] == 0 && d.bits[1] == 0 && d.bits[2] == 0) result = 1;
  return result;
}

/**
 * @brief Сравнивает мантиссы двух децималов.
 *
 * @param value_1 Первый децимал.
 * @param value_2 Второй децимал.
 * @return Возвращает TRUE, если мантиссы равны, иначе FALSE.
 */
int s21_mantissa_is_equal(s21_decimal value_1, s21_decimal value_2) {
  comparison_result status;
  int i = 95;
  while (i >= 0 && (s21_get_bit(value_1, i) == s21_get_bit(value_2, i))) i--;
  if (i == -1)
    status = TRUE;
  else
    status = FALSE;
  return status;
}

/**
 * @brief Пересчёт scale двух стандартных десятичных чисел
 *
 * Функция приводит два стандартных десятичных числа к одинаковому scale путём
 * преобразования их в большие десятичные числа, выполнения операции пересчёта и
 * обратного преобразования.
 *
 * @param value_1 Указатель на первое число для пересчёта масштаба
 * @param value_2 Указатель на второе число для пересчёта масштаба
 */
void s21_normalisation(s21_decimal *value_1, s21_decimal *value_2) {
  s21_big_decimal value1_big = s21_to_big_decimal(*value_1);
  s21_big_decimal value2_big = s21_to_big_decimal(*value_2);
  s21_normalisation_big(&value1_big, &value2_big);
  *value_1 = s21_to_std_decimal(value1_big);
  *value_2 = s21_to_std_decimal(value2_big);
}

/**
 * @brief Извлекает бит из целочисленного значения.
 *
 * @param num Целочисленное значение.
 * @param pos Позиция бита (начиная с нуля).
 *
 * @return Значение бита в указанной позиции.
 */
bool s21_get_bit_int(unsigned int num, int pos) { return (num >> pos) & 1; }

/**
 * @brief Извлекает знак из значения s21_decimal.
 *
 * @param dec Значение s21_decimal.
 *
 * @return Значение знака.
 */
bool s21_get_sign(s21_decimal dec) { return s21_get_bit_int(dec.bits[3], 31); }

/**
 * @brief Извлекает показатель степени (exp) из значения s21_decimal.
 *
 * @param dec Значение s21_decimal.
 *
 * @return Показатель степени.
 */
int s21_get_exp(s21_decimal dec) { return (dec.bits[3] % 2147483648) >> 16; }

/**
 * @brief Инициализирует значение s21_decimal нулями.
 *
 * @param decimal Указатель на значение.
 */
void s21_init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

/**
 * @brief Получает значение бита в указанной позиции
 * @param d Структура десятичного числа.
 * @param bit Позиция бита для чтения.
 * @return Значение бита (0 или 1).
 */
int s21_get_bit(s21_decimal d, unsigned int bit) {
  unsigned int i = 0;
  s21_rescale_bit(&bit, &i);
  // Возвращаем значение бита, смещенного на указанную позицию
  return !!(d.bits[i] & (1U << bit));
}

/**
 * @brief Преобразует номер бита в индекс десятичного числа и номер бита внутри
 * этого числа.
 * @param bit Указатель на номер бита, который нужно преобразовать.
 * @param i Указатель на переменную для хранения индекса числа.
 */
void s21_rescale_bit(unsigned int *bit, unsigned int *i) {
  // В зависимости от диапазона входного номера бита, корректируем номер бита и
  // индекс числа. Используется для преобразования линейного номера бита в
  // двумерную схему адресации.
  unsigned int ind = 0;
  unsigned int bit_num = *bit;
  if (bit_num > 31 && bit_num < 64) {
    ind = 1;
    bit_num = (32 - bit_num) * -1;
  } else if (bit_num > 63 && bit_num < 96) {
    ind = 2;
    bit_num = (64 - bit_num) * -1;
  } else if (bit_num > 95 && bit_num < 128) {
    ind = 3;
    bit_num = (96 - bit_num) * -1;
  } else if (bit_num > 127 && bit_num < 160) {
    ind = 4;
    bit_num = (128 - bit_num) * -1;
  } else if (bit_num > 159 && bit_num < 192) {
    ind = 5;
    bit_num = (160 - bit_num) * -1;
  } else if (bit_num > BIG_DECIMAL_SIZE - 1 && bit_num < 224) {
    ind = 6;
    bit_num = (192 - bit_num) * -1;
  } else if (bit_num > 223 && bit_num < 256) {
    ind = 7;
    bit_num = (224 - bit_num) * -1;
  }
  *bit = bit_num;
  *i = ind;
}

/**
 * @brief Установить знак числа.
 * @param d Указатель на десятичное число.
 * @param sign Значение знака (0 = "+", 1 = "-").
 */
void s21_set_sign(s21_decimal *d, int sign) {
  d->bits[3] = (sign == 1) ? d->bits[3] | (1U << 31) : d->bits[3] & ~(1U << 31);
}

/**
 * @brief Копирует десятичное число.
 * @param value Десятичное число, которое нужно скопировать.
 * @return Копия десятичного числа.
 */
s21_decimal s21_copy_decimal(s21_decimal value) {
  s21_decimal result;
  s21_init_decimal(&result);
  s21_set_sign(&result, s21_get_sign(value));
  s21_set_exp(&result, s21_get_exp(value));
  for (int i = 0; i < 96; i++) {
    if (s21_get_bit(value, i)) s21_set_bit(&result, i, 1);
  }
  return result;
}

/**
 * @brief Получает экспоненту из числа с плавающей точкой.
 * @param f Число с плавающей точкой, экспонента которого требуется.
 * @return Экспонента числа с плавающей точкой.
 */
int s21_get_float_exp(float f) {
  unsigned int fbits = *((unsigned int *)&f);
  int exp = ((2139095040 & fbits) >> 23) - 127;
  if (exp == -127) exp = 0;
  return exp;
}

/**
 * @brief Устанавливает экспоненту для десятичного числа.
 * @param d Указатель на десятичное число, в котором требуется установить
 * экспоненту.
 * @param exp Экспонента, которую нужно установить.
 */
void s21_set_exp(s21_decimal *d, int exp) {
  d->bits[3] = d->bits[3] & ~16711680;
  d->bits[3] = d->bits[3] | (exp << 16);
}

/**
 * @brief Устанавливает значение конкретного бита.
 * @param d Указатель на десятичное число, в котором требуется установить бит.
 * @param bit_num Номер бита, который нужно установить.
 * @param bit Значение бита, которое нужно установить.
 */
void s21_set_bit(s21_decimal *d, unsigned int bit_num, bool bit) {
  int i = 0;
  if (bit_num > 31 && bit_num < 64) {
    i = 1;
    bit_num = (32 - bit_num) * -1;
  } else if (bit_num > 63 && bit_num < 96) {
    i = 2;
    bit_num = (64 - bit_num) * -1;
  } else if (bit_num > 95) {
    fprintf(stderr, "There is no such bit: %i.\n", bit_num);
  }
  if (bit == 1) {
    d->bits[i] = d->bits[i] | (1U << bit_num);
  } else {
    d->bits[i] = d->bits[i] & ~(1U << bit_num);
  }
}