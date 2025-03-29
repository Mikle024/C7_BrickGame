#include "s21_tests.h"

// Тест очистки одной полной линии
START_TEST(test_clearLines_one_line) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем одну линию полностью
  int fullLine = 5;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    context->gameStateInfo.field[fullLine][j] = 1;
  }
  
  // Вызываем функцию и проверяем, что она вернула количество удаленных линий
  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, 1);
  
  // Проверяем, что линия была очищена (теперь она пустая)
  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[fullLine][j], 0);
  }
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест очистки нескольких полных линий
START_TEST(test_clearLines_multiple_lines) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем несколько линий полностью
  int fullLines[] = {3, 5, 8};
  int numFullLines = sizeof(fullLines) / sizeof(fullLines[0]);
  
  for (int i = 0; i < numFullLines; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[fullLines[i]][j] = 1;
    }
  }
  
  // Вызываем функцию и проверяем, что она вернула количество удаленных линий
  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, numFullLines);
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест, когда нет полных линий
START_TEST(test_clearLines_no_lines) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем линию, но оставляем одну ячейку пустой
  int nonFullLine = 5;
  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    context->gameStateInfo.field[nonFullLine][j] = 1;
  }
  context->gameStateInfo.field[nonFullLine][FIELD_WIDTH - 1] = 0;
  
  // Вызываем функцию и проверяем, что она вернула 0 (нет удаленных линий)
  int clearedLines = clearLines();
  ck_assert_int_eq(clearedLines, 0);
  
  // Проверяем, что линия не изменилась
  for (int j = 0; j < FIELD_WIDTH - 1; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[nonFullLine][j], 1);
  }
  ck_assert_int_eq(context->gameStateInfo.field[nonFullLine][FIELD_WIDTH - 1], 0);
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Набор тестов для функции clearLines
Suite *suiteClearLines(void) {
  Suite *s = suite_create("suite_clearLines");
  TCase *tc = tcase_create("tc_clearLines");
  
  tcase_add_test(tc, test_clearLines_one_line);
  tcase_add_test(tc, test_clearLines_multiple_lines);
  tcase_add_test(tc, test_clearLines_no_lines);
  
  suite_add_tcase(s, tc);
  return s;
}
