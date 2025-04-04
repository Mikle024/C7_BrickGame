#include "s21_tests.h"

START_TEST(test_transition_to_start) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_Start;
  transitionToState();
  ck_assert_int_eq(actualState, context->currentState);

  cleanupTest();
}
END_TEST

START_TEST(test_transition_to_spawn) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_Spawn;
  transitionToState();
  ck_assert_int_ne(actualState, context->currentState);

  cleanupTest();
}
END_TEST

START_TEST(test_transition_to_moving) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_Moving;
  transitionToState();
  ck_assert_int_ne(actualState, context->currentState);

  cleanupTest();
}
END_TEST

START_TEST(test_transition_to_shifting) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_Shifting;
  transitionToState();
  ck_assert_int_ne(actualState, context->currentState);

  cleanupTest();
}
END_TEST

START_TEST(test_transition_to_attaching) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_Attaching;
  transitionToState();
  ck_assert_int_ne(actualState, context->currentState);

  cleanupTest();
}
END_TEST

START_TEST(test_transition_to_gameover) {
  setupTest();
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  GameState actualState = context->currentState;
  context->currentState = GameState_GameOver;
  transitionToState();
  ck_assert_int_eq(actualState, context->currentState);
  cleanupTest();
}
END_TEST

Suite *suiteTransitionToState(void) {
  Suite *s = suite_create("suite_transitionToState");
  TCase *tc = tcase_create("tc_transitionToState");

  tcase_add_checked_fixture(tc, setupTest, cleanupTest);
  tcase_add_test(tc, test_transition_to_start);
  tcase_add_test(tc, test_transition_to_spawn);
  tcase_add_test(tc, test_transition_to_moving);
  tcase_add_test(tc, test_transition_to_shifting);
  tcase_add_test(tc, test_transition_to_attaching);
  tcase_add_test(tc, test_transition_to_gameover);

  suite_add_tcase(s, tc);
  return s;
}