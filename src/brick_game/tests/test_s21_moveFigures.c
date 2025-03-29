#include "s21_tests.h"

// Тест движения фигуры влево
START_TEST(test_moveFigureLeft) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное положение
  int originalX = context->figureX;
  
  // Вызываем функцию и проверяем, что координата X уменьшилась
  moveFigureLeft();
  ck_assert_int_eq(context->figureX, originalX - 1);
  
  // Восстанавливаем исходное положение
  context->figureX = originalX;
}
END_TEST

// Тест движения фигуры вправо
START_TEST(test_moveFigureRight) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное положение
  int originalX = context->figureX;
  
  // Вызываем функцию и проверяем, что координата X увеличилась
  moveFigureRight();
  ck_assert_int_eq(context->figureX, originalX + 1);
  
  // Восстанавливаем исходное положение
  context->figureX = originalX;
}
END_TEST

// Тест движения фигуры вниз
START_TEST(test_moveFigureDown) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное положение
  int originalY = context->figureY;
  
  // Устанавливаем положение, где нет коллизии
  context->figureY = 5;
  
  // Создаем пустое поле для предотвращения коллизий
  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Вызываем функцию и проверяем, что координата Y увеличилась (фигура опустилась)
  bool result = moveFigureDown();
  ck_assert_int_eq(context->figureY, 6);
  ck_assert_int_eq(result, false);  // Коллизии нет, результат должен быть false
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = savedField;
  context->figureY = originalY;
}
END_TEST

// Тест движения фигуры вверх
START_TEST(test_moveFigureUp) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное положение
  int originalY = context->figureY;
  
  // Устанавливаем положение, где нет коллизии
  context->figureY = 5;
  
  // Создаем пустое поле для предотвращения коллизий
  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Вызываем функцию и проверяем, что координата Y уменьшилась (фигура поднялась)
  moveFigureUp();
  ck_assert_int_eq(context->figureY, 4);
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = savedField;
  context->figureY = originalY;
}
END_TEST

// Тест коллизии при движении влево
START_TEST(test_moveFigureLeft_collision) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем тестовую фигуру и поле
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[0][0] = 1;  // Левый верхний угол фигуры занят
  
  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру у левого края
  int savedX = context->figureX;
  context->figureX = 0;
  
  // Движение должно быть невозможно из-за края поля
  moveFigureLeft();
  ck_assert_int_eq(context->figureX, 0);  // Координата не должна измениться
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = savedField;
  context->figureX = savedX;
}
END_TEST

// Тест коллизии при движении вправо
START_TEST(test_moveFigureRight_collision) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем тестовую фигуру и поле
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[0][FIGURE_SIZE-1] = 1;  // Правый верхний угол фигуры занят
  
  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру у правого края
  int savedX = context->figureX;
  context->figureX = FIELD_WIDTH - FIGURE_SIZE;
  
  // Движение должно быть невозможно из-за края поля
  moveFigureRight();
  ck_assert_int_eq(context->figureX, FIELD_WIDTH - FIGURE_SIZE);  // Координата не должна измениться
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = savedField;
  context->figureX = savedX;
}
END_TEST

// Тест коллизии при движении вниз
START_TEST(test_moveFigureDown_collision) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем тестовую фигуру и поле
  context->currentFigure = createMatrix(FIGURE_SIZE, FIGURE_SIZE);
  context->currentFigure[FIGURE_SIZE-1][0] = 1;  // Левый нижний угол фигуры занят
  
  int **savedField = context->gameStateInfo.field;
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Устанавливаем фигуру у нижнего края
  int savedY = context->figureY;
  context->figureY = FIELD_HEIGHT - FIGURE_SIZE;
  
  // Движение должно быть невозможно из-за края поля
  bool result = moveFigureDown();
  ck_assert_int_eq(context->figureY, FIELD_HEIGHT - FIGURE_SIZE);  // Координата не должна измениться
  ck_assert_int_eq(result, true);  // Результат должен быть true (есть коллизия)
  
  // Восстанавливаем исходное состояние
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = savedField;
  context->figureY = savedY;
}
END_TEST

// Набор тестов для функции moveFigureLeft
Suite *suiteMoveFigureLeft(void) {
  Suite *s = suite_create("suite_moveFigureLeft");
  TCase *tc = tcase_create("tc_moveFigureLeft");
  
  tcase_add_test(tc, test_moveFigureLeft);
  tcase_add_test(tc, test_moveFigureLeft_collision);
  
  suite_add_tcase(s, tc);
  return s;
}

// Набор тестов для функции moveFigureRight
Suite *suiteMoveFigureRight(void) {
  Suite *s = suite_create("suite_moveFigureRight");
  TCase *tc = tcase_create("tc_moveFigureRight");
  
  tcase_add_test(tc, test_moveFigureRight);
  tcase_add_test(tc, test_moveFigureRight_collision);
  
  suite_add_tcase(s, tc);
  return s;
}

// Набор тестов для функции moveFigureDown
Suite *suiteMoveFigureDown(void) {
  Suite *s = suite_create("suite_moveFigureDown");
  TCase *tc = tcase_create("tc_moveFigureDown");
  
  tcase_add_test(tc, test_moveFigureDown);
  tcase_add_test(tc, test_moveFigureDown_collision);
  
  suite_add_tcase(s, tc);
  return s;
}

// Набор тестов для функции moveFigureUp
Suite *suiteMoveFigureUp(void) {
  Suite *s = suite_create("suite_moveFigureUp");
  TCase *tc = tcase_create("tc_moveFigureUp");
  
  tcase_add_test(tc, test_moveFigureUp);
  
  suite_add_tcase(s, tc);
  return s;
} 