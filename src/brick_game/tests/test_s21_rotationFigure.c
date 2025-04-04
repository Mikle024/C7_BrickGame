#include "s21_tests.h"

START_TEST(test_rotationFigure_I) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern,
                            FIELD_WIDTH / 2 - FIGURE_SIZE / 2,
                            FIELD_HEIGHT / 2 - FIGURE_SIZE / 2);

  rotationFigure();

  bool hasNonZeroInColumn = false;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if (context->currentFigure[i][2] != 0) {
      hasNonZeroInColumn = true;
      break;
    }
  }
  ck_assert_int_eq(hasNonZeroInColumn, true);

  cleanupTest();
}
END_TEST

START_TEST(test_rotationFigure_collision) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, FIELD_WIDTH - FIGURE_SIZE, 0);

  int **figureBefore = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figureBefore[i][j] = context->currentFigure[i][j];
    }
  }

  rotationFigure();

  bool figureUnchanged = true;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figureBefore[i][j] != context->currentFigure[i][j]) {
        figureUnchanged = false;
        break;
      }
    }
    if (!figureUnchanged) break;
  }

  freeMatrix(figureBefore, FIGURE_SIZE);
  cleanupTest();
}
END_TEST

START_TEST(test_rotationFigure_square) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {0, 2, 2, 0}, {0, 2, 2, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern,
                            FIELD_WIDTH / 2 - FIGURE_SIZE / 2,
                            FIELD_HEIGHT / 2 - FIGURE_SIZE / 2);

  int **figureBefore = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figureBefore[i][j] = context->currentFigure[i][j];
    }
  }

  rotationFigure();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figureBefore[i][j] == 2) {
        ck_assert_int_eq(context->currentFigure[i][j], 2);
      }
    }
  }

  freeMatrix(figureBefore, FIGURE_SIZE);
  cleanupTest();
}
END_TEST

START_TEST(test_rotationFigure_collision_with_blocks) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int figurePattern[FIGURE_SIZE][FIGURE_SIZE] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  setupGameWithCustomValues(NULL, figurePattern, FIELD_WIDTH - 2, 0);

  int **figureBefore = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figureBefore[i][j] = context->currentFigure[i][j];
    }
  }

  rotationFigure();

  bool figureUnchanged = true;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figureBefore[i][j] != context->currentFigure[i][j]) {
        figureUnchanged = false;
        break;
      }
    }
    if (!figureUnchanged) break;
  }
  ck_assert_int_eq(figureUnchanged, true);

  freeMatrix(figureBefore, FIGURE_SIZE);
  cleanupTest();
}
END_TEST

Suite *suiteRotationFigure(void) {
  Suite *s = suite_create("suite_rotationFigure");
  TCase *tc = tcase_create("tc_rotationFigure");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_rotationFigure_I);
  tcase_add_test(tc, test_rotationFigure_collision);
  tcase_add_test(tc, test_rotationFigure_square);
  tcase_add_test(tc, test_rotationFigure_collision_with_blocks);

  suite_add_tcase(s, tc);
  return s;
}
