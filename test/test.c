#include "test.h"

int main() {
  int number_failed;
  Suite *add, *sub, *mul, *div, *equ, *toi, *ftd, *itd, *greater, *less, *dtf,
      *neg, *flr, *rnd, *trc;
  SRunner *sr;
  add = suite_add();
  sub = suite_sub();
  mul = suite_mul();
  div = suite_div();
  equ = suite_is_equal();
  toi = suite_to_int();
  ftd = suite_ftod();
  itd = suite_itd();
  greater = suite_greater();
  less = suite_less();
  dtf = suite_to_float();
  neg = suite_negate();
  flr = suite_floor();
  rnd = suite_round();
  trc = suite_truncate();
  sr = srunner_create(add);
  srunner_add_suite(sr, sub);
  srunner_add_suite(sr, mul);
  srunner_add_suite(sr, div);
  srunner_add_suite(sr, equ);
  srunner_add_suite(sr, toi);
  srunner_add_suite(sr, ftd);
  srunner_add_suite(sr, itd);
  srunner_add_suite(sr, greater);
  srunner_add_suite(sr, less);
  srunner_add_suite(sr, dtf);
  srunner_add_suite(sr, neg);
  srunner_add_suite(sr, flr);
  srunner_add_suite(sr, rnd);
  srunner_add_suite(sr, trc);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}