#include "s21_tests.h"

START_TEST(test_clearCurrentFigureFromField_positive) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, 3, 5);
  context->oldFigureX = 3;
  context->oldFigureY = 5;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = context->oldFigureX + j;
        int fieldY = context->oldFigureY + i;

        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          context->gameStateInfo.field[fieldY][fieldX] =
              context->currentFigure[i][j];
        }
      }
    }
  }

  clearCurrentFigureFromField();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      int fieldX = context->oldFigureX + j;
      int fieldY = context->oldFigureY + i;

      if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
          fieldY < FIELD_HEIGHT) {
        ck_assert_int_eq(context->gameStateInfo.field[fieldY][fieldX], 0);
      }
    }
  }

  ck_assert_int_eq(context->oldFigureX, context->figureX);
  ck_assert_int_eq(context->oldFigureY, context->figureY);

  cleanupTest();
}
END_TEST

Suite *suiteClearCurrentFigureFromField(void) {
  Suite *s = suite_create("suite_clearCurrentFigureFromField");
  TCase *tc_core = tcase_create("tc_clearCurrentFigureFromField");

  tcase_add_checked_fixture(tc_core, setupTest, cleanupTest);
  tcase_add_test(tc_core, test_clearCurrentFigureFromField_positive);

  suite_add_tcase(s, tc_core);
  return s;
}