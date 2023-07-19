#include "../test/test.h"

START_TEST(test_decimal_to_float_1) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 18122;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 3 << 16;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 18.122);
}
END_TEST

START_TEST(test_decimal_to_float_2) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 18122;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 3 << 16;
  _set_bit(&a, 127);
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, -18.122);
}
END_TEST

START_TEST(test_decimal_to_float_3) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 344218122;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 344218122.);
}
END_TEST

START_TEST(test_decimal_to_float_4) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 32;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 32.);
}
END_TEST

START_TEST(test_decimal_to_float_5) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 0xFFFFFF;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 16777215);
}
END_TEST

START_TEST(test_decimal_to_float_6) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

START_TEST(test_decimal_to_float_7) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 0);
}
END_TEST

START_TEST(test_decimal_to_float_8) {
  s21_decimal a = {0};
  float test = 0;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 1;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 0);
}
END_TEST

START_TEST(test_decimal_to_float_9) {
  s21_decimal a = {0};
  float test;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 0);
}
END_TEST

START_TEST(test_decimal_to_float_10) {
  s21_decimal a = {0};
  float test;
  a.bits[0] = 123456789;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 3 << 16;
  s21_from_decimal_to_float(a, &test);
  ck_assert_float_eq(test, 123456.789062);
}
END_TEST

START_TEST(test_decimal_to_float_11) {
  s21_decimal a = {0};
  int result = s21_from_decimal_to_float(a, NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_to_float_12) {
  s21_decimal a = {0};
  float test;
  a.bits[0] = 1;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 30 << 16;
  int result = s21_from_decimal_to_float(a, &test);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *suite_to_float(void) {
  Suite *s = suite_create("suite_to_float");
  TCase *tc = tcase_create("_to_float_tc");
  tcase_add_test(tc, test_decimal_to_float_1);
  tcase_add_test(tc, test_decimal_to_float_2);
  tcase_add_test(tc, test_decimal_to_float_3);
  tcase_add_test(tc, test_decimal_to_float_4);
  tcase_add_test(tc, test_decimal_to_float_5);
  tcase_add_test(tc, test_decimal_to_float_6);
  tcase_add_test(tc, test_decimal_to_float_7);
  tcase_add_test(tc, test_decimal_to_float_8);
  tcase_add_test(tc, test_decimal_to_float_9);
  tcase_add_test(tc, test_decimal_to_float_10);
  tcase_add_test(tc, test_decimal_to_float_11);
  tcase_add_test(tc, test_decimal_to_float_12);

  suite_add_tcase(s, tc);
  return s;
}