#include "../test/test.h"

START_TEST(test_s21_is_less) {
  // Инициализация чисел
  s21_decimal a;
  s21_decimal b;

  // Тест 1: 0 < 1
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;  // знак 0, степень 0
  b.bits[0] = 1;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;  // знак 0, степень 0
  ck_assert_int_eq(s21_is_less(a, b), 1);

  // Тест 2: -1 < 1
  a.bits[0] = UINT_MAX;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 1u << 31;  // знак 1, степень 0
  b.bits[0] = UINT_MAX;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;  // знак 0, степень 0
  ck_assert_int_eq(s21_is_less(a, b), 1);

  // Тест 3: 1 не меньше 1
  a.bits[0] = 1;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;  // знак 0, степень 0
  b.bits[0] = 1;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;  // знак 0, степень 0
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 4: проверка работы со знаками и степенями
  a.bits[0] = 10;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0x80000000;  // знак 1, степень 0
  b.bits[0] = 10;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0;  // знак 0, степень 0
  ck_assert_int_eq(s21_is_less(a, b), 1);

  // Тест 5: проверка работы со знаками и степенями
  a.bits[0] = 10;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (2 << 16);

  b.bits[0] = 100000;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (1 << 16);
  ck_assert_int_eq(s21_is_less(a, b), 1);

  // Тест 5: a == b
  a.bits[0] = 10;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (2 << 16);

  b.bits[0] = 10;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (2 << 16);

  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 7: a > b
  a.bits[0] = 100000;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = (2 << 16);

  b.bits[0] = 10;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = (1 << 16);

  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 8: Положительное и отрицательное число с одинаковой мантиссой
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 9: Два одинаковых положительных числа
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 10: Два одинаковых отрицательных числа
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 11: Ноль и отрицательное число
  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 12: Ноль и положительное число
  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less(a, b), 1);

  // Тест 13: Максимальное положительное и максимальное отрицательное число
  a.bits[0] = a.bits[1] = a.bits[2] = UINT_MAX;
  a.bits[3] = (28 << 16);  // максимальный показатель степени

  b.bits[0] = b.bits[1] = b.bits[2] = UINT_MAX;
  b.bits[3] = (28 << 16) | 0x80000000;  // максимальная негативная экспонента
  ck_assert_int_eq(s21_is_less(a, b), 0);

  // Тест 14: Максимальное положительное и максимальное отрицательное число
  a.bits[0] = a.bits[1] = a.bits[2] = UINT_MAX;
  a.bits[3] = (28 << 16) | 0x80000000;  // максимальный показатель отрицательный

  b.bits[0] = b.bits[1] = b.bits[2] = UINT_MAX;
  b.bits[3] = (28 << 16);  // максимальный положительный
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal a, b;

  // Тест 1: Два одинаковых положительных числа
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 2: Два одинаковых отрицательных числа
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 3: Ноль и отрицательное число
  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);

  // Тест 4: Ноль и положительное число
  a.bits[0] = a.bits[1] = a.bits[2] = a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 5: Максимальное положительное и максимальное отрицательное число
  a.bits[0] = a.bits[1] = a.bits[2] = UINT_MAX;
  a.bits[3] = (28 << 16);  // максимальный показатель степени
  b.bits[0] = b.bits[1] = b.bits[2] = UINT_MAX;
  b.bits[3] = (28 << 16) | 0x80000000;  // максимальная негативная экспонента
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);

  // Тест 6: Два положительных числа, одно больше другого
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 200;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 7: Два отрицательных числа, одно меньше другого
  a.bits[0] = a.bits[1] = a.bits[2] = 200;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 8: Два числа с одинаковой мантиссой, но разными знаками
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);

  // Тест 9: Два числа с одинаковыми знаками, но разной мантиссой
  a.bits[0] = a.bits[1] = a.bits[2] = 100;
  a.bits[3] = 0;
  b.bits[0] = b.bits[1] = b.bits[2] = 200;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);

  // Тест 10: Два отрицательных числа с одинаковыми знаками, но разной мантиссой
  a.bits[0] = a.bits[1] = a.bits[2] = 200;
  a.bits[3] = 0x80000000;
  b.bits[0] = b.bits[1] = b.bits[2] = 100;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

Suite *suite_less(void) {
  Suite *s = suite_create("suite_less");
  TCase *tc = tcase_create("less_tc");
  tcase_add_test(tc, test_s21_is_less);
  tcase_add_test(tc, test_s21_is_less_or_equal);

  suite_add_tcase(s, tc);
  return s;
}