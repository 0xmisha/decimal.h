#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "s21_tests.h"

int main() {
  int failed = 0;
  int passed = 0;

  Suite *s21_string_test[] = {
      add_suite(),        div_suite(),        mul_suite(),   sub_suite(),
      comparsion_suite(), conversion_suite(), floor_suite(), negate_suite(),
      round_suite(),      truncate_suite(),   NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    passed += srunner_ntests_run(sr) - srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  printf("========= PASSED: %d =========\n", passed);
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
