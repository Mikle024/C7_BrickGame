#include "../s21_tests.h"

START_TEST(test_positive_init_game) {
  bool initGameActual = true;
  bool initGameExpected = false;

  GameContext_t actualGame;
  GameContext_t expectedGame;

  expectedGame.currentState = GameState_Start;
  expectedGame.figureX = FIELD_WIDTH / 2;
  expectedGame.figureY = 0;
  expectedGame.ticksSinceLastMove = 0;
  expectedGame.gameStateInfo.score = 0;
  expectedGame.gameStateInfo.high_score = 0;
  expectedGame.gameStateInfo.level = 1;
  expectedGame.gameStateInfo.speed = 1;
  expectedGame.gameStateInfo.pause = 0;
  expectedGame.gameStateInfo.field = createField(FIELD_WIDTH, FIELD_HEIGHT);
  expectedGame.gameStateInfo.next = createFigure(expectedGame.gameStateInfo);
  expectedGame.figuresType = createFiguresType();
  expectedGame.currentFigure = createFigure(expectedGame.gameStateInfo);

  initializeGame(&actualGame, &initGameActual);

  ck_assert_int_eq(initGameActual, initGameExpected);
  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
  ck_assert_int_eq(actualGame.figureX, expectedGame.figureX);
  ck_assert_int_eq(actualGame.figureY, expectedGame.figureY);
  ck_assert_int_eq(actualGame.ticksSinceLastMove,
                   expectedGame.ticksSinceLastMove);
  ck_assert_int_eq(actualGame.gameStateInfo.score,
                   expectedGame.gameStateInfo.score);
  ck_assert_int_eq(actualGame.gameStateInfo.high_score,
                   expectedGame.gameStateInfo.high_score);
  ck_assert_int_eq(actualGame.gameStateInfo.level,
                   expectedGame.gameStateInfo.level);
  ck_assert_int_eq(actualGame.gameStateInfo.speed,
                   expectedGame.gameStateInfo.speed);
  ck_assert_int_eq(actualGame.gameStateInfo.pause,
                   expectedGame.gameStateInfo.pause);

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(actualGame.gameStateInfo.field[i][j],
                       expectedGame.gameStateInfo.field[i][j]);
    }
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      ck_assert_int_eq(actualGame.gameStateInfo.next[i][j],
                       expectedGame.gameStateInfo.next[i][j]);
    }
  }

  for (int i = 0; i < FIGURE_COUNT; i++) {
    for (int j = 0; j < FIGURE_SIZE * FIGURE_SIZE; j++) {
      ck_assert_int_eq(actualGame.figuresType[i][j],
                       expectedGame.figuresType[i][j]);
    }
  }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      ck_assert_int_eq(actualGame.currentFigure[i][j],
                       expectedGame.currentFigure[i][j]);
    }
  }
}
END_TEST

Suite *suiteInitializeGame(void) {
  Suite *suite = suite_create("suite_initializeGame");
  TCase *tc = tcase_create("tc_initializeGame");

  tcase_add_test(tc, test_positive_init_game);

  suite_add_tcase(suite, tc);
  return suite;
}