#include "s21_tests.h"

// Тест удаления линии из середины поля
START_TEST(test_removeLine_middle) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем разные линии разными значениями для отслеживания сдвига
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;  // Значение ячейки = номер строки + 1
    }
  }
  
  // Удаляем линию из середины
  int lineToRemove = 5;
  removeLine(lineToRemove);
  
  // Проверяем, что верхняя строка (0) стала пустой
  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }
  
  // Проверяем, что все строки выше удаленной сдвинулись вниз
  for (int i = 1; i <= lineToRemove; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i);  // Теперь значение должно быть на 1 меньше
    }
  }
  
  // Проверяем, что строки ниже удаленной остались без изменений
  for (int i = lineToRemove + 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i + 1);
    }
  }
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест удаления верхней линии
START_TEST(test_removeLine_top) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем разные линии разными значениями
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;
    }
  }
  
  // Удаляем верхнюю линию
  removeLine(0);
  
  // Проверяем, что верхняя строка (0) стала пустой
  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }
  
  // Проверяем, что все остальные строки остались без изменений
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i + 1);
    }
  }
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Тест удаления нижней линии
START_TEST(test_removeLine_bottom) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Создаем и заполняем поле
  context->gameStateInfo.field = createMatrix(FIELD_HEIGHT, FIELD_WIDTH);
  
  // Заполняем разные линии разными значениями
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      context->gameStateInfo.field[i][j] = i + 1;
    }
  }
  
  // Удаляем нижнюю линию
  int lastLine = FIELD_HEIGHT - 1;
  removeLine(lastLine);
  
  // Проверяем, что верхняя строка (0) стала пустой
  for (int j = 0; j < FIELD_WIDTH; j++) {
    ck_assert_int_eq(context->gameStateInfo.field[0][j], 0);
  }
  
  // Проверяем, что все строки сдвинулись вниз
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(context->gameStateInfo.field[i][j], i);
    }
  }
  
  // Очищаем ресурсы
  freeMatrix(context->gameStateInfo.field, FIELD_HEIGHT);
  context->gameStateInfo.field = NULL;
}
END_TEST

// Набор тестов для функции removeLine
Suite *suiteRemoveLine(void) {
  Suite *s = suite_create("suite_removeLine");
  TCase *tc = tcase_create("tc_removeLine");
  
  tcase_add_test(tc, test_removeLine_middle);
  tcase_add_test(tc, test_removeLine_top);
  tcase_add_test(tc, test_removeLine_bottom);
  
  suite_add_tcase(s, tc);
  return s;
}
