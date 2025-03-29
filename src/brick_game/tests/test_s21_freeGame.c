#include "s21_tests.h"

// Тест: freeGame() с валидным контекстом
START_TEST(test_freeGame_valid_context) {
  // Получаем текущий контекст
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Выделяем память
  context->currentFigure = calloc(FIGURE_SIZE, sizeof(int *));
  context->gameStateInfo.field = calloc(FIELD_HEIGHT, sizeof(int *));
  context->gameStateInfo.next = calloc(FIGURE_SIZE, sizeof(int *));

  for (int i = 0; i < FIGURE_SIZE; i++) {
    context->currentFigure[i] = calloc(FIGURE_SIZE, sizeof(int));
    context->gameStateInfo.next[i] = calloc(FIGURE_SIZE, sizeof(int));
  }
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    context->gameStateInfo.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  // Вызываем freeGame()
  freeGame();

  // Проверяем, что указатели обнулены
  ck_assert_ptr_null(context->currentFigure);
  ck_assert_ptr_null(context->gameStateInfo.field);
  ck_assert_ptr_null(context->gameStateInfo.next);

  // Проверяем сброс значений
  ck_assert_int_eq(context->figureX, 0);
  ck_assert_int_eq(context->figureY, 0);
  ck_assert_int_eq(context->oldFigureX, 0);
  ck_assert_int_eq(context->oldFigureY, 0);
  ck_assert_int_eq(context->exit, 0);
  ck_assert_int_eq(context->lastTime, 0);
  ck_assert_int_eq(context->currentState, GameState_Start);

  ck_assert_int_eq(context->gameStateInfo.score, 0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 0);
  ck_assert_int_eq(context->gameStateInfo.level, 0);
  ck_assert_int_eq(context->gameStateInfo.speed, 0);
  ck_assert_int_eq(context->gameStateInfo.pause, 0);
}
END_TEST

Suite *suiteFreeGame(void) {
  Suite *s = suite_create("suite_freeGame");
  TCase *tc_core = tcase_create("tc_freeGame");

  tcase_add_test(tc_core, test_freeGame_valid_context);

  suite_add_tcase(s, tc_core);
  return s;
}