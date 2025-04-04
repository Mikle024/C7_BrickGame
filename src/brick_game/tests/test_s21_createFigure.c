#include "s21_tests.h"

START_TEST(test_createFigure_all_types) {
  for (int figureType = 0; figureType < FIGURE_COUNT; figureType++) {
    int **figure = createFigure(figureType);

    ck_assert_ptr_nonnull(figure);

    bool foundNonZero = false;
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (figure[i][j] == (figureType + 1)) {
          foundNonZero = true;
          break;
        }
      }
      if (foundNonZero) break;
    }

    ck_assert_int_eq(foundNonZero, true);

    freeMatrix(figure, FIGURE_SIZE);
  }
}
END_TEST

START_TEST(test_createFigure_invalid_index) {
  int **figure = createFigure(FIGURE_COUNT + 5);

  ck_assert_ptr_nonnull(figure);

  freeMatrix(figure, FIGURE_SIZE);

  figure = createFigure(-1);

  ck_assert_ptr_nonnull(figure);

  freeMatrix(figure, FIGURE_SIZE);
}
END_TEST

START_TEST(test_createFigure_dimensions) {
  int **figure = createFigure(0);

  ck_assert_ptr_nonnull(figure);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_ptr_nonnull(figure[i]);
  }

  freeMatrix(figure, FIGURE_SIZE);
}
END_TEST

Suite *suiteCreateFigure(void) {
  Suite *s = suite_create("suite_createFigure");
  TCase *tc = tcase_create("tc_createFigure");

  tcase_add_test(tc, test_createFigure_all_types);
  tcase_add_test(tc, test_createFigure_invalid_index);
  tcase_add_test(tc, test_createFigure_dimensions);

  suite_add_tcase(s, tc);
  return s;
}