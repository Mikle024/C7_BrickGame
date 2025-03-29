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
  Suite *listCases[] = {
                        // Тесты для утилитных функций
                        suiteCreateMatrix(),
                        suiteFreeMatrix(),
                        
                        // Тесты для файловых операций
                        suiteInitHighScore(),
                        suiteUpdateScore(),
                        
                        // Тесты для core механик
                        suiteGetCurrentContext(),
                        suiteInitRandom(),
                        suiteGetCurrentTime(),
                        suiteTimer(),
                        suiteInitializeGame(),
                        suiteFreeGame(),
                        suiteCreateFigure(),
                        suiteDropNewFigure(),
                        
                        // Тесты для операций с фигурами
                        suiteAddCurrentFigureToField(),
                        suiteClearCurrentFigureFromField(), 
                        suiteAttachFigureToField(),
                        suiteIsSquareFigure(),
                        suiteCollision(),
                        suitePixelInField(),
                        suiteProcessShift(),
                        suiteProcessAttaching(),
                        
                        // Тесты для логики очков и уровней
                        suiteCountScore(),
                        suiteCountSpeed(),
                        suiteClearLines(),
                        suiteFullLine(),
                        suiteRemoveLine(),
                        
                        // Тесты для движения фигур
                        suiteMoveFigureRight(),
                        suiteMoveFigureLeft(),
                        suiteMoveFigureDown(),
                        suiteMoveFigureUp(),
                        suiteRotationFigure(),
                        
                        NULL};
  for (Suite **currentTestcase = listCases; *currentTestcase != NULL;
       currentTestcase++) {
    runTestcase(*currentTestcase);
  }
}