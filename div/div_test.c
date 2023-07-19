#include "../test/test.h"

START_TEST(s21_div_1) {
  s21_decimal src1, src2, result, origin;
  // 30064771176
  // 3
  // 10021590392
  src1.bits[0] = 0b00000000000000000000000001101000;
  src1.bits[1] = 0b00000000000000000000000000000111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b01010101010101010101010101111000;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_2) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = -2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

START_TEST(s21_div_4) {
  s21_decimal src1, src2, result, origin;
  // -30064771176
  // 2
  // 10021590392
  src1.bits[0] = 0b00000000000000000000000001101000;
  src1.bits[1] = 0b00000000000000000000000000000111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b10000000000000000000000000110100;
  origin.bits[1] = 0b00000000000000000000000000000011;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_5) {
  s21_decimal src1, src2, result, origin;
  // 0
  // 0.015
  // 0
  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000001111;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(s21_div_6) {
  s21_decimal src1, src2, result, origin;
  s21_from_int_to_decimal(-101, &src1);
  s21_from_float_to_decimal(10.1, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  origin.bits[0] = 0b00000000000000000000000000001010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  //       printf("%u\n", src1.bits[0]);
  //    printf("%u\n", src1.bits[1]);
  //     printf("%u\n", src1.bits[2]);
  //      printf("%u\n", src1.bits[3]);

  //     printf("%u\n", src2.bits[0]);
  //    printf("%u\n", src2.bits[1]);
  //     printf("%u\n", src2.bits[2]);
  //      printf("%u\n", src2.bits[3]);

  //   printf("%u\n", result.bits[0]);
  //    printf("%u\n", result.bits[1]);
  //     printf("%u\n", result.bits[2]);
  //      printf("%u\n", result.bits[3]);
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(s21_is_equal(result, origin), 1);
}
END_TEST

START_TEST(s21_div_8) {
  s21_decimal src1, src2, result;
  float a = -115.2;
  float b = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  int check = s21_div(src1, src2, &result);
  int check_origin = 3;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(s21_div_9) {
  s21_decimal src1, src2, result;
  src1.bits[0] = 0x0006BFD0;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000028;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[0], 0x00002B32);
}
END_TEST

START_TEST(s21_div_10) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{70, 0, 0, 0}};
  _set_scale(&value_1, 1);
  _set_scale(&value_2, 2);

  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal value_1 = {{0x88888888, 0x88888888, 0x88888888, 0}};
  s21_decimal value_2 = {{0x2, 0, 0, 0}};
  _set_sign(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{0x44444444, 0x44444444, 0x44444444, 0}};
  _set_sign(&check, 1);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_12) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  _set_scale(&value_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{1000u, 0, 0, 0}};
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_13) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  _set_scale(&value_1, 2);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal check = {{10u, 0, 0, 0}};
  _set_scale(&check, 4);
  int return_value = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_div_14) {
  s21_decimal value1 = {.bits[0] = 4, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {.bits[0] = 2, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST
/*простое деление большие числа*/
START_TEST(s21_div_15) {
  s21_decimal value1 = {.bits[0] = 0, .bits[1] = 4, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {.bits[0] = 0, .bits[1] = 2, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST
/*с остатком малые числа*/
START_TEST(s21_div_16) {
  s21_decimal value1 = {.bits[0] = 3, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {.bits[0] = 2, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3] >> 16 & 0xff, 1);
}
END_TEST

START_TEST(s21_div_17) {
  s21_decimal value1 = {.bits[0] = 0, .bits[1] = 3, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {.bits[0] = 3, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 1);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST
/*деление 0 на не ноль*/
START_TEST(s21_div_18) {
  s21_decimal value1 = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {.bits[0] = 3, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_div_19) {
  s21_decimal value1 = {
      .bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 1u << 31};
  s21_decimal value2 = {.bits[0] = 3, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal result = _init_decimal();
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_div_20) {
  s21_decimal value1 = {.bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {
      .bits[0] = 3, .bits[1] = 0, .bits[2] = 0, .bits[3] = 1u << 31};
  s21_decimal result = {0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST
/*деление на ноль*/
START_TEST(s21_div_21) {
  s21_decimal value1 = {.bits[0] = 1, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  s21_decimal value2 = {
      .bits[0] = 0, .bits[1] = 0, .bits[2] = 0, .bits[3] = 1u << 31};
  s21_decimal result = _init_decimal();
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 3);
}
END_TEST
/*получение положительной бесконечности */
START_TEST(s21_div_22) {
  s21_decimal value1 = {.bits[0] = 1, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  _set_scale(&value1, 28);
  s21_decimal value2 = {
      .bits[0] = 0, .bits[1] = 0, .bits[2] = 0xffffffffu, .bits[3] = 0};
  s21_decimal result = {0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 1);  //тут 1
}
END_TEST

/*получение отрицательной бесконечности */
START_TEST(s21_div_23) {
  s21_decimal value1 = {.bits[0] = 1, .bits[1] = 0, .bits[2] = 0, .bits[3] = 0};
  _set_scale(&value1, 28);
  s21_decimal value2 = {
      .bits[0] = 0, .bits[1] = 0, .bits[2] = 0xffffffffu, .bits[3] = 1u << 31};
  s21_decimal result = {0};
  int sub_result = s21_div(value1, value2, &result);
  ck_assert_int_eq(sub_result, 2);  //тут 2
}
END_TEST

Suite *suite_div(void) {
  Suite *s = suite_create("suite_div");
  TCase *tc = tcase_create("div_tc");
  tcase_add_test(tc, s21_div_1);
  tcase_add_test(tc, s21_div_2);
  tcase_add_test(tc, s21_div_3);
  tcase_add_test(tc, s21_div_4);
  tcase_add_test(tc, s21_div_5);
  tcase_add_test(tc, s21_div_6);
  tcase_add_test(tc, s21_div_8);
  tcase_add_test(tc, s21_div_9);
  tcase_add_test(tc, s21_div_10);
  tcase_add_test(tc, s21_div_11);
  tcase_add_test(tc, s21_div_12);
  tcase_add_test(tc, s21_div_13);
  tcase_add_test(tc, s21_div_14);
  tcase_add_test(tc, s21_div_15);
  tcase_add_test(tc, s21_div_16);
  tcase_add_test(tc, s21_div_17);
  tcase_add_test(tc, s21_div_18);
  tcase_add_test(tc, s21_div_19);
  tcase_add_test(tc, s21_div_20);
  tcase_add_test(tc, s21_div_21);
  tcase_add_test(tc, s21_div_22);
  tcase_add_test(tc, s21_div_23);
  suite_add_tcase(s, tc);
  return s;
}