#include "s21_tests.h"

START_TEST(test_addCurrentFigureToField_positive) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {3, 3, 3, 0}, {0, 3, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, 4, 6);

  addCurrentFigureToField();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0 && context->figureY + i >= 0 &&
          context->figureY + i < FIELD_HEIGHT && context->figureX + j >= 0 &&
          context->figureX + j < FIELD_WIDTH) {
        ck_assert_int_eq(context->gameStateInfo
                             .field[context->figureY + i][context->figureX + j],
                         context->currentFigure[i][j]);
      }
    }
  }

  cleanupTest();
}
END_TEST

Suite *suiteAddCurrentFigureToField(void) {
  Suite *s = suite_create("suite_addCurrentFigureToField");
  TCase *tc_core = tcase_create("tc_addCurrentFigureToField");

  tcase_add_checked_fixture(tc_core, setupTest, cleanupTest);
  tcase_add_test(tc_core, test_addCurrentFigureToField_positive);

  suite_add_tcase(s, tc_core);
  return s;
}