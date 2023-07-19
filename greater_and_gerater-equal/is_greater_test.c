#include "../test/test.h"

START_TEST(test_is_greater) {
  s21_decimal a;
  s21_decimal b;

  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000u;
  ck_assert_int_eq(s21_is_greater(a, b), 1);

  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = a.bits[1] = a.bits[2] = 200;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_greater(a, b), 1);

  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 200;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = a.bits[1] = a.bits[2] = 200;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 200;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_greater(a, b), 1);

  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_greater(a, b), 0);

  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_greater(a, b), 1);

  a.bits[0] = a.bits[1] = a.bits[2] = UINT_MAX;
  a.bits[3] = (28 << 16);
  b.bits[0] = b.bits[1] = b.bits[2] = UINT_MAX;
  b.bits[3] = (28 << 16) | 0x80000000;
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

Suite *suite_greater(void) {
  Suite *s = suite_create("suite_greater");
  TCase *tc = tcase_create("greater_tc");
  tcase_add_test(tc, test_is_greater);
  suite_add_tcase(s, tc);
  return s;
}