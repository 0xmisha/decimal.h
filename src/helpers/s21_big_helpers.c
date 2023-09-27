#include "s21_helpers.h"

/**
 * @brief Вычитает два значения s21_big_decimal.
 *
 * @param value1_big Первое значение.
 * @param value2_big Второе значение.
 * @param result_big Указатель на переменную для записи результата.
 *
 * @return Код ошибки. 0, если ошибок не было.
 */
int s21_sub_big(s21_big_decimal value1_big, s21_big_decimal value2_big,
                s21_big_decimal *result_big) {
  int status = 0;
  // отслеживаниe возможного переноса при выполнении вычитания
  bool t_bit = 0;
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    // Вычитание каждого бита с помощью XOR
    result_big->bits[i] = value1_big.bits[i] ^ value2_big.bits[i] ^ t_bit;

    // Если текущий бит первого числа равен 0, а текущий бит второго числа равен
    // 1, то перенос устанавливается в 1 для следующего бита
    if (value1_big.bits[i] == 0 && value2_big.bits[i] == 1) t_bit = 1;

    // Если текущий бит первого числа равен 1, а текущий бит второго числа равен
    // 0, то перенос устанавливается в 0 для следующего бита
    else if (value1_big.bits[i] == 1 && value2_big.bits[i] == 0)
      t_bit = 0;
  }

  return status;
}

/**
 * @brief Суммирует два больших децимала.
 *
 * @param value1_big Первый децимал для суммирования.
 * @param value2_big Второй децимал для суммирования.
 * @param result_big Результат суммирования.
 * @return Статус выполнения операции.
 */
int s21_add_big(s21_big_decimal value1_big, s21_big_decimal value2_big,
                s21_big_decimal *result_big) {
  // Определяем начальные значения и переменные
  int status = 0;
  bool t_bit = false;
  s21_initialise_big(result_big);

  // Используем цикл для выполнения операции сложения для каждого бита в большом
  // десятичном числе
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    // Применяем операцию XOR к битам обоих чисел и значению переноса
    result_big->bits[i] = value1_big.bits[i] ^ value2_big.bits[i] ^ t_bit;

    // Определяем значение переноса для следующего бита
    t_bit = (value1_big.bits[i] & value2_big.bits[i]) ||
            (value1_big.bits[i] & t_bit) || (value2_big.bits[i] & t_bit);
  }

  // Задаем знак и экспоненту результата
  result_big->exp = value1_big.exp;
  result_big->sign = value1_big.sign;

  // Проверяем, не превышает ли последний бит порог, и выполняем округление при
  // необходимости
  if (s21_get_last_bit_big(*result_big) > 95 && result_big->exp <= 0) {
    status = 1;
  } else if (s21_get_last_bit_big(*result_big) > 95) {
    int mod = s21_div_by_ten_big(result_big);
    s21_bank_rounding(result_big, mod);
  }

  return status;
}

/**
 * @brief Умножение двух больших десятичных чисел
 *
 * Функция выполняет умножение двух больших десятичных чисел.
 *
 * @param value1_big Первый множитель типа s21_big_decimal
 * @param value2_big Второй множитель типа s21_big_decimal
 * @param result_big Указатель на переменную, в которой будет сохранен результат
 * @return Статус операции (0 - успешно, 1 - переполнение, 2 - умножение на
 * ноль)
 */
