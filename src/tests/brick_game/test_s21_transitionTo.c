#include "../s21_tests.h"

// 1. START -> SPAWN
START_TEST(test_positive_from_Start_to_Spawn) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Start;
  expectedGame.currentState = GameState_Spawn;

  transitionTo(&actualGame, GameState_Spawn);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

// 2. SPAWN -> MOVING
START_TEST(test_postive_from_Spawn_to_Moving) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Spawn;
  expectedGame.currentState = GameState_Moving;

  transitionTo(&actualGame, GameState_Moving);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

// 3. MOVING -> SHIFTING
START_TEST(test_postive_from_Moving_to_Shifting) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Moving;
  expectedGame.currentState = GameState_Shifting;

  transitionTo(&actualGame, GameState_Shifting);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

// 4. MOVING -> ATTACHING
START_TEST(test_postive_from_Moving_to_Attaching) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Moving;
  expectedGame.currentState = GameState_Attaching;

  transitionTo(&actualGame, GameState_Attaching);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

//// 5. SHIFTING -> MOVING
// START_TEST(test_postive_from_Shifting_to_Moving) {
//   bool initGame = true;
//   GameContext_t actualGame;
//   GameContext_t expectedGame;
//
//   initializeGame(&actualGame, &initGame);
//   initializeGame(&expectedGame, &initGame);
//
//   actualGame.currentState = GameState_Shifting;
//   expectedGame.currentState = GameState_Moving;
//
//   transitionTo(&actualGame, GameState_Moving);
//
//   ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
// }
// END_TEST
//
//// 6. SHIFTING -> ATTACHING
// START_TEST(test_postive_from_Shifting_to_Attaching) {
//   bool initGame = true;
//   GameContext_t actualGame;
//   GameContext_t expectedGame;
//
//   initializeGame(&actualGame, &initGame);
//   initializeGame(&expectedGame, &initGame);
//
//   actualGame.currentState = GameState_Shifting;
//   expectedGame.currentState = GameState_Attaching;
//
//   transitionTo(&actualGame, GameState_Attaching);
//
//   ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
// }
// END_TEST
//
//// 7. ATTACHING -> SPAWN
// START_TEST(test_postive_from_Attaching_to_Spawn) {
//   bool initGame = true;
//   GameContext_t actualGame;
//   GameContext_t expectedGame;
//
//   initializeGame(&actualGame, &initGame);
//   initializeGame(&expectedGame, &initGame);
//
//   actualGame.currentState = GameState_Attaching;
//   expectedGame.currentState = GameState_Spawn;
//
//   transitionTo(&actualGame, GameState_Spawn);
//
//   ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
// }
// END_TEST
//
//// 8. ATTACHING -> GAME_OVER
// START_TEST(test_postive_from_Attaching_to_GameOver) {
//   bool initGame = true;
//   GameContext_t actualGame;
//   GameContext_t expectedGame;
//
//   initializeGame(&actualGame, &initGame);
//   initializeGame(&expectedGame, &initGame);
//
//   actualGame.currentState = GameState_Attaching;
//   expectedGame.currentState = GameState_GameOver;
//
//   transitionTo(&actualGame, GameState_GameOver);
//
//   ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
// }
// END_TEST
//
//// 9. GAME_OVER -> START
// START_TEST(test_postive_from_GameOver_to_Start) {
//   bool initGame = true;
//   GameContext_t actualGame;
//   GameContext_t expectedGame;
//
//   initializeGame(&actualGame, &initGame);
//   initializeGame(&expectedGame, &initGame);
//
//   actualGame.currentState = GameState_GameOver;
//   expectedGame.currentState = GameState_Start;
//
//   transitionTo(&actualGame, GameState_Start);
//
//   ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
// }
// END_TEST

// 10. NEGATIVE START -> MOVING
START_TEST(test_negative_from_Start_to_Moving) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Start;
  expectedGame.currentState = GameState_Start;

  transitionTo(&actualGame, GameState_Moving);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

// 11. NEGATIVE START -> SHIFTING
START_TEST(test_negative_from_Start_to_Shifting) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Start;
  expectedGame.currentState = GameState_Start;

  transitionTo(&actualGame, GameState_Shifting);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST

