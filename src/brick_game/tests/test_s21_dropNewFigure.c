#include "s21_tests.h"

START_TEST(test_dropNewFigure_basic) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = 0;
    }
  }

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = NULL;
  }
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  ck_assert_ptr_nonnull(context->currentFigure);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      context->currentFigure[i][j] = 0;
    }
  }
  context->currentFigure[1][1] = 1;
  context->currentFigure[1][2] = 1;
  context->currentFigure[2][1] = 1;
  context->currentFigure[2][2] = 1;

  int x = 3;
  int y = 2;

  dropNewFigure(x, y);

  ck_assert_int_eq(context->figureX, x);
  ck_assert_int_eq(context->figureY, y);

  addCurrentFigureToField();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = x + j;
        int fieldY = y + i;

        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          ck_assert_int_eq(context->gameStateInfo.field[fieldY][fieldX],
                           context->currentFigure[i][j]);
        }
      }
    }
  }

  cleanupTest();
}
END_TEST

START_TEST(test_dropNewFigure_out_of_bounds) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = 0;
    }
  }

  freeMatrix(context->currentFigure, FIGURE_SIZE);
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  ck_assert_ptr_nonnull(context->currentFigure);

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      context->currentFigure[i][j] = 0;
    }
  }
  context->currentFigure[0][0] = 1;

  dropNewFigure(-1, -1);

  int counts_1s = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (context->gameStateInfo.field[i][j] == 1) {
        counts_1s++;
      }
    }
  }

  ck_assert_int_eq(counts_1s, 0);

  cleanupTest();
}
END_TEST

Suite *suiteDropNewFigure(void) {
  Suite *s = suite_create("suite_dropNewFigure");
  TCase *tc = tcase_create("tc_drop_new_figure");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_dropNewFigure_basic);
  tcase_add_test(tc, test_dropNewFigure_out_of_bounds);

  suite_add_tcase(s, tc);
  return s;
}