int s21_mul_big(s21_big_decimal value1_big, s21_big_decimal value2_big,
                s21_big_decimal *result_big) {
  // Проверка на умножение на ноль - если один из операндов равен нулю,
  // результат также будет нулем
  if (s21_is_null_big(value1_big) || s21_is_null_big(value2_big)) {
    return 2;
  }
  // Статус операции устанавливается в 0 (успешное выполнение)
  int status = 0;

  s21_initialise_big(result_big);

  // Умножение: для каждого бита второго числа добавляем первое число в
  // результат, если бит равен 1
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) {
    if (value2_big.bits[i] == 1) {
      s21_add_big(*result_big, value1_big, result_big);
    }
    // Для следующего раунда умножения сдвигаем первое число влево
    s21_left_shift_big(&value1_big);
  }

  // После умножения складываем экспоненты и определяем знак результата
  result_big->exp = value1_big.exp + value2_big.exp;
  result_big->sign = value1_big.sign ^ value2_big.sign;

  // Проверяем, не превышает ли максимальный бит порог или не слишком ли большая
  // экспонента
  int maxBit = s21_get_last_bit_big(*result_big);
  if (maxBit > 95 || result_big->exp > 28) {
    int mod = 0;
    // Если это так, проводим дополнительные операции для приведения числа в
    // допустимый диапазон
    while (result_big->exp > 0 && (maxBit > 95 || result_big->exp > 28)) {
      if (result_big->exp == 0) {
        break;
      }
      // Делим число на 10, пока его размер или экспонента не уменьшатся до
      // приемлемого значения
      mod = s21_div_by_ten_big(result_big);
    }
    // Проводим округление по правилам банковского округления, если экспонента
    // все еще больше нуля
    if (result_big->exp > 0) {
      s21_bank_rounding(result_big, mod);
    } else {
      status = 1;  // Переполнение
    }
  }

  // Pезультат оказывается равным нулю
  if (s21_is_null_big(*result_big)) {
    status = 2;
  }

  return status;
}

/**
 * @brief Деление двух больших десятичных чисел
 *
 * Функция выполняет деление двух чисел типа s21_big_decimal и сохраняет
 * результат в переменной result_big.
 *
 * @param value1_big Делимое число типа s21_big_decimal
 * @param value2_big Делитель число типа s21_big_decimal
 * @param result_big Указатель на переменную, в которой будет сохранен результат
 * @return Статус операции (0 - успешно, 1 - переполнение, 2 - деление на ноль)
 */
int s21_div_big(s21_big_decimal value1_big, s21_big_decimal value2_big,
                s21_big_decimal *result_big) {
  s21_big_decimal ten;
  s21_initialise_big(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_initialise_big(result_big);
  int status = 0;

  // Определение знака результата и приведение исходных чисел к положительному
  // виду
  bool sign = value1_big.sign ^ value2_big.sign;
  value1_big.sign = 0;
  value2_big.sign = 0;

  s21_set_scale_to_zero_big(&value1_big, &value2_big);

  // Выполнение первичного деления с остатком
  s21_big_decimal modulo;
  s21_initialise_big(&modulo);
  modulo = s21_div_with_remainder(value1_big, value2_big, &value1_big);

  int exp = 0;
  int flag = 0;

  // пока числитель или остаток не станут равными нулю
  while (!s21_is_null_big(value1_big) || !s21_is_null_big(modulo)) {
    exp++;
    s21_mul_big(modulo, ten, &modulo);
    s21_mul_big(*result_big, ten, result_big);
    flag = s21_add_big(*result_big, value1_big, result_big);
    modulo = s21_div_with_remainder(modulo, value2_big, &value1_big);
    // Если происходит переполнение, выходим из цикла
    if (flag == 1) break;
  }

  // Обработка ситуации переполнения
  int mod;
  if (flag == 1) {
    mod = s21_div_by_ten_big(result_big);
    // Сокращаем число, пока его размер не станет приемлемым
    while (s21_get_last_bit_big(*result_big) > 95 && exp > 0) {
      mod = s21_div_by_ten_big(result_big);
      exp--;
    }
    // Применяем банковское округление к числу
    s21_bank_rounding(result_big, mod);
    exp--;
  }

  // Установка экспоненты результата
  result_big->exp = exp - 1;
  mod = 10;

  // Обеспечиваем, чтобы экспонента результата была в допустимых пределах
  while (result_big->exp > 28) {
    mod = s21_div_by_ten_big(result_big);
  }

  // Если результат равен нулю
  if (s21_is_null_big(*result_big)) {
    status = 2;
  } else if (mod != 10) {
    // Если число было уменьшено
    s21_bank_rounding(result_big, mod);
  }

  // Если размер числа все еще больше допустимого
  if (s21_get_last_bit_big(*result_big) > 95) {
    status = 1;
  }

  result_big->sign = sign;
  return status;
}

/**
 * @brief Сдвигает все биты значения s21_big_decimal на один вправо.
 *
 * @param big Указатель на значение.
 */
void s21_right_shift_big(s21_big_decimal *big) {
  for (int i = 0; i < BIG_DECIMAL_SIZE - 1; i++)
    big->bits[i] = big->bits[i + 1];
  big->bits[BIG_DECIMAL_SIZE - 1] = 0;
}

/**
 * @brief Сдвигает все биты значения s21_big_decimal на один влево.
 *
 * @param big Указатель на значение.
 */
void s21_left_shift_big(s21_big_decimal *big) {
  for (int i = BIG_DECIMAL_SIZE - 1; i > 0; i--)
    big->bits[i] = big->bits[i - 1];
  big->bits[0] = 0;
}

/**
 * @brief Инициализирует значение s21_big_decimal нулями.
 *
 * @param big Указатель на значение.
 */
void s21_initialise_big(s21_big_decimal *big) {
  big->sign = 0;
  big->exp = 0;
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) big->bits[i] = 0;
}

