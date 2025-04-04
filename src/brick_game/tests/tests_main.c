#include "s21_tests.h"

static TestStats stats = {0, 0, 0, 0, 0, 0};

int main(void) {
  stats.startTime = clock();

  printf("\n");
  printf("==========================================================\n");
  printf("                BRICK GAME TEST SUITE                     \n");
  printf("==========================================================\n");
  printf("\n");

  runTests();

  cleanupAfterTest();

  stats.endTime = clock();
  double testDurationSec =
      ((double)(stats.endTime - stats.startTime)) / CLOCKS_PER_SEC;

  printf("\n");
  printf("==========================================================\n");
  printf("                   TEST SUMMARY                           \n");
  printf("==========================================================\n");
  printf("Total tests: %d\n", stats.total);
  printf("Passed:      %d (%d%%)\n", stats.passed,
         stats.total > 0 ? (stats.passed * 100 / stats.total) : 0);
  printf("Failed:      %d\n", stats.failed);
  printf("Skipped:     %d\n", stats.skipped);
  printf("Time:        %.2f seconds\n", testDurationSec);
  printf("==========================================================\n");

  return (stats.failed > 0) ? 1 : 0;
}

void runTestcase(Suite *testcase, const char *category) {
  static int counterTestcase = 1;

  if (counterTestcase > 1) putchar('\n');

  printf("TEST %d: ", counterTestcase);
  if (category) {
    printf("[%s] ", category);
  }
  printf("\n");
  printf("----------------------------------------------------------\n");

  counterTestcase++;

  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);

  stats.total += srunner_ntests_run(sr);
  stats.failed += srunner_ntests_failed(sr);
  stats.passed += srunner_ntests_run(sr) - srunner_ntests_failed(sr);

  srunner_free(sr);

  cleanupAfterTest();
}

void runTests(void) {
  struct TestGroup {
    const char *category;
    Suite *suite;
  };

  struct TestGroup testGroups[] = {
      {"Core", suiteCreateMatrix()},
      {"Core", suiteFreeMatrix()},

      {"File", suiteInitHighScore()},
      {"File", suiteUpdateScore()},

      {"State", suiteGetCurrentContext()},
      {"State", suiteInitRandom()},
      {"State", suiteGetCurrentTime()},
      {"State", suiteTimer()},
      {"State", suiteInitializeGame()},
      {"State", suiteFreeGame()},
      {"State", suiteCreateFigure()},
      {"State", suiteDropNewFigure()},

      {"FSM", suiteTransitionToState()},
      {"FSM", suiteStateUtils()},
      {"FSM", suiteFsm()},

      {"Field", suiteAddCurrentFigureToField()},
      {"Field", suiteClearCurrentFigureFromField()},
      {"Field", suiteAttachFigureToField()},
      {"Field", suiteIsSquareFigure()},
      {"Field", suiteCollision()},
      {"Field", suitePixelInField()},

      {"Score", suiteCountScore()},
      {"Score", suiteCountSpeed()},
      {"Score", suiteClearLines()},
      {"Score", suiteFullLine()},
      {"Score", suiteRemoveLine()},

      {"Movement", suiteMoveFigureLeft()},
      {"Movement", suiteMoveFigureRight()},
      {"Movement", suiteMoveFigureDown()},
      {"Movement", suiteMoveFigureUp()},
      {"Movement", suiteRotationFigure()},

      {"Utils", suiteStateUtils()},

      {"Library", suiteTetrisLibrary()},

      {NULL, NULL}};

  for (struct TestGroup *current = testGroups; current->suite != NULL;
       current++) {
    runTestcase(current->suite, current->category);
    cleanupAfterTest();
  }

  cleanupAfterTest();
}