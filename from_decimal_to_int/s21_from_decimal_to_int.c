#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_status = 0;
  if (dst == NULL) {
    return_status = 1;
  } else {
    // Получение знакового бита и экспоненты
    int sign_bit = _find_bit(src, 127);
    unsigned int exponent = (src.bits[3] & 0x00FF0000u) >> 16;
    // Проверка, есть ли в bits[1], bits[2] так как int может быть только в
    // bits[0]
    if ((src.bits[1] != 0) || (src.bits[2] != 0)) {
      return_status = 1;
      // Проверка, что экспонента в допустимом диапазоне от 0 до 28
    } else if (exponent > 28) {
      return_status = 1;
    } else if ((sign_bit == 0 && src.bits[0] > INT_MAX) ||
               (sign_bit == 1 && src.bits[0] > (unsigned int)INT_MAX + 1)) {
      return_status = 1;
    } else {
      // Применяем экспоненту, делая деление на соответствующую степень 10
      unsigned int divisor = pow(10, exponent);
      src.bits[0] /= divisor;
      *dst = src.bits[0];  // Присваиваем значение dst
      if (sign_bit == 1) {
        *dst = -*dst;  // Меняем знак на отрицательный, если это необходимо
      }
    }
  }
  return return_status;
}
