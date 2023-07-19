#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal ten;
  s21_decimal valueBuff = _init_decimal();
  s21_decimal one = {{1, 0, 0, 0}};
  s21_from_float_to_decimal(10, &ten);
  *result = _init_decimal();
  int sign1 = _find_bit(value_1, 127);
  int sign2 = _find_bit(value_2, 127);
  if (sign1 == 1 && sign2 == 0) {
    _set_bit(&value_2, 127);
    status = s21_add(value_1, value_2, result);
  } else if (sign1 == 0 && sign2 == 1) {
    _set_sign(&value_2, 0);
    status = s21_add(value_1, value_2, result);
  } else {
    _set_common_exponent(&value_1, &value_2);
    int exp = (value_1.bits[3] >> 16) & 0xFF;
    sign2 = sign2 ^ 1;
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    if (s21_is_greater(value_1, value_2) == 1) {
      _binary_not(&value_2);
      status = s21_add(value_1, value_2, result) ^ 1;
      result->bits[3] = exp << 16 | (unsigned)(sign1) << 31;
      one.bits[3] = exp << 16 | (unsigned)(sign1) << 31;
      s21_add(*result, one, &valueBuff);
      *result = valueBuff;
    } else if (s21_is_less(value_1, value_2) == 1) {
      _binary_not(&value_1);
      status = s21_add(value_2, value_1, result) ^ 1;
      result->bits[3] = ((unsigned)(sign2) << 31) + (exp << 16);
      one.bits[3] = ((unsigned)(sign2) << 31) + (exp << 16);
      s21_add(*result, one, &valueBuff);
      *result = valueBuff;
    } else {
      status = 0;
    }
  }
  return status;
}