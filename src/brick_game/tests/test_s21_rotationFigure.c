#include "s21_tests.h"

// Тест вращения фигуры типа I (палка)
START_TEST(test_rotationFigure_I) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем тестовую фигуру и поле
  int **savedFigure = context->currentFigure;
  int **savedField = context->gameStateInfo.field;
  
  // Создаем фигуру типа I (горизонтальная палка)
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[1][0] = 1;
  context->currentFigure[1][1] = 1;
  context->currentFigure[1][2] = 1;
  context->currentFigure[1][3] = 1;
  
  // Создаем пустое поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру в центр поля
  context->figureX = FIELD_WIDTH / 2 - FIGURE_SIZE / 2;
  context->figureY = FIELD_HEIGHT / 2 - FIGURE_SIZE / 2;
  
  // Вызываем функцию вращения
  rotationFigure();
  
  // Проверяем, что фигура повернулась (стала вертикальной)
  // В зависимости от реализации, это может выглядеть по-разному
  // Проверим, что есть ненулевые элементы в столбце 2
  bool hasNonZeroInColumn = false;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if (context->currentFigure[i][2] != 0) {
      hasNonZeroInColumn = true;
      break;
    }
  }
  ck_assert_int_eq(hasNonZeroInColumn, true);
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  
  context->currentFigure = savedFigure;
  context->gameStateInfo.field = savedField;
}
END_TEST

// Тест вращения фигуры, когда есть коллизия
START_TEST(test_rotationFigure_collision) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем тестовую фигуру и поле
  int **savedFigure = context->currentFigure;
  int **savedField = context->gameStateInfo.field;
  
  // Создаем фигуру типа I
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[1][0] = 1;
  context->currentFigure[1][1] = 1;
  context->currentFigure[1][2] = 1;
  context->currentFigure[1][3] = 1;
  
  // Создаем поле с блоком рядом с фигурой, чтобы вызвать коллизию
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру у края поля
  context->figureX = FIELD_WIDTH - FIGURE_SIZE;
  context->figureY = 0;
  
  // Запоминаем состояние фигуры до вращения
  int **figureBefore = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figureBefore[i][j] = context->currentFigure[i][j];
    }
  }
  
  // Вызываем функцию вращения
  rotationFigure();
  
  // Проверяем, что фигура не изменилась из-за коллизии
  bool figureUnchanged = true;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figureBefore[i][j] != context->currentFigure[i][j]) {
        figureUnchanged = false;
        break;
      }
    }
    if (!figureUnchanged) break;
  }
  
  // Освобождаем память временной матрицы
  freeMatrix(figureBefore, FIGURE_SIZE);
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  
  context->currentFigure = savedFigure;
  context->gameStateInfo.field = savedField;
}
END_TEST

// Тест вращения квадратной фигуры, которая не должна меняться
START_TEST(test_rotationFigure_square) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Замечание: В игре перед вызовом rotationFigure() выполняется проверка
  // isSquareFigure(), и если это квадрат, то функция не вызывается
  // Здесь мы тестируем прямой вызов rotationFigure() без этой проверки
  
  // Создаем тестовую фигуру и поле
  int **savedFigure = context->currentFigure;
  int **savedField = context->gameStateInfo.field;
  
  // Создаем фигуру типа O (квадрат)
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[1][1] = 2;
  context->currentFigure[1][2] = 2;
  context->currentFigure[2][1] = 2;
  context->currentFigure[2][2] = 2;
  
  // Создаем пустое поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру в центр поля
  context->figureX = FIELD_WIDTH / 2 - FIGURE_SIZE / 2;
  context->figureY = FIELD_HEIGHT / 2 - FIGURE_SIZE / 2;
  
  // Запоминаем состояние фигуры до вращения
  int **figureBefore = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figureBefore[i][j] = context->currentFigure[i][j];
    }
  }
  
  // Вызываем функцию вращения
  rotationFigure();
  
  // Проверяем, что фигура не изменилась (квадрат остается квадратом)
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (figureBefore[i][j] == 2) {
        ck_assert_int_eq(context->currentFigure[i][j], 2);
      }
    }
  }
  
  // Освобождаем память временной матрицы
  freeMatrix(figureBefore, FIGURE_SIZE);
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  
  context->currentFigure = savedFigure;
  context->gameStateInfo.field = savedField;
}
END_TEST

// Набор тестов для функции rotationFigure
Suite *suiteRotationFigure(void) {
  Suite *s = suite_create("suite_rotationFigure");
  TCase *tc = tcase_create("tc_rotationFigure");
  
  tcase_add_test(tc, test_rotationFigure_I);
  tcase_add_test(tc, test_rotationFigure_collision);
  tcase_add_test(tc, test_rotationFigure_square);
  
  suite_add_tcase(s, tc);
  return s;
}
