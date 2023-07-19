#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  for (int i = 0; i < 4; ++i) {
    result->bits[i] = 0;
  }
  int return_status = 0;
  if (s21_get_scale(value)) {
    long double new_int = 0.0;
    return_status = s21_from_decimal_to_double(value, &new_int);
    if (return_status != 0 || isnan(new_int) || isinf(new_int)) {
      return_status = 1;
    } else {
      new_int = floor(new_int);  // округляем до ближайшего меньшего целого.
      if (new_int < 0.0) {
        s21_set_bit(result, 127, 1);
        new_int *= -1;
      }
      for (int i = 0; new_int >= 1 && i < 96; i++) {
        s21_set_bit(result, i, (int)fmod(new_int, 2));
        new_int /= 2;
      }
      _set_scale(result, 0);
    }
  } else {
    for (int i = 0; i < 4; ++i) {
      result->bits[i] = value.bits[i];
    }
  }
  return return_status;
}