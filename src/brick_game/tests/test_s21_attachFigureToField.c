#include "s21_tests.h"

START_TEST(test_attachFigureToField_positive) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем и заполняем поле
  context->gameStateInfo.field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    context->gameStateInfo.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  // Создаем фигуру
  context->currentFigure = createFigure(2);  // Любая тестовая фигура

  // Устанавливаем координаты фигуры (в пределах поля)
  context->figureX = 3;
  context->figureY = 5;

  // Вызываем attachFigureToField
  bool outOfField = attachFigureToField();

  // Проверяем, что фигура добавлена на поле (все ненулевые элементы заменились
  // на 8)
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = context->figureX + j;
        int fieldY = context->figureY + i;

        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          ck_assert_int_eq(context->gameStateInfo.field[fieldY][fieldX], 8);
        }
      }
    }
  }

  // Проверяем, что игра не окончена (фигура не выходит за верхнюю границу)
  ck_assert_int_eq(outOfField, false);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(context->gameStateInfo.field[i]);
  }
  free(context->gameStateInfo.field);
}
END_TEST

START_TEST(test_attachFigureToField_gameOver) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем и заполняем поле
  context->gameStateInfo.field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    context->gameStateInfo.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  // Создаем фигуру
  context->currentFigure = createFigure(2);

  // Устанавливаем координаты так, чтобы часть фигуры выходила за верхнюю
  // границу
  context->figureX = 3;
  context->figureY = -1;

  // Вызываем attachFigureToField
  bool outOfField = attachFigureToField();

  // Проверяем, что игра окончена
  ck_assert_int_eq(outOfField, true);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(context->gameStateInfo.field[i]);
  }
  free(context->gameStateInfo.field);
}
END_TEST

Suite *suiteAttachFigureToField(void) {
  Suite *s = suite_create("suite_attachFigureToField");
  TCase *tc_core = tcase_create("tc_attachFigureToField");

  tcase_add_test(tc_core, test_attachFigureToField_positive);
  tcase_add_test(tc_core, test_attachFigureToField_gameOver);

  suite_add_tcase(s, tc_core);
  return s;
}