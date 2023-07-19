#include "../test/test.h"

START_TEST(test_equal_1) {
  // Проверка равенства двух одинаковых чисел.
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16);
  b = a;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST
// Проверка равенства чисел с одинаковыми мантиссами и разными знаками.
START_TEST(test_equal_2) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16);
  b = a;
  b.bits[3] |= 0x80000000;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST
// Проверка равенства чисел с разными мантиссами.
START_TEST(test_equal_3) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16);
  b.bits[0] = 123455;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (5 << 16);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST
// Разные экспоненты
START_TEST(test_equal_4) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16);
  b.bits[0] = 123456;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (6 << 16);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST
// Проверка равенства чисел, где одно число является нулем.
START_TEST(test_equal_5) {
  s21_decimal a, b;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  b.bits[0] = 123456;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (5 << 16);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

// Оба нулевые

START_TEST(test_equal_6) {
  s21_decimal a, b;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  b = a;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

// Проверка равенства максимального и минимального допустимых значений.
START_TEST(test_equal_7) {
  s21_decimal a, b;
  a.bits[0] = INT_MAX;
  a.bits[1] = INT_MAX;
  a.bits[2] = INT_MAX;
  a.bits[3] = (28 << 16) | 0x8000;  // Максимальное отрицательное число
  b.bits[0] = INT_MIN;
  b.bits[1] = INT_MIN;
  b.bits[2] = INT_MIN;
  b.bits[3] = 28 << 16;  // Максимальное положительное число
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

// Проверка равенства чисел с максимально возможными мантиссами и разными
// знаками.
START_TEST(test_equal_8) {
  s21_decimal a, b;
  a.bits[0] = INT_MAX;
  a.bits[1] = INT_MAX;
  a.bits[2] = INT_MAX;
  a.bits[3] = (5 << 16);
  b = a;
  b.bits[3] |= 0x80000000;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST
// Проверка равенства чисел с минимально возможными мантиссами и разными
// знаками.
START_TEST(test_equal_9) {
  s21_decimal a, b;
  a.bits[0] = INT_MIN;
  a.bits[1] = INT_MIN;
  a.bits[2] = INT_MIN;
  a.bits[3] = (5 << 16);
  b = a;
  b.bits[3] |= 0x80000000;
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST
START_TEST(test_not_equal_1) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  b = a;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_not_equal_2) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  b = a;
  b.bits[0] = 123457;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_3) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16);
  b = a;
  b.bits[3] = (6 << 16);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_4) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  b = a;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_5) {
  s21_decimal a, b;
  a.bits[0] = INT_MAX;
  a.bits[1] = INT_MAX;
  a.bits[2] = INT_MAX;
  a.bits[3] = (28 << 16) | 0x8000;
  b.bits[0] = INT_MIN;
  b.bits[1] = INT_MIN;
  b.bits[2] = INT_MIN;
  b.bits[3] = 28 << 16;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_6) {
  s21_decimal a, b;
  a.bits[0] = INT_MIN;
  a.bits[1] = INT_MIN;
  a.bits[2] = INT_MIN;
  a.bits[3] = (28 << 16) | 0x8000;
  b.bits[0] = 0;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_7) {
  s21_decimal a, b;
  a.bits[0] = INT_MAX;
  a.bits[1] = INT_MAX;
  a.bits[2] = INT_MAX;
  a.bits[3] = 28 << 16;
  b.bits[0] = 0;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_8) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16) | 0x8000;
  b.bits[0] = 123455;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (5 << 16) | 0x8000;
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal_9) {
  s21_decimal a, b;
  a.bits[0] = 123456;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (5 << 16) | 0x8000;
  b = a;
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

Suite *suite_is_equal(void) {
  Suite *s = suite_create("suite_is_equal");
  TCase *tc = tcase_create("is_equal_tc");
  tcase_add_test(tc, test_equal_1);
  tcase_add_test(tc, test_equal_2);
  tcase_add_test(tc, test_equal_3);
  tcase_add_test(tc, test_equal_4);
  tcase_add_test(tc, test_equal_5);
  tcase_add_test(tc, test_equal_6);
  tcase_add_test(tc, test_equal_7);
  tcase_add_test(tc, test_equal_8);
  tcase_add_test(tc, test_equal_9);
  tcase_add_test(tc, test_not_equal_1);
  tcase_add_test(tc, test_not_equal_2);
  tcase_add_test(tc, test_not_equal_3);
  tcase_add_test(tc, test_not_equal_4);
  tcase_add_test(tc, test_not_equal_5);
  tcase_add_test(tc, test_not_equal_6);
  tcase_add_test(tc, test_not_equal_7);
  tcase_add_test(tc, test_not_equal_8);
  tcase_add_test(tc, test_not_equal_9);

  suite_add_tcase(s, tc);
  return s;
}