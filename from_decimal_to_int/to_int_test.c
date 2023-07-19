#include "../test/test.h"

START_TEST(decimal_to_int_1) {
  s21_decimal a = {0};
  int answer = s21_from_decimal_to_int(a, NULL);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_2) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = 5000000;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, a.bits[0]);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(decimal_to_int_3) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = 5000000;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0x80000000;
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, -5000000);
  ck_assert_int_eq(a.bits[3], 0x80000000);
}
END_TEST

START_TEST(decimal_to_int_4) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MAX;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, INT_MAX);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(decimal_to_int_5) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MAX;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, INT_MAX);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(decimal_to_int_6) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MAX;
  a.bits[1] = 123;
  a.bits[2] = 0;
  a.bits[3] = 0;
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, 0);
}
END_TEST

START_TEST(decimal_to_int_7) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MAX;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 30 << 16;
  int answer = s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_8) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = 2;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 30 << 16;
  int answer = s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_9) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = UINT_MAX;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  int answer = s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_10) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MIN;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  int answer = s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_11) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = 1;
  a.bits[1] = 2;
  a.bits[2] = 3;
  a.bits[3] = 0;
  int answer = s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(answer, 1);
}
END_TEST

START_TEST(decimal_to_int_12) {
  s21_decimal a;
  int test = 0;
  a.bits[0] = INT_MAX + 1u;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  _set_bit(&a, 127);
  s21_from_decimal_to_int(a, &test);
  ck_assert_int_eq(test, INT_MIN);
}
END_TEST

Suite *suite_to_int(void) {
  Suite *s = suite_create("suite_to_int");
  TCase *tc = tcase_create("_to_int_tc");
  tcase_add_test(tc, decimal_to_int_1);
  tcase_add_test(tc, decimal_to_int_2);
  tcase_add_test(tc, decimal_to_int_3);
  tcase_add_test(tc, decimal_to_int_4);
  tcase_add_test(tc, decimal_to_int_5);
  tcase_add_test(tc, decimal_to_int_6);
  tcase_add_test(tc, decimal_to_int_7);
  tcase_add_test(tc, decimal_to_int_8);
  tcase_add_test(tc, decimal_to_int_9);
  tcase_add_test(tc, decimal_to_int_10);
  tcase_add_test(tc, decimal_to_int_11);
  tcase_add_test(tc, decimal_to_int_12);

  suite_add_tcase(s, tc);
  return s;
}