/**
 * @brief Рескейлинг двух значений s21_big_decimal так, чтобы их показатели
 * стали равными.
 *
 * @param value1_big Указатель на первое значение.
 * @param value2_big Указатель на второе значение.
 *
 * Если показатели (exp) значений не равны, большее значение масштабируется вниз
 * до меньшего. Если одно из значений равно нулю, его показатель устанавливается
 * равным показателю другого значения.
 */
void s21_normalisation_big(s21_big_decimal *value1_big,
                           s21_big_decimal *value2_big) {
  // Инициализация значения "десять" в формате s21_big_decimal
  s21_big_decimal ten;
  s21_initialise_big(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;

  // Если оба значения не равны нулю
  if (!s21_is_null_big(*value1_big) && !s21_is_null_big(*value2_big)) {
    // Если показатель первого значения больше показателя второго
    if (value1_big->exp > value2_big->exp) {
      // Вычисление разности показателей
      int exp_dif = value1_big->exp - value2_big->exp;
      // Умножение второго значения на 10 столько раз, сколько составляет
      // разница показателей
      for (int i = 0; i < exp_dif; i++)
        s21_mul_big(*value2_big, ten, value2_big);
      // Если после умножения количество бит во втором значении превысило 95
      // оба значения уменьшаются, сохраняя их отношение
      if (s21_get_last_bit_big(*value2_big) > 95) {
        s21_do_smaller_big(value1_big, value2_big);
      }
      // Устанавливаем показатели обоих значений равными
      value2_big->exp = value1_big->exp;
      // Если показатель второго значения больше показателя первого
    } else if (value2_big->exp > value1_big->exp) {
      // В этом случае функция вызывает саму себя с обратным порядком аргументов
      s21_normalisation_big(value2_big, value1_big);
    }
    // Если первое значение равно нулю, его показатель устанавливается равным
    // показателю второго значения
  } else if (s21_is_null_big(*value1_big)) {
    value1_big->exp = value2_big->exp;
    // Если второе значение равно нулю, его показатель устанавливается равным
    // показателю первого значения
  } else {
    value2_big->exp = value1_big->exp;
  }
}

/**
 * @brief Уменьшает оба значения s21_big_decimal так, чтобы их битовое
 * представление не превышало 95 бит.
 *
 * @param value1_big Указатель на первое значение.
 * @param value2_big Указатель на второе значение.
 *
 * Функция уменьшает оба значения путем деления их на 10 до тех пор, пока
 * битовое представление второго значения не станет меньше или равно 95 бит.
 * Остатки от деления используются для округления значений по правилам
 * банковского округления.
 */
void s21_do_smaller_big(s21_big_decimal *value1_big,
                        s21_big_decimal *value2_big) {
  int mod1 = 0, mod2 = 0;
  while (s21_get_last_bit_big(*value2_big) > 95) {
    mod1 = s21_div_by_ten_big(value1_big);
    mod2 = s21_div_by_ten_big(value2_big);
  }
  s21_bank_rounding(value1_big, mod1);
  s21_bank_rounding(value2_big, mod2);
  if (s21_get_last_bit_big(*value2_big) > 95) {
    mod1 = s21_div_by_ten_big(value1_big);
    mod2 = s21_div_by_ten_big(value2_big);
    s21_bank_rounding(value1_big, mod1);
    s21_bank_rounding(value2_big, mod2);
  }
}

/**
 * @brief Сравнивает два значения s21_big_decimal по их битовым представлениям,
 * не учитывая показатели степени.
 *
 * @param decimal_big1 Первое значение.
 * @param decimal_big2 Второе значение.
 *
 * @return 1, если первое значение больше или равно второму, 0, если второе
 * значение больше первого.
 */
bool s21_compare_bits_big(s21_big_decimal decimal_big1,
                          s21_big_decimal decimal_big2) {
  int i = BIG_DECIMAL_SIZE - 1;
  while (i >= 0 && decimal_big1.bits[i] == decimal_big2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : decimal_big1.bits[i];
}

/**
 * @brief Делит большой децимал на 10.
 *
 * @param big Децимал для деления.
 * @return Остаток от деления децимала на 10.
 */
int s21_div_by_ten_big(s21_big_decimal *big) {
  s21_big_decimal result;
  s21_initialise_big(&result);
  int exp = big->exp;
  int sign = big->sign;
  result.sign = 0;
  result.exp = 0;
  s21_big_decimal ten;
  s21_initialise_big(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_big_decimal modulo = s21_div_with_remainder(*big, ten, big);
  int res = s21_to_std_decimal(modulo).bits[0];
  big->exp = exp - 1;
  big->sign = sign;
  return res;
}

/**
 * @brief Проверяет, равно ли значение s21_big_decimal нулю.
 *
 * @param big Значение.
 *
 * @return True, если значение равно нулю, иначе false.
 */
bool s21_is_null_big(s21_big_decimal big) {
  bool result = 0;
  for (int i = 0; i < BIG_DECIMAL_SIZE; i++) result += big.bits[i];
  return !result;
}

/**
 * @brief Ищет позицию самого левого единичного бита в значении s21_big_decimal.
 *
 * @param big Значение.
 *
 * @return Позиция самого левого единичного бита. Возвращает -1, если значение
 * равно нулю.
 */
int s21_get_last_bit_big(s21_big_decimal big) {
  int i = -1;
  if (!s21_is_null_big(big)) {
    for (i = BIG_DECIMAL_SIZE - 1; i >= 0; i--)
      if (big.bits[i] == 1) break;
  }
  return i;
}

/**
 * @brief Выравнивание чисел для операций деления.
 * Преобразует пары чисел типа 1001 и 10 в 1001 и 1000 или пары типа 1001 и 11 в
 * 1001 и 110.
 * @param value1_big Указатель на первое десятичное число для выравнивания.
 * @param value2_big Указатель на второе десятичное число для выравнивания.
 */
void s21_padding_big(s21_big_decimal *value1_big, s21_big_decimal *value2_big) {
  if (s21_is_null_big(*value1_big) || s21_is_null_big(*value2_big)) {
    return;
  }

  int l1 = s21_get_last_bit_big(*value1_big);
  int l2 = s21_get_last_bit_big(*value2_big);

  while (l1 != l2) {
    if (l1 < l2) {
      s21_left_shift_big(value1_big);
      l1++;
    } else {
      s21_left_shift_big(value2_big);
      l2++;
    }
  }

  if (value1_big->bits[0] == 0 && value2_big->bits[0] == 0 &&
      l1 > s21_get_last_bit_big(*value1_big) &&
      l2 > s21_get_last_bit_big(*value2_big)) {
    s21_right_shift_big(value1_big);
    s21_right_shift_big(value2_big);
  }
}

/**
 * @brief Устанавливает показатель степени (exp) обоих значений s21_big_decimal
 * равным нулю.
 *
 * @param value1_big Указатель на первое значение.
 * @param value2_big Указатель на второе значение.
 *
 * Функция используется для подготовки значений к делению.
 */
void s21_set_scale_to_zero_big(s21_big_decimal *value1_big,
                               s21_big_decimal *value2_big) {
  s21_big_decimal ten;
  s21_initialise_big(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;

  if (value1_big->exp > value2_big->exp) {
    value1_big->exp -= value2_big->exp;
    value2_big->exp = 0;
    while (value1_big->exp--) {
      s21_mul_big(*value2_big, ten, value2_big);
    }
  } else {
    value2_big->exp -= value1_big->exp;
    value1_big->exp = 0;
    while (value2_big->exp--) {
      s21_mul_big(*value1_big, ten, value1_big);
    }
  }
}

/**
 * @brief Деление большого десятичного числа с остатком
 *
 * Функция выполняет деление двух больших десятичных чисел с остатком.
 *
 * @param value1_big Делимое число типа s21_big_decimal
 * @param value2_big Делитель число типа s21_big_decimal
 * @param result_big Указатель на переменную, в которой будет сохранен результат
 * @return Остаток от деления типа s21_big_decimal
 */
s21_big_decimal s21_div_with_remainder(s21_big_decimal value1_big,
                                       s21_big_decimal value2_big,
                                       s21_big_decimal *result_big) {
  int denominator_left_bit = s21_get_last_bit_big(value2_big);
  s21_initialise_big(result_big);

  if (s21_compare_bits_big(value1_big, value2_big)) {
    s21_padding_big(&value1_big, &value2_big);
  }

  for (int i = 0; i < BIG_DECIMAL_SIZE - 1; i++) {
    if (s21_compare_bits_big(value1_big, value2_big)) {
      s21_sub_big(value1_big, value2_big, &value1_big);
      result_big->bits[0] = 1;
    }

    if (s21_get_last_bit_big(value2_big) <= denominator_left_bit) {
      break;
    }

    if (s21_get_last_bit_big(value2_big) > denominator_left_bit) {
      s21_right_shift_big(&value2_big);
    }

    s21_left_shift_big(result_big);
  }

  s21_big_decimal modulo = value1_big;
  return modulo;
}

/**
 * @brief Урезает значение s21_big_decimal до его целой части путем
 * последовательного деления на 10.
 *
 * @param value_big Указатель на значение.
 */
void s21_truncate_big(s21_big_decimal *value_big) {
  while (value_big->exp > 0) s21_div_by_ten_big(value_big);
}

/**
 * @brief Конвертирует стандартный децимал в большой децимал.
 *
 * @param std Стандартный децимал.
 * @return Большой децимал.
 */
void s21_bank_rounding(s21_big_decimal *big, int mod) {
  if ((mod == 5 && big->bits[0]) || mod > 5) {
    s21_big_decimal one;
    s21_initialise_big(&one);
    one.bits[0] = 1;
    one.exp = big->exp;
    one.sign = big->sign;
    s21_add_big(*big, one, big);
    if (s21_get_last_bit_big(*big) > 95) {
      s21_sub_big(*big, one, big);
      mod = s21_div_by_ten_big(big);
      s21_bank_rounding(big, mod);
    }
  }
}

/**
 * @brief Конвертация большого десятичного числа в стандартный десятичный формат
 *
 * Данная функция преобразует число типа s21_big_decimal в число типа
 * s21_decimal. Используется для уменьшения размерности числа.
 *
 * @param big Число типа s21_big_decimal для конвертации
 * @return Число типа s21_decimal
 */
s21_decimal s21_to_std_decimal(s21_big_decimal big) {
  s21_decimal std;
  s21_init_decimal(&std);
  int k = 95;

  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      std.bits[i] = (std.bits[i] << 1) + big.bits[k--];
    }
  }

  std.bits[3] = big.sign << 7;
  k = 128;

  for (int i = 7; i >= 0; i--) {
    std.bits[3] <<= 1;
    if (big.exp >= k) {
      big.exp -= k;
      std.bits[3]++;
    }
    k >>= 1;
  }

  std.bits[3] <<= 16;
  return std;
}

/**
 * @brief Конвертирует большой децимал в стандартный децимал.
 *
 * @param big Большой децимал.
 * @return Стандартный децимал.
 */
s21_big_decimal s21_to_big_decimal(s21_decimal std) {
  s21_big_decimal big;
  s21_initialise_big(&big);
  big.sign = s21_get_sign(std);
  big.exp = s21_get_exp(std);
  int i = 0;
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 32; k++)
      big.bits[i++] = s21_get_bit_int(std.bits[j], k);
  }
  return big;
}
