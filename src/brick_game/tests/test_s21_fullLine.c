#include "s21_tests.h"

// Тест для полной линии (все ячейки заполнены)
START_TEST(test_fullLine_true) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем одну линию полностью (все ячейки ненулевые)
  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }
  
  // Проверяем, что функция определяет линию как полную
  ck_assert_int_eq(fullLine(testLine), true);
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест для неполной линии (есть пустые ячейки)
START_TEST(test_fullLine_false) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем линию, оставляя одну ячейку пустой
  int testLine = 5;
  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    context->gameStateInfo.field[testLine][j] = 1;
  }
  context->gameStateInfo.field[testLine][FIELD_WIDTH - 1] = 0;
  
  // Проверяем, что функция определяет линию как неполную
  ck_assert_int_eq(fullLine(testLine), false);
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест для пустой линии
START_TEST(test_fullLine_empty) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Проверяем пустую линию (все ячейки нулевые по умолчанию)
  int testLine = 5;
  
  // Проверяем, что функция определяет линию как неполную
  ck_assert_int_eq(fullLine(testLine), false);
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Набор тестов для функции fullLine
Suite *suiteFullLine(void) {
  Suite *s = suite_create("suite_fullLine");
  TCase *tc = tcase_create("tc_fullLine");
  
  tcase_add_test(tc, test_fullLine_true);
  tcase_add_test(tc, test_fullLine_false);
  tcase_add_test(tc, test_fullLine_empty);
  
  suite_add_tcase(s, tc);
  return s;
}