// 12. NEGATIVE START -> ATTACHING
START_TEST(test_negative_from_Start_to_Attaching) {
  bool initGame = true;
  GameContext_t actualGame;
  GameContext_t expectedGame;

  initializeGame(&actualGame, &initGame);
  initializeGame(&expectedGame, &initGame);

  actualGame.currentState = GameState_Start;
  expectedGame.currentState = GameState_Start;

  transitionTo(&actualGame, GameState_Attaching);

  ck_assert_int_eq(actualGame.currentState, expectedGame.currentState);
}
END_TEST
//
//// 13. NEGATIVE START -> GAME_OVER
// START_TEST(test_negative_from_Start_to_GameOver) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Start;
//   expectedGame->currentState = GameState_Start;
//
//   transitionTo(actualGame, GameState_GameOver);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 14. NEGATIVE SPAWN -> START
// START_TEST(test_negative_from_Spawn_to_Start) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Spawn;
//   expectedGame->currentState = GameState_Spawn;
//
//   transitionTo(actualGame, GameState_Start);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 15. NEGATIVE SPAWN -> SHIFTING
// START_TEST(test_negative_from_Spawn_to_Shifting) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Spawn;
//   expectedGame->currentState = GameState_Spawn;
//
//   transitionTo(actualGame, GameState_Shifting);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 16. NEGATIVE SPAWN -> ATTACHING
// START_TEST(test_negative_from_Spawn_to_Attaching) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Spawn;
//   expectedGame->currentState = GameState_Spawn;
//
//   transitionTo(actualGame, GameState_Attaching);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 17. NEGATIVE SPAWN -> GAME_OVER
// START_TEST(test_negative_from_Spawn_to_GameOver) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Spawn;
//   expectedGame->currentState = GameState_Spawn;
//
//   transitionTo(actualGame, GameState_GameOver);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 18. NEGATIVE MOVING -> START
// START_TEST(test_negative_from_Moving_to_Start) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Moving;
//   expectedGame->currentState = GameState_Moving;
//
//   transitionTo(actualGame, GameState_Start);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 19. NEGATIVE MOVING -> SPAWN
// START_TEST(test_negative_from_Moving_to_Spawn) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Moving;
//   expectedGame->currentState = GameState_Moving;
//
//   transitionTo(actualGame, GameState_Spawn);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 20. NEGATIVE MOVING -> GAME_OVER
// START_TEST(test_negative_from_Moving_to_GameOver) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Moving;
//   expectedGame->currentState = GameState_Moving;
//
//   transitionTo(actualGame, GameState_GameOver);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 21. NEGATIVE SHIFTING -> START
// START_TEST(test_negative_from_Shifting_to_Start) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Shifting;
//   expectedGame->currentState = GameState_Shifting;
//
//   transitionTo(actualGame, GameState_Start);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 22. NEGATIVE SHIFTING -> SPAWN
// START_TEST(test_negative_from_Shifting_to_Spawn) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Shifting;
//   expectedGame->currentState = GameState_Shifting;
//
//   transitionTo(actualGame, GameState_Spawn);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 23. NEGATIVE SHIFTING -> GAME_OVER
// START_TEST(test_negative_from_Shifting_to_GameOver) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Shifting;
//   expectedGame->currentState = GameState_Shifting;
//
//   transitionTo(actualGame, GameState_GameOver);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 24. NEGATIVE ATTACHING -> START
// START_TEST(test_negative_from_Attaching_to_Start) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Attaching;
//   expectedGame->currentState = GameState_Attaching;
//
//   transitionTo(actualGame, GameState_Start);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 25. NEGATIVE ATTACHING -> MOVING
// START_TEST(test_negative_from_Attaching_to_Moving) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Attaching;
//   expectedGame->currentState = GameState_Attaching;
//
//   transitionTo(actualGame, GameState_Moving);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 26. NEGATIVE ATTACHING -> SHIFTING
// START_TEST(test_negative_from_Attaching_to_Shifting) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_Attaching;
//   expectedGame->currentState = GameState_Attaching;
//
//   transitionTo(actualGame, GameState_Shifting);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 27. NEGATIVE GAME_OVER -> SPAWN
// START_TEST(test_negative_from_GameOver_to_Spawn) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_GameOver;
//   expectedGame->currentState = GameState_GameOver;
//
//   transitionTo(actualGame, GameState_Spawn);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 28. NEGATIVE GAME_OVER -> MOVING
// START_TEST(test_negative_from_GameOver_to_Moving) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_GameOver;
//   expectedGame->currentState = GameState_GameOver;
//
//   transitionTo(actualGame, GameState_Moving);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 29. NEGATIVE GAME_OVER -> SHIFTING
// START_TEST(test_negative_from_GameOver_to_Shifting) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_GameOver;
//   expectedGame->currentState = GameState_GameOver;
//
//   transitionTo(actualGame, GameState_Shifting);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST
//
//// 30. NEGATIVE GAME_OVER -> ATTACHING
// START_TEST(test_negative_from_GameOver_to_Attaching) {
//   GameContext_t *actualGame = createGame(FIELD_WIDTH, FIELD_HEIGHT,
//   FIGURE_SIZE,
//                                          FIGURE_COUNT, patternFigure);
//   GameContext_t *expectedGame = createGame(
//       FIELD_WIDTH, FIELD_HEIGHT, FIGURE_SIZE, FIGURE_COUNT, patternFigure);
//
//   actualGame->currentState = GameState_GameOver;
//   expectedGame->currentState = GameState_GameOver;
//
//   transitionTo(actualGame, GameState_Attaching);
//
//   ck_assert_int_eq(actualGame->currentState, expectedGame->currentState);
// }
// END_TEST

