#include "../test/test.h"

START_TEST(test_negate_v1) {
  s21_decimal value = {
      .bits[0] = 1294567, .bits[1] = 0, .bits[2] = 0, .bits[3] = (1u << 31)};
  s21_decimal result = {0};
  s21_negate(value, &result);
  ck_assert_int_eq(result.bits[0], 1294567);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST
/*некорректная экспонента*/
START_TEST(test_negate_v4) {
  s21_decimal value1 = {.bits[0] = 0xffffffffu,
                        .bits[1] = 0xffffffffu,
                        .bits[2] = 0xffffffffu,
                        .bits[3] = 0b10000000111111110000000000000000};
  s21_decimal result = {0};
  int sub_result = s21_negate(value1, &result);
  ck_assert_int_eq(sub_result, 1);
}
END_TEST
/*null*/
START_TEST(test_negate_v5) {
  s21_decimal value1 = {.bits[0] = 0xffffffffu,
                        .bits[1] = 0xffffffffu,
                        .bits[2] = 0xffffffffu,
                        .bits[3] = 0};
  int sub_result = s21_negate(value1, NULL);
  ck_assert_int_eq(sub_result, 1);
}
END_TEST
/*лишние биты*/
START_TEST(test_negate_v6) {
  s21_decimal value1 = {.bits[0] = 0xffffffffu,
                        .bits[1] = 0xffffffffu,
                        .bits[2] = 0xffffffffu,
                        .bits[3] = 0b00000000000000000000000000100000};
  s21_decimal result = {0};
  int sub_result = s21_negate(value1, &result);
  ck_assert_int_eq(sub_result, 1);
}
END_TEST

START_TEST(test_negate_v2) {
  s21_decimal value = {.bits[0] = 1294567,
                       .bits[1] = 0,
                       .bits[2] = 0,
                       .bits[3] = 0b10000000000010000000000000000000};
  s21_decimal result = {0};
  s21_negate(value, &result);
  ck_assert_int_eq(result.bits[0], 1294567);
  ck_assert_int_eq(result.bits[3], 0b00000000000010000000000000000000);
}
END_TEST

START_TEST(test_negate_v3) {
  s21_decimal value = {.bits[0] = 1294567,
                       .bits[1] = 0,
                       .bits[2] = 0,
                       .bits[3] = 0b00000000000010000000000000000000};
  s21_decimal result = {0};
  s21_negate(value, &result);
  ck_assert_int_eq(result.bits[0], 1294567);
  ck_assert_int_eq(result.bits[3], 0b10000000000010000000000000000000);
}
END_TEST

Suite *suite_negate(void) {
  Suite *s = suite_create("suite_negate");
  TCase *tc = tcase_create("negate_tc");
  tcase_add_test(tc, test_negate_v1);
  tcase_add_test(tc, test_negate_v2);
  tcase_add_test(tc, test_negate_v3);
  tcase_add_test(tc, test_negate_v4);
  tcase_add_test(tc, test_negate_v5);
  tcase_add_test(tc, test_negate_v6);

  suite_add_tcase(s, tc);
  return s;
}