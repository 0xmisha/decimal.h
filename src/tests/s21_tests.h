#ifndef TESTS_H
#define TESTS_H

#include <check.h>

#include "../s21_decimal.h"

#define MINUS 2147483648

Suite* comparsion_suite(void);
Suite* conversion_suite(void);
Suite* add_suite(void);
Suite* sub_suite(void);
Suite* mul_suite(void);
Suite* div_suite(void);
Suite* mod_suite(void);
Suite* negate_suite(void);
Suite* truncate_suite(void);
Suite* round_suite(void);
Suite* floor_suite(void);

#endif
