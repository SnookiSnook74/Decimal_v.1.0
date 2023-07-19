
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef struct 
{
    uint32_t bits[4];
} s21_decimal;

#define s21_MAXDEC 7.9228162514264337593543950335e28


/*функция сложения*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*функция вычитания*/
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*функция умножения*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*функция деления*/
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* округляет десятичное значение до ближайшего целого*/
int s21_round(s21_decimal value, s21_decimal *result);

/*отбрасывает дробную часть без округления*/
int s21_truncate(s21_decimal value, s21_decimal *result);

/*округление в сторону отрицательной бесконечности*/
int s21_floor(s21_decimal value, s21_decimal *result);

/*Возвращает результат умножения указанного Decimal на -1.*/
int s21_negate(s21_decimal value, s21_decimal *result);

/*Равенство децималов*/
int s21_is_equal(s21_decimal a, s21_decimal b);

/*Неравенство децималов*/
int s21_is_not_equal(s21_decimal a, s21_decimal b);

/*Больше*/
int s21_is_greater(s21_decimal a, s21_decimal b);

/*Больше или равно*/
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);

/*Меньше*/
int s21_is_less(s21_decimal a, s21_decimal b);

/*Меньше или равно*/
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);

/*преобразователь из float*/
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/*Из int*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);

/*В int*/
int s21_from_decimal_to_int(s21_decimal src, int *dst);

/*В float*/
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*возвращает децимал инициализированный нулем*/
s21_decimal _init_decimal();

/*возвращает состояние бита на указанной позиции 1 или 0*/
int _find_bit(s21_decimal decimal, int elem);

/*устанавливает 1 в указанную позицию*/
void _set_bit(s21_decimal *decimal, int elem);

/*проверка децимала на корректность*/
bool _is_decimal_correct(s21_decimal decimal);

/*проверяет равен ли децимал нулю*/
bool _is_zero(s21_decimal value);

/*выравнивает экспоненты двух децималов*/
void _set_common_exponent(s21_decimal *value_1, s21_decimal *value_2);

/*Уменьшает экспоненту*/
void _decrease_exponent(s21_decimal *value_1, s21_decimal *value_2, int diff,
                        int *v1_exponent, int *v2_exponent);

/*умножает децимал на целое число*/
int _muliply_uint(s21_decimal *value, uint32_t num);

/*делит мантиссу decimal на любой int, при делении на 0 возвращает 3*/
int _divide_uint(s21_decimal *value, uint32_t num, int round_type);

/*функция округления */
void _parse_rounding(s21_decimal *result, uint64_t buffer, uint32_t num,
                     int round_type);

/*подсчет количества цифр в числе*/
int count_digits(int n);

/*сдвиг децимала влево*/
int _left_shift(s21_decimal *value);

/*побитовое сложение*/
int _binary_addition(int bit1, int bit2, int *remainder);

/*побитовое "не"*/
void _binary_not(s21_decimal * value);

/*устанавливает экспаненту*/
void _set_scale(s21_decimal * value, int scale);

/*устанавливает знак*/
void _set_sign(s21_decimal * value, int sign);

void s21_set_bit(s21_decimal *dst, int index, int bit);

int s21_from_decimal_to_double(s21_decimal src, long double *dst);

int s21_get_scale(s21_decimal dst);