#include "../s21_decimal.h"
/*возвращает децимал инициализированный нулем*/
s21_decimal _init_decimal() {
  s21_decimal result = {0};
  return result;
}

/*возвращает состояние бита на указанной позиции 1 или 0*/
int _find_bit(s21_decimal decimal, int elem) {
  // Определение индекса элемента массива и позиции бита внутри этого элемента
  int index = elem / 32;
  int position = elem % 32;
  // Получение нужного элемента массива
  int number = decimal.bits[index];
  // Побитовый сдвиг и получение нужного бита
  int bit = (number >> position) & 1;
  return bit;
}

/*проверяет децимал на валидность*/
bool _is_decimal_correct(s21_decimal decimal) {
  int status = 1;
  if (decimal.bits[3] & 0x7F00FFFFu) {
    status = 0;
  } else {
    int power = decimal.bits[3] >> 16 & 0xFF;
    if (power < 0 || power > 28) {
      status = 0;
    }
  }

  return status;
}

bool _is_zero(s21_decimal value) {
  int result = 1;
  for (int i = 0; i < 3 && result == 1; i++) {
    if (value.bits[i] != 0) result = 0;
  }
  return result;
}

void _set_common_exponent(s21_decimal *value_1, s21_decimal *value_2) {
  //достаем все биты кроме старшего отвечающего за знак
  int v1_exponent = (value_1->bits[3] & 0x7FFFFFFFu) >> 16;
  int v2_exponent = (value_2->bits[3] & 0x7FFFFFFFu) >> 16;
  //вычисляем разницу экспонент.
  int diff = v1_exponent - v2_exponent;
  //экспонента v2  больше значит нужно уменьшать экспoненту и
  //увеличивать мантиссу
  if (diff < 0) {
    diff = -diff;
    _decrease_exponent(value_1, value_2, diff, &v1_exponent, &v2_exponent);
  } else if (diff > 0) {
    _decrease_exponent(value_2, value_1, diff, &v2_exponent, &v1_exponent);
  }
  value_1->bits[3] &= 0x80000000u;  //стираем все данные битс3 кроме знака.
  value_2->bits[3] &= 0x80000000u;
  value_1->bits[3] |= (v1_exponent << 16);  //сохраняем значение экспоненты
  value_2->bits[3] |= (v2_exponent << 16);
}

void _decrease_exponent(s21_decimal *value_1, s21_decimal *value_2, int diff,
                        int *v1_exponent, int *v2_exponent) {
  while (diff) {
    //умножаем value_2 на 10. именно частями,потому что если
    //возвести 10 в степень 28 то получим переполнение инта
    s21_decimal copy = *value_1;
    int mult_result = _muliply_uint(&copy, 10);
    if (mult_result) {
      while (diff) {
        _divide_uint(value_2, 10, value_1->bits[0] % 2);
        diff--;
        (*v2_exponent)--;
      }
    } else {
      *value_1 = copy;
    }
    if (diff > 0) {
      diff--;
      (*v1_exponent)++;
    }
  }
}

int _muliply_uint(s21_decimal *value, uint32_t num) {
  int status = 0;
  uint64_t buffer = 0;
  s21_decimal result = {0};
  for (int i = 0; i < 3; i++) {
    buffer += (uint64_t)value->bits[i] * num;
    result.bits[i] = buffer & 0xFFFFFFFFu;
    buffer >>= 32;
  }
  if (buffer)
    status = 1;
  else
    result.bits[3] = value->bits[3];
  *value = result;
  return status;
}

