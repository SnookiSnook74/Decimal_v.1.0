#include "../test/test.h"
START_TEST(test_ftod_1) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(8e96, &dst);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_ftod_2) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(INFINITY, &dst);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_ftod_3) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(9876543.1234567, &dst);
  ck_assert_int_eq(status, 0);
  // Проверка того, что результат округлен до 7 значащих цифр
}
END_TEST

START_TEST(test_ftod_4) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(1e-29, &dst);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(test_ftod_5) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(-1234.5, &dst);
  ck_assert_int_eq(_find_bit(dst, 127), 1);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_ftod_6) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(1234.554352, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(_find_bit(dst, 127), 0);
  ck_assert_int_eq(dst.bits[0], 1234554);
}
END_TEST

START_TEST(test_ftod_7) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(-1.5543524553, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(_find_bit(dst, 127), 1);
  ck_assert_int_eq(dst.bits[0], 1554352);
}
END_TEST

START_TEST(test_ftod_8) {
  int status = s21_from_float_to_decimal(-1.5543524553, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_ftod_9) {
  s21_decimal dst = {0};
  int status = s21_from_float_to_decimal(-1.5543529553, &dst);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(_find_bit(dst, 127), 1);
  ck_assert_int_eq(dst.bits[0], 1554353);
}
END_TEST

Suite *suite_ftod(void) {
  Suite *s = suite_create("suite_ftod");
  TCase *tc = tcase_create("ftod_tc");
  tcase_add_test(tc, test_ftod_1);
  tcase_add_test(tc, test_ftod_2);
  tcase_add_test(tc, test_ftod_3);
  tcase_add_test(tc, test_ftod_4);
  tcase_add_test(tc, test_ftod_5);
  tcase_add_test(tc, test_ftod_6);
  tcase_add_test(tc, test_ftod_7);
  tcase_add_test(tc, test_ftod_8);
  tcase_add_test(tc, test_ftod_9);

  suite_add_tcase(s, tc);
  return s;
}