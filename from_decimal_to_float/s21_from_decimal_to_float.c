#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
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
      int exponent = (src.bits[3] & 0x7FFFFFFF) >> 16;
      // Обратное преобразование мантиссы
      double mantissa = 0;
      for (int k = 0; k < 96; k++) {
        if (_find_bit(src, k)) {
          mantissa += pow(2.0, k);
        }
      }
      // Обратная нормализация
      if (exponent > 0) {
        mantissa /= pow(10.0, exponent);
      } else {
        mantissa *= pow(10.0, -exponent);
      }
      // Применение знака
      if (sign_bit) {
        mantissa = -mantissa;
      }
      // Проверка на наличие больших, малых или бесконечных значений
      if ((mantissa != 0.0 && fabs(mantissa) < 1.0e-28) ||
          fabs(mantissa) > s21_MAXDEC) {
        *dst = 0.0f;
        return_status = 1;
      } else {
        // Преобразование мантиссы к формату с плавающей точкой
        *dst = (float)mantissa;
      }
    }
  }
  return return_status;
}