Suite *suiteTransitionTo(void) {
  Suite *suite = suite_create("suite_transitionTo");
  TCase *tc = tcase_create("tc_transitionTo");

  // POSITIVE TESTS
  // 1. START -> SPAWN
  tcase_add_test(tc, test_positive_from_Start_to_Spawn);
  // 2. SPAWN -> MOVING
  tcase_add_test(tc, test_postive_from_Spawn_to_Moving);
  // 3. MOVING -> SHIFTING
  tcase_add_test(tc, test_postive_from_Moving_to_Shifting);
  // 4. MOVING -> ATTACHING
  tcase_add_test(tc, test_postive_from_Moving_to_Attaching);
  //  // 5. SHIFTING -> MOVING
  //  tcase_add_test(tc, test_postive_from_Shifting_to_Moving);
  //  // 6. SHIFTING -> ATTACHING
  //  tcase_add_test(tc, test_postive_from_Shifting_to_Attaching);
  //  // 7. ATTACHING -> SPAWN
  //  tcase_add_test(tc, test_postive_from_Attaching_to_Spawn);
  //  // 8. ATTACHING -> GAME_OVER
  //  tcase_add_test(tc, test_postive_from_Attaching_to_GameOver);
  //  // 9. GAME_OVER -> START
  //  tcase_add_test(tc, test_postive_from_GameOver_to_Start);
  //
  //  // NEGATIVE TESTS
  //  // 10. NEGATIVE START -> MOVING
  //  tcase_add_test(tc, test_negative_from_Start_to_Moving);
  //  // 11. NEGATIVE START -> SHIFTING
  //  tcase_add_test(tc, test_negative_from_Start_to_Shifting);
  //  // 12. NEGATIVE START -> ATTACHING
  //  tcase_add_test(tc, test_negative_from_Start_to_Attaching);
  // 13. NEGATIVE START -> GAME_OVER
  //   tcase_add_test(tc, test_negative_from_Start_to_GameOver);
  //   // 14. NEGATIVE SPAWN -> START
  //   tcase_add_test(tc, test_negative_from_Spawn_to_Start);
  //   // 15. NEGATIVE SPAWN -> SHIFTING
  //   tcase_add_test(tc, test_negative_from_Spawn_to_Shifting);
  //   // 16. NEGATIVE SPAWN -> ATTACHING
  //   tcase_add_test(tc, test_negative_from_Spawn_to_Attaching);
  //   // 17. NEGATIVE SPAWN -> GAME_OVER
  //   tcase_add_test(tc, test_negative_from_Spawn_to_GameOver);
  //   // 18. NEGATIVE MOVING -> START
  //   tcase_add_test(tc, test_negative_from_Moving_to_Start);
  //   // 19. NEGATIVE MOVING -> SPAWN
  //   tcase_add_test(tc, test_negative_from_Moving_to_Spawn);
  //   // 20. NEGATIVE MOVING -> GAME_OVER
  //   tcase_add_test(tc, test_negative_from_Moving_to_GameOver);
  //   // 21. NEGATIVE SHIFTING -> START
  //   tcase_add_test(tc, test_negative_from_Shifting_to_Start);
  //   // 22. NEGATIVE SHIFTING -> SPAWN
  //   tcase_add_test(tc, test_negative_from_Shifting_to_Spawn);
  //   // 23. NEGATIVE SHIFTING -> GAME_OVER
  //   tcase_add_test(tc, test_negative_from_Shifting_to_GameOver);
  //   // 24. NEGATIVE ATTACHING -> START
  //   tcase_add_test(tc, test_negative_from_Attaching_to_Start);
  //   // 25. NEGATIVE ATTACHING -> MOVING
  //   tcase_add_test(tc, test_negative_from_Attaching_to_Moving);
  //   // 26. NEGATIVE ATTACHING -> SHIFTING
  //   tcase_add_test(tc, test_negative_from_Attaching_to_Shifting);
  //   // 27. NEGATIVE GAME_OVER -> SPAWN
  //   tcase_add_test(tc, test_negative_from_GameOver_to_Spawn);
  //   // 28. NEGATIVE GAME_OVER -> MOVING
  //   tcase_add_test(tc, test_negative_from_GameOver_to_Moving);
  //   // 29. NEGATIVE GAME_OVER -> SHIFTING
  //   tcase_add_test(tc, test_negative_from_GameOver_to_Shifting);
  //   // 30. NEGATIVE GAME_OVER -> ATTACHING
  //   tcase_add_test(tc, test_negative_from_GameOver_to_Attaching);

  suite_add_tcase(suite, tc);
  return suite;
}