#include "../s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  if (_is_zero(a) && _is_zero(b)) return 0;
  // Получаем знаки чисел
  int signA = (a.bits[3] & 0x80000000) != 0;
  int signB = (b.bits[3] & 0x80000000) != 0;
  int result = 0;
  // Если знаки различны
  if (signA != signB) {
    // Если знак a положительный и знак b отрицательный, a > b
    result = !signA;
  }
  // Если знаки равны, сравниваем мантиссы чисел
  else {
    // Выравниваем показатели степени копий
    _set_common_exponent(&a, &b);
    // Сравниваем мантиссы чисел
    int status = 1;
    for (int i = 2; i >= 0 && status == 1; --i) {
      if (a.bits[i] != b.bits[i]) {
        status = 0;
        // Если знаки положительные, больше число с большей мантиссой
        // Если знаки отрицательные, больше число с меньшей мантиссой
        result =
            (signA == 0) ? (a.bits[i] > b.bits[i]) : (a.bits[i] < b.bits[i]);
      }
    }
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  if (_is_zero(a) && _is_zero(b)) return 1;
  int is_less = s21_is_less(a, b);
  // если a не меньше b, оно либо равно b, либо больше b, и функция
  // возвращает 1.
  return !is_less;
}
