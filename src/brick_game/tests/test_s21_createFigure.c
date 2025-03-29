#include "s21_tests.h"

// Тестирование создания разных типов фигур
START_TEST(test_createFigure_all_types) {
  // Проверяем создание всех 7 типов фигур
  for (int figureType = 0; figureType < FIGURE_COUNT; figureType++) {
    int **figure = createFigure(figureType);
    
    // Проверяем, что фигура создалась
    ck_assert_ptr_nonnull(figure);
    
    // Проверяем, что в фигуре есть хотя бы один ненулевой элемент
    // (соответствующий её типу figureType + 1)
    bool foundNonZero = false;
    for (int i = 0; i < FIGURE_SIZE; i++) {
      for (int j = 0; j < FIGURE_SIZE; j++) {
        if (figure[i][j] == (figureType + 1)) {
          foundNonZero = true;
          break;
        }
      }
      if (foundNonZero) break;
    }
    
    ck_assert_int_eq(foundNonZero, true);
    
    // Освобождаем память
    freeMatrix(figure, FIGURE_SIZE);
  }
}
END_TEST

// Тестирование обработки некорректного индекса фигуры
START_TEST(test_createFigure_invalid_index) {
  // Проверяем индекс выше максимального
  int **figure = createFigure(FIGURE_COUNT + 5);
  
  // Фигура все равно должна быть создана (с каким-то типом в диапазоне 0-6)
  ck_assert_ptr_nonnull(figure);
  
  // Освобождаем память
  freeMatrix(figure, FIGURE_SIZE);
  
  // Проверяем отрицательный индекс
  figure = createFigure(-1);
  
  // Фигура все равно должна быть создана
  ck_assert_ptr_nonnull(figure);
  
  // Освобождаем память
  freeMatrix(figure, FIGURE_SIZE);
}
END_TEST

// Тестирование проверки размерности фигуры
START_TEST(test_createFigure_dimensions) {
  int **figure = createFigure(0); // I-фигура
  
  // Проверяем, что размеры фигуры соответствуют ожидаемому
  ck_assert_ptr_nonnull(figure);
  
  for (int i = 0; i < FIGURE_SIZE; i++) {
    ck_assert_ptr_nonnull(figure[i]);
  }
  
  // Освобождаем память
  freeMatrix(figure, FIGURE_SIZE);
}
END_TEST

// Набор тестов для функции createFigure
Suite *suiteCreateFigure(void) {
  Suite *s = suite_create("suite_createFigure");
  TCase *tc = tcase_create("tc_createFigure");
  
  tcase_add_test(tc, test_createFigure_all_types);
  tcase_add_test(tc, test_createFigure_invalid_index);
  tcase_add_test(tc, test_createFigure_dimensions);
  
  suite_add_tcase(s, tc);
  return s;
} 