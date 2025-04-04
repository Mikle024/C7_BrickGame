#include "s21_tests.h"

START_TEST(test_pixelInField_inside) {
  ck_assert_int_eq(pixelInField(0, 0), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, 0), true);
  ck_assert_int_eq(pixelInField(0, FIELD_HEIGHT - 1), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, FIELD_HEIGHT - 1), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH / 2, FIELD_HEIGHT / 2), true);
}
END_TEST

START_TEST(test_pixelInField_outside) {
  ck_assert_int_eq(pixelInField(-1, 0), false);
  ck_assert_int_eq(pixelInField(0, -1), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, 0), false);
  ck_assert_int_eq(pixelInField(0, FIELD_HEIGHT), false);

  ck_assert_int_eq(pixelInField(-1, -1), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, FIELD_HEIGHT), false);
  ck_assert_int_eq(pixelInField(-1, FIELD_HEIGHT), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH, -1), false);

  ck_assert_int_eq(pixelInField(FIELD_WIDTH, FIELD_HEIGHT - 1), false);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, FIELD_HEIGHT), false);
}
END_TEST

START_TEST(test_pixelInField_border_cases) {
  ck_assert_int_eq(pixelInField(0, FIELD_HEIGHT / 2), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 1, FIELD_HEIGHT / 2), true);

  ck_assert_int_eq(pixelInField(FIELD_WIDTH / 2, 0), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH / 2, FIELD_HEIGHT - 1), true);

  ck_assert_int_eq(pixelInField(1, 1), true);
  ck_assert_int_eq(pixelInField(FIELD_WIDTH - 2, FIELD_HEIGHT - 2), true);
}
END_TEST

Suite *suitePixelInField(void) {
  Suite *s = suite_create("suite_pixelInField");
  TCase *tc = tcase_create("tc_pixelInField");

  tcase_add_test(tc, test_pixelInField_inside);
  tcase_add_test(tc, test_pixelInField_outside);
  tcase_add_test(tc, test_pixelInField_border_cases);

  suite_add_tcase(s, tc);
  return s;
}