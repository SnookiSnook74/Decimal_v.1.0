#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_status = 0;
  if ((src != 0.0f && fabs(src) < 1e-28f) || fabs(src) > s21_MAXDEC) {
    return 1;
  }
  if (dst) {
    dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -src;
    }
    int new = (int)src;
    int exp = 0;
    while (src - ((float)new / (int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(int)(pow(10, exp));
    }
    s21_from_int_to_decimal(new, dst);
    if (count_digits(dst->bits[0]) > 7) {
      exp--;
      dst->bits[0] /= 10.0;
    }
    unsigned int mask = (0u | exp) << 16;
    if (sign) {
      mask |= 1u << 31;
    }
    dst->bits[3] |= mask;
  } else {
    return_status = 1;
  }
  return return_status;
}
