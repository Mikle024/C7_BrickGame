#include "s21_tests.h"

int main(void) {
  runTests();
  return 0;
}

void runTestcase(Suite *testcase) {
  static int counterTestcase = 1;
  if (counterTestcase > 1) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counterTestcase, "\n");
  counterTestcase++;
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

void runTests(void) {
  Suite *listCases[] = {suiteGetCurrentContext(),
                        suiteInitRandom(),
                        suiteGetCurrentTime(),
                        suiteTimer(),
                        suiteInitHighScore(),
                        suiteFreeMatrix(),
                        suiteFreeGame(),
                        suiteDropNewFigure(),
                        suiteAddCurrentFigureToField(),
                        suiteClearCurrentFigureFromField(),
                        suiteAttachFigureToField(),
                        suiteIfSquare(),
                        suiteCollision(),
//                        suiteProcessShift(),
                        NULL};
  for (Suite **currentTestcase = listCases; *currentTestcase != NULL;
       currentTestcase++) {
    runTestcase(*currentTestcase);
  }
}