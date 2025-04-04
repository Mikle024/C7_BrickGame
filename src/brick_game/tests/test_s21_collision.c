#include "s21_tests.h"

int collisionWithContext(GameContext_t *context);

START_TEST(test_collision_no_overlap) {
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

  context->currentFigure[1][1] = 1;
  context->currentFigure[2][1] = 1;
  context->currentFigure[3][1] = 1;
  context->currentFigure[3][2] = 1;

  context->figureX = 3;
  context->figureY = 3;

  ck_assert_int_eq(collision(), 0);

  cleanupTest();
}
END_TEST

START_TEST(test_collision_with_border) {
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

  context->currentFigure[1][1] = 1;
  context->currentFigure[2][1] = 1;
  context->currentFigure[3][1] = 1;
  context->currentFigure[3][2] = 1;

  context->figureX = -2;
  context->figureY = 3;
  ck_assert_int_eq(collision(), 1);

  context->figureX = FIELD_WIDTH - 1;
  context->figureY = 3;
  ck_assert_int_eq(collision(), 1);

  context->figureX = 3;
  context->figureY = FIELD_HEIGHT - 3;
  ck_assert_int_eq(collision(), 1);

  cleanupTest();
}
END_TEST

START_TEST(test_collision_with_blocks) {
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

  context->currentFigure[1][1] = 1;
  context->currentFigure[2][1] = 1;
  context->currentFigure[3][1] = 1;
  context->currentFigure[3][2] = 1;

  context->figureX = 3;
  context->figureY = 3;

  context->gameStateInfo.field[0][0] = 2;
  ck_assert_int_eq(collision(), 0);

  context->figureY = 3;
  context->gameStateInfo.field[7][4] = 2;

  context->figureY = 6;
  ck_assert_int_eq(collision(), 1);

  cleanupTest();
}
END_TEST

START_TEST(test_collision_with_null_field) {
  GameContext_t context;
  memset(&context, 0, sizeof(GameContext_t));

  context.currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context.currentFigure[0][0] = 1;

  context.gameStateInfo.field = NULL;

  int result = collisionWithContext(&context);

  freeMatrix(context.currentFigure, FIGURE_SIZE);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_collision_with_null_figure) {
  GameContext_t context;
  memset(&context, 0, sizeof(GameContext_t));

  context.gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);

  context.currentFigure = NULL;

  int result = collisionWithContext(&context);

  freeMatrix(context.gameStateInfo.field, FIELD_HEIGHT);

  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_collision_with_negative_y) {
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

  context->currentFigure[1][1] = 1;
  context->currentFigure[2][1] = 1;
  context->currentFigure[3][1] = 1;
  context->currentFigure[3][2] = 1;

  context->figureX = 3;
  context->figureY = -1;
  ck_assert_int_eq(collision(), 0);

  context->gameStateInfo.field[0][4] = 2;
  ck_assert_int_eq(collision(), 1);

  cleanupTest();
}
END_TEST

Suite *suiteCollision(void) {
  Suite *s = suite_create("suite_collision");
  TCase *tc = tcase_create("tc_collision");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_collision_no_overlap);
  tcase_add_test(tc, test_collision_with_border);
  tcase_add_test(tc, test_collision_with_blocks);
  tcase_add_test(tc, test_collision_with_null_field);
  tcase_add_test(tc, test_collision_with_null_figure);
  tcase_add_test(tc, test_collision_with_negative_y);

  suite_add_tcase(s, tc);
  return s;
}