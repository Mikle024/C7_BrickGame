#include "s21_tests.h"

START_TEST(test_state_utils_initialization) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  ck_assert_ptr_nonnull(context->gameStateInfo.field);
  ck_assert_ptr_nonnull(context->currentFigure);
  ck_assert_ptr_nonnull(context->gameStateInfo.next);

  ck_assert_int_eq(context->currentState, GameState_Start);
  ck_assert_int_eq(context->gameStateInfo.score, 0);
  ck_assert_int_eq(context->gameStateInfo.pause, 1);
  ck_assert_int_eq(context->figureX, START_COORD_F_X);
  ck_assert_int_eq(context->figureY, START_COORD_F_Y);

  cleanupTest();
}
END_TEST

START_TEST(test_state_utils_timer) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->lastTime = getCurrentTime();
  context->gameStateInfo.speed = 1000;

  ck_assert_int_eq(timer(), 0);

  sleep(2);
  ck_assert_int_eq(timer(), 1);

  cleanupTest();
}
END_TEST

START_TEST(test_state_utils_game_over) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  for (int i = 0; i < FIELD_WIDTH; i++) {
    context->gameStateInfo.field[0][i] = 1;
  }

  ck_assert_int_eq(processGameOver(), 1);

  for (int i = 0; i < FIELD_WIDTH; i++) {
    context->gameStateInfo.field[0][i] = 0;
  }

  ck_assert_int_eq(processGameOver(), 0);

  cleanupTest();
}
END_TEST

START_TEST(test_state_utils_attaching) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->currentFigure[0][0] = 1;
  context->figureY = FIELD_HEIGHT - 1;

  ck_assert_int_eq(processAttaching(), 1);

  context->figureY = FIELD_HEIGHT - 2;
  ck_assert_int_eq(processAttaching(), 0);

  cleanupTest();
}
END_TEST

START_TEST(test_state_utils_shift) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  context->currentFigure[0][0] = 1;
  context->figureX = START_COORD_F_X;
  context->figureY = START_COORD_F_Y;

  context->userInput = Left;
  processShift();
  ck_assert_int_eq(context->figureX, START_COORD_F_X - 1);

  context->userInput = Right;
  processShift();
  ck_assert_int_eq(context->figureX, START_COORD_F_X);

  context->userInput = Down;
  processShift();
  ck_assert_int_eq(context->figureY, START_COORD_F_Y + 1);

  cleanupTest();
}
END_TEST

START_TEST(test_rotation_if_figure_square) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = NULL;
  }

  context->currentFigure = createFigure(1);
  context->figureX = START_COORD_F_X;
  context->figureY = START_COORD_F_Y;

  context->userInput = Action;
  processShift();
  ck_assert_int_eq(context->figureX, START_COORD_F_X);

  cleanupTest();
}
END_TEST

START_TEST(test_rotation_if_figure_not_square) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  if (context->currentFigure) {
    freeMatrix(context->currentFigure, FIGURE_SIZE);
    context->currentFigure = NULL;
  }

  context->currentFigure = createFigure(0);
  context->figureX = START_COORD_F_X;
  context->figureY = START_COORD_F_Y;

  context->userInput = Action;
  processShift();
  ck_assert_int_eq(context->figureX, START_COORD_F_X);

  cleanupTest();
}
END_TEST

START_TEST(test_processShift_if_field_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = NULL;

  processShift();
  ck_assert_ptr_null(context->gameStateInfo.field);

  context->gameStateInfo.field = savedField;

  cleanupTest();
}
END_TEST

START_TEST(test_processShift_if_current_figure_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedFigure = context->currentFigure;
  context->currentFigure = NULL;

  processShift();
  ck_assert_ptr_null(context->currentFigure);

  context->currentFigure = savedFigure;

  cleanupTest();
}
END_TEST

START_TEST(test_processShift_if_current_figure_and_field_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedFigure = context->currentFigure;
  int **savedField = context->gameStateInfo.field;

  context->currentFigure = NULL;
  context->gameStateInfo.field = NULL;

  processShift();
  ck_assert_ptr_null(context->currentFigure);
  ck_assert_ptr_null(context->gameStateInfo.field);

  context->currentFigure = savedFigure;
  context->gameStateInfo.field = savedField;

  cleanupTest();
}
END_TEST

START_TEST(test_processGameOver_if_field_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = NULL;

  processGameOver();
  ck_assert_ptr_null(context->gameStateInfo.field);

  context->gameStateInfo.field = savedField;

  cleanupTest();
}
END_TEST

Suite *suiteStateUtils(void) {
  Suite *s = suite_create("suite_state_utils");
  TCase *tc = tcase_create("tc_state_utils");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_state_utils_initialization);
  tcase_add_test(tc, test_state_utils_timer);
  tcase_add_test(tc, test_state_utils_game_over);
  tcase_add_test(tc, test_state_utils_attaching);
  tcase_add_test(tc, test_state_utils_shift);
  tcase_add_test(tc, test_rotation_if_figure_square);
  tcase_add_test(tc, test_rotation_if_figure_not_square);
  tcase_add_test(tc, test_processShift_if_field_NULL);
  tcase_add_test(tc, test_processShift_if_current_figure_NULL);
  tcase_add_test(tc, test_processShift_if_current_figure_and_field_NULL);
  tcase_add_test(tc, test_processGameOver_if_field_NULL);

  suite_add_tcase(s, tc);
  return s;
}