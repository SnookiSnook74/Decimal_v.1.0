#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (_is_decimal_correct(value) && result) {
    value.bits[3] ^= (1u << 31);
    *result = value;
  } else {
    status = 1;
  }

  return status;
}
