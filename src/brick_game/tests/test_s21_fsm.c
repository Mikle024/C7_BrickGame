#include "s21_tests.h"

START_TEST(no_valid_state) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->currentState = 6;
    transitionToState();
    ck_assert_int_eq(context->currentState, 6);
  }

  cleanupTest();
}
END_TEST

START_TEST(transition_from_start_state_without_timer) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->gameStateInfo.pause = 0;
    context->currentState = GameState_Start;
    transitionToState();
    ck_assert_int_eq(context->currentState, GameState_Spawn);
  }

  cleanupTest();
}
END_TEST

START_TEST(transition_from_timed_start_state) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->gameStateInfo.pause = 0;
    context->currentState = GameState_Start;
    transitionToState();
    sleep(2);
    transitionToState();
    ck_assert_int_eq(context->currentState, GameState_Moving);
  }

  cleanupTest();
}
END_TEST

START_TEST(full_game_without_user_input) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    if (context->gameStateInfo.field) {
      for (int i = FIELD_HEIGHT - 1; i > 1; i--) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
          context->gameStateInfo.field[i][j] = 8;
        }
      }
    }

    context->currentState = GameState_Start;
    context->gameStateInfo.pause = 0;

    while (context->currentState != GameState_GameOver) {
      context->lastTime = 0;

      if (context->currentState == GameState_Spawn) {
        context->figureY = 0;
      }

      transitionToState();
    }

    ck_assert_int_eq(context->currentState, GameState_GameOver);
  }

  cleanupTest();
}
END_TEST

START_TEST(test_stateOfShifting_if_field_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = NULL;

  stateOfShifting();
  ck_assert_ptr_null(context->gameStateInfo.field);

  context->gameStateInfo.field = savedField;

  cleanupTest();
}
END_TEST

START_TEST(test_stateOfShifting_if_current_figure_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedFigure = context->currentFigure;
  context->currentFigure = NULL;

  stateOfShifting();
  ck_assert_ptr_null(context->currentFigure);

  context->currentFigure = savedFigure;

  cleanupTest();
}
END_TEST

START_TEST(test_stateOfShifting_if_current_figure_and_field_NULL) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **savedFigure = context->currentFigure;
  int **savedField = context->gameStateInfo.field;

  context->currentFigure = NULL;
  context->gameStateInfo.field = NULL;

  stateOfShifting();
  ck_assert_ptr_null(context->currentFigure);
  ck_assert_ptr_null(context->gameStateInfo.field);

  context->currentFigure = savedFigure;
  context->gameStateInfo.field = savedField;

  cleanupTest();
}
END_TEST

Suite *suiteFsm(void) {
  Suite *suite = suite_create("suite_fsm");
  TCase *tc = tcase_create("tc_fsm");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, no_valid_state);
  tcase_add_test(tc, transition_from_start_state_without_timer);
  tcase_add_test(tc, transition_from_timed_start_state);
  tcase_add_test(tc, full_game_without_user_input);
  tcase_add_test(tc, test_stateOfShifting_if_field_NULL);
  tcase_add_test(tc, test_stateOfShifting_if_current_figure_NULL);
  tcase_add_test(tc, test_stateOfShifting_if_current_figure_and_field_NULL);

  suite_add_tcase(suite, tc);
  return suite;
}