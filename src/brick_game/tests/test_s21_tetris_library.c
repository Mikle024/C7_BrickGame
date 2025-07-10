#include "s21_tests.h"

START_TEST(test_userInput_different_states) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->currentState = GameState_Spawn;

    userInput(Left, false);
    userInput(Right, false);
    userInput(Down, false);
    userInput(Action, false);
    userInput(Pause, false);
  }

  cleanupTest();
}
END_TEST

START_TEST(test_userInput_actions) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->currentState = GameState_Start;
    userInput(Start, true);

    userInput(Start, false);
    ck_assert_int_eq(context->gameStateInfo.pause, 0);

    context->currentState = GameState_Moving;

    userInput(Start, false);

    userInput(Left, false);
    ck_assert_int_eq(context->userInput, Left);
    ck_assert_int_eq(context->shiftRequested, true);

    context->shiftRequested = false;

    userInput(Right, false);
    ck_assert_int_eq(context->userInput, Right);
    ck_assert_int_eq(context->shiftRequested, true);

    context->shiftRequested = false;

    userInput(Down, false);
    ck_assert_int_eq(context->userInput, Down);
    ck_assert_int_eq(context->shiftRequested, true);

    context->shiftRequested = false;

    userInput(Action, false);
    ck_assert_int_eq(context->userInput, Action);
    ck_assert_int_eq(context->shiftRequested, true);

    userInput(Action, true);

    context->gameStateInfo.pause = 0;
    userInput(Pause, false);
    ck_assert_int_eq(context->gameStateInfo.pause, 1);

    userInput(Pause, false);
    ck_assert_int_eq(context->gameStateInfo.pause, 0);

    userInput(Pause, true);

    userInput(Up, false);
  }

  cleanupTest();
}
END_TEST

START_TEST(test_userInput_terminate) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  int **currentFigure = context->currentFigure;
  int **field = context->gameStateInfo.field;
  int **next = context->gameStateInfo.next;

  ck_assert_ptr_nonnull(currentFigure);
  ck_assert_ptr_nonnull(field);
  ck_assert_ptr_nonnull(next);

  userInput(Terminate, false);

  ck_assert_ptr_null(context->currentFigure);
  ck_assert_ptr_null(context->gameStateInfo.field);
  ck_assert_ptr_null(context->gameStateInfo.next);

  ck_assert_int_eq(context->figureX, 0);
  ck_assert_int_eq(context->figureY, 0);
  ck_assert_int_eq(context->oldFigureX, 0);
  ck_assert_int_eq(context->oldFigureY, 0);
  ck_assert_int_eq(context->lastTime, 0);
  ck_assert_int_eq(context->currentState, GameState_Start);

  ck_assert_int_eq(context->gameStateInfo.score, 0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 0);
  ck_assert_int_eq(context->gameStateInfo.level, 0);
  ck_assert_int_eq(context->gameStateInfo.speed, 0);
  ck_assert_int_eq(context->gameStateInfo.pause, 0);

  userInput(Terminate, true);
}
END_TEST

START_TEST(test_updateCurrentState) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    ck_assert_int_eq(context->currentState, GameState_Start);

    userInput(Start, false);
    GameInfo_t info = updateCurrentState();
    ck_assert_int_eq(context->currentState, GameState_Spawn);
    ck_assert_ptr_nonnull(info.field);
    ck_assert_ptr_nonnull(info.next);

    info = updateCurrentState();
    ck_assert_int_eq(context->currentState, GameState_Moving);

    ck_assert_ptr_nonnull(info.field);
    ck_assert_ptr_nonnull(info.next);

    context->shiftRequested = true;
    context->userInput = Left;
    updateCurrentState();

    ck_assert_int_eq(context->currentState, GameState_Shifting);
  }

  cleanupTest();
}
END_TEST

START_TEST(test_game_over_state) {
  setupTest();

  GameContext_t *context = getCurrentContext();
  if (context) {
    context->currentState = GameState_GameOver;

    GameInfo_t info = updateCurrentState();

    ck_assert(info.field == NULL || info.next == NULL);
  }

  cleanupTest();
}
END_TEST

Suite *suiteTetrisLibrary(void) {
  Suite *suite = suite_create("suite_tetris_library");
  TCase *tc = tcase_create("tc_tetris_library");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_userInput_different_states);
  tcase_add_test(tc, test_userInput_actions);
  tcase_add_test(tc, test_userInput_terminate);
  tcase_add_test(tc, test_updateCurrentState);
  tcase_add_test(tc, test_game_over_state);

  suite_add_tcase(suite, tc);
  return suite;
}