/*делит мантиссу decimal на любой int, при делении на 0 возвращает 3*/
int _divide_uint(s21_decimal *value, uint32_t num, int round_type) {
  int status = 0;
  if (num == 0) {
    status = 3;
  } else {
    uint64_t buffer = 0;  // Используем буфер размером 64 бита
    s21_decimal result = {0};  // Сюда записываем результат деления
    for (int i = 2; i >= 0; i--) {
      // Сдвигаем буфер на 32 бита и добавляем текущий
      // блок value->bits[i]
      buffer = (buffer << 32) | value->bits[i];
      result.bits[i] = buffer / num;  // Выполняем деление
      buffer %= num;  // Сохраняем остаток в буфере
    }
    if (buffer) {
      /*округляем в зависимости от типа округления*/
      _parse_rounding(&result, buffer, num, round_type);
    }
    *value = result;  // Иначе перезаписываем результат входящего децимала
  }
  return status;
}

/*функция округления при делении на целое число*/
void _parse_rounding(s21_decimal *result, uint64_t buffer, uint32_t num,
                     int round_type) {
  if (round_type == 1) {
    if (buffer / (float)num >= .5) {
      result->bits[0]++;
    }
  }
}

void _set_bit(s21_decimal *decimal, int elem) {
  int index = elem / 32;
  int position = elem % 32;
  decimal->bits[index] |= (1u << position);
}

int count_digits(int n) {
  int count = 0;
  if (n == 0) return 1;  // Если число равно нулю, то возвращаем 1
  if (n < 0) n = -n;  // Для отрицательных чисел делаем число положительным
  while (n != 0) {
    n /= 10;
    ++count;
  }
  return count;
}

int _left_shift(s21_decimal *value) {
  int status = 0;
  int b0 = _find_bit(*value, 31);
  int b1 = _find_bit(*value, 63);
  int b2 = _find_bit(*value, 95);
  if (b2) {
    status = 1;
  } else {
    value->bits[0] <<= 1;
    value->bits[1] <<= 1;
    value->bits[1] += b0;
    value->bits[2] <<= 1;
    value->bits[2] += b1;
  }
  return status;
}

int _binary_addition(int bit1, int bit2, int *remainder) {
  int result = bit1 + bit2 + (*remainder);
  if (result == 1) {
    *remainder = 0;
    result = 1;
  } else if (result == 2) {
    *remainder = 1;
    result = 0;
  } else if (result == 3) {
    *remainder = 1;
    result = 1;
  } else {
    *remainder = 0;
    result = 0;
  }
  return result;
}

void _binary_not(s21_decimal *value) {
  value->bits[0] = ~value->bits[0];
  value->bits[1] = ~value->bits[1];
  value->bits[2] = ~value->bits[2];
}

void _set_scale(s21_decimal *value, int exp) {
  value->bits[3] = value->bits[3] | (exp << 16);
}

void _set_sign(s21_decimal *value, int sign) {
  int scale = value->bits[3] & 0x7fffffff;
  value->bits[3] = scale + ((unsigned)sign << 31);
}

int s21_get_scale(s21_decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}

void s21_set_bit(s21_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  int return_status = 0;  // Результат, который будет возвращён в конце функции
  // Проверка, что dst не является нулевым указателем
  if (dst == NULL) {
    return_status = 1;
  } else {
    // Отдельная обработка для чисел, равных нулю
    if (_is_zero(src) == 1 && (src.bits[3] & 0x7FFFFFFF) == 0) {
      int sign_bit = _find_bit(src, 127);
      *dst = sign_bit ? 0.0f * -1 : 0.0f;
    } else {
      // Получаем знак, экспоненту и мантиссу из src
      int sign_bit = _find_bit(src, 127);
      long double temp = 0.0L;
      for (int i = 0; i < 96; i++) {
        temp += _find_bit(src, i) * powl(2, i);
      }
      temp = temp * powl(10, -s21_get_scale(src));
      if (sign_bit) temp = temp * (-1);
      // Проверка на наличие больших, малых или бесконечных значений
      if ((temp != 0.0 && fabsl(temp) < 1.0e-28) || fabsl(temp) > s21_MAXDEC) {
        *dst = 0.0L;
        return_status = 1;
      } else {
        // Преобразование мантиссы к формату с плавающей точкой
        *dst = temp;
      }
    }
  }
  return return_status;
}
