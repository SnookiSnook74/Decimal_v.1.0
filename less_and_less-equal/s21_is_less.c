#include "../s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  if (_is_zero(a) && _is_zero(b)) return 0;
  // Получаем знаки чисел
  uint32_t signA = (a.bits[3] & 0x80000000u);
  uint32_t signB = (b.bits[3] & 0x80000000u);
  int result = 0;
  // Если знаки различны
  if (signA != signB) {
    // Если знак a отрицательный и знак b положительный, a < b
    if (signA) result = 1;
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
        // Если знаки положительные, меньше число с меньшей мантиссой
        // Если знаки отрицательные, меньше число с большей мантиссой
        result =
            (signA == 0) ? (a.bits[i] < b.bits[i]) : (a.bits[i] > b.bits[i]);
      }
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  if (_is_zero(a) && _is_zero(b)) return 1;
  int is_great = s21_is_greater(a, b);
  // eсли a не больше b, это автоматически означает, что a меньше или равно b.
  return !is_great;
}
