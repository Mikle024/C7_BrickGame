#include "s21_tests.h"

// Тест для случая, когда фигура является квадратом (содержит элемент со значением 2)
START_TEST(test_isSquareFigure_true) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем тестовую фигуру 4x4 (пусть это будет квадрат с 2)
  context->currentFigure = calloc(FIGURE_SIZE, sizeof(int *));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    context->currentFigure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }

  // Задаем фигуру O-образного типа (квадрат)
  context->currentFigure[1][1] = 2;
  context->currentFigure[1][2] = 2;
  context->currentFigure[2][1] = 2;
  context->currentFigure[2][2] = 2;

  // Проверяем, что функция isSquareFigure() возвращает true
  ck_assert_int_eq(isSquareFigure(), true);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

// Тест для случая, когда фигура не является квадратом (не содержит элемент со значением 2)
START_TEST(test_isSquareFigure_false) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем тестовую фигуру 4x4 без 2
  context->currentFigure = calloc(FIGURE_SIZE, sizeof(int *));
  for (int i = 0; i < FIGURE_SIZE; i++) {
    context->currentFigure[i] = calloc(FIGURE_SIZE, sizeof(int));
  }

  // Заполняем случайными значениями, но без 2
  context->currentFigure[1][1] = 1;
  context->currentFigure[1][2] = 3;
  context->currentFigure[2][1] = 3;
  context->currentFigure[2][2] = 1;

  // Проверяем, что isSquareFigure() возвращает false
  ck_assert_int_eq(isSquareFigure(), false);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

// Тест для случая, когда фигура не инициализирована (NULL)
START_TEST(test_isSquareFigure_null) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Сохраняем текущую фигуру
  int **savedFigure = context->currentFigure;
  
  // Устанавливаем NULL для текущей фигуры
  context->currentFigure = NULL;
  
  // Проверяем, что функция корректно обрабатывает NULL
  ck_assert_int_eq(isSquareFigure(), false);
  
  // Восстанавливаем исходную фигуру
  context->currentFigure = savedFigure;
}
END_TEST

// Набор тестов для функции isSquareFigure
Suite *suiteIsSquareFigure(void) {
  Suite *s = suite_create("suite_isSquareFigure");
  TCase *tc_core = tcase_create("tc_isSquareFigure");

  tcase_add_test(tc_core, test_isSquareFigure_true);
  tcase_add_test(tc_core, test_isSquareFigure_false);
  tcase_add_test(tc_core, test_isSquareFigure_null);

  suite_add_tcase(s, tc_core);
  return s;
}