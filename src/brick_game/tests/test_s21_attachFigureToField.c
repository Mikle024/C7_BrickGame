#include "s21_tests.h"

START_TEST(test_attachFigureToField_positive) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  ck_assert_ptr_nonnull(context->gameStateInfo.field);
  ck_assert_ptr_nonnull(context->currentFigure);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = 0;
    }
  }

  freeMatrix(context->currentFigure, FIGURE_SIZE);
  context->currentFigure = createFigure(2);
  ck_assert_ptr_nonnull(context->currentFigure);

  context->figureX = 3;
  context->figureY = 5;

  attachFigureToField();

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = context->figureX + j;
        int fieldY = context->figureY + i;

        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          ck_assert_int_eq(context->gameStateInfo.field[fieldY][fieldX], 8);
        }
      }
    }
  }

  cleanupTest();
}
END_TEST

START_TEST(test_attachFigureToField_edge_cases) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  ck_assert_ptr_nonnull(context->gameStateInfo.field);
  ck_assert_ptr_nonnull(context->currentFigure);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = 0;
    }
  }

  freeMatrix(context->currentFigure, FIGURE_SIZE);
  context->currentFigure = createFigure(2);
  ck_assert_ptr_nonnull(context->currentFigure);

  context->figureX = 0;
  context->figureY = 0;
  attachFigureToField();

  context->figureX = FIELD_WIDTH - FIGURE_SIZE;
  context->figureY = FIELD_HEIGHT - FIGURE_SIZE;
  attachFigureToField();

  cleanupTest();
}
END_TEST

START_TEST(test_attachFigureToField_overlap) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  ck_assert_ptr_nonnull(context->gameStateInfo.field);
  ck_assert_ptr_nonnull(context->currentFigure);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = 0;
    }
  }

  freeMatrix(context->currentFigure, FIGURE_SIZE);
  context->currentFigure = createFigure(2);
  ck_assert_ptr_nonnull(context->currentFigure);

  context->figureX = 3;
  context->figureY = 5;
  attachFigureToField();

  int **savedField = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      savedField[i][j] = context->gameStateInfo.field[i][j];
    }
  }

  attachFigureToField();

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], savedField[i][j]);
    }
  }

  freeMatrix(savedField, FIELD_HEIGHT);
  cleanupTest();
}
END_TEST

Suite *suiteAttachFigureToField(void) {
  Suite *s = suite_create("suite_attachFigureToField");
  TCase *tc = tcase_create("tc_attachFigureToField");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_attachFigureToField_positive);
  tcase_add_test(tc, test_attachFigureToField_edge_cases);
  tcase_add_test(tc, test_attachFigureToField_overlap);

  suite_add_tcase(s, tc);
  return s;
}