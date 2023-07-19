#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_status = 0;
  if (dst == NULL) {
    return_status = 1;
  } else {
    // очищаем все bits
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    // если исходное число отрицательное, устанавливаем знаковый бит в bits[3]
    if (src < 0) {
      // Меняем бит на 1 чтобы получить отрицательный знак
      _set_bit(dst, 127);
      if (src == INT_MIN) {
        src = -src - 1;
      } else {
        src = -src;  // приводим исходное число к положительному значению
      }
    }
    // преобразуем int в s21_decimal
    dst->bits[0] = src;
  }
  return return_status;
}
