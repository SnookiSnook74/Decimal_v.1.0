#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal ten;
  *result = _init_decimal();
  s21_from_float_to_decimal(10, &ten);
  int remainder = 0;
  int bit1, bit2;

  int sign1 = _find_bit(value_1, 127);
  int sign2 = _find_bit(value_2, 127);
  int exp1 = (value_1.bits[3] >> 16) & 0xFF;
  int exp2 = (value_2.bits[3] >> 16) & 0xFF;
  int exp = exp1 >= exp2 ? exp1 : exp2;

  if (sign1 == 1 && sign2 == 0) {
    value_1.bits[3] = exp1 << 16;
    status = s21_sub(value_2, value_1, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = s21_sub(value_1, value_2, result);
  } else {
    _set_common_exponent(&value_1, &value_2);

    for (int i = 0; i < 96; i++) {
      bit1 = _find_bit(value_1, i);
      bit2 = _find_bit(value_2, i);

      int resultBit = _binary_addition(bit1, bit2, &remainder);
      if (resultBit == 1) {
        _set_bit(result, i);
      }
    }
    result->bits[3] = exp << 16 | (unsigned)(sign1 | sign2) << 31;
    if (_find_bit(*result, 127) == 1 && remainder == 1) {
      remainder = 2;
    }
    status = remainder;
  }
  return status;
}
