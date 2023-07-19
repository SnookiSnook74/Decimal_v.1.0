#include "../s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  // Проверяем, являются ли оба числа нулями независимо от знака
  if (_is_zero(a) && _is_zero(b)) return 1;
  // Получаем знаки чисел
  int signA = (a.bits[3] & 0x80000000) != 0;
  int signB = (b.bits[3] & 0x80000000) != 0;
  // Если знаки чисел различаются, то числа не равны
  if (signA != signB) {
    return 0;
  }
  // Выравниваем показатели степени копий
  _set_common_exponent(&a, &b);
  // Сравниваем мантиссы чисел
  int is_equal = 1;
  for (int i = 2; i >= 0 && is_equal; --i) {
    if (a.bits[i] != b.bits[i]) {
      is_equal = 0;
    }
  }

  return is_equal;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  // Просто обратная функций от сравнения
  return !s21_is_equal(a, b);
}
