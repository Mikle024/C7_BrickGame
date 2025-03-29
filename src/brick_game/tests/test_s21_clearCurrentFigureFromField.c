#include "s21_tests.h"

START_TEST(test_clearCurrentFigureFromField_positive) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем и заполняем поле
  context->gameStateInfo.field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    context->gameStateInfo.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  // Создаем фигуру
  context->currentFigure = createFigure(2);

  // Устанавливаем старые координаты
  context->oldFigureX = 3;
  context->oldFigureY = 5;

  // "Добавляем" фигуру на поле вручную
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0) {
        int fieldX = context->oldFigureX + j;
        int fieldY = context->oldFigureY + i;

        if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
            fieldY < FIELD_HEIGHT) {
          context->gameStateInfo.field[fieldY][fieldX] =
              context->currentFigure[i][j];
        }
      }
    }
  }

  // Вызываем функцию очистки
  clearCurrentFigureFromField();

  // Проверяем, что поле очищено в нужных местах
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      int fieldX = context->oldFigureX + j;
      int fieldY = context->oldFigureY + i;

      if (fieldX >= 0 && fieldX < FIELD_WIDTH && fieldY >= 0 &&
          fieldY < FIELD_HEIGHT) {
        ck_assert_int_eq(context->gameStateInfo.field[fieldY][fieldX], 0);
      }
    }
  }

  // Проверяем, что oldFigureX и oldFigureY обновились
  ck_assert_int_eq(context->oldFigureX, context->figureX);
  ck_assert_int_eq(context->oldFigureY, context->figureY);

  // Освобождаем память
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(context->gameStateInfo.field[i]);
  }
  free(context->gameStateInfo.field);
}
END_TEST

Suite *suiteClearCurrentFigureFromField(void) {
  Suite *s = suite_create("suite_clearCurrentFigureFromField");
  TCase *tc_core = tcase_create("tc_clearCurrentFigureFromField");

  tcase_add_test(tc_core, test_clearCurrentFigureFromField_positive);

  suite_add_tcase(s, tc_core);
  return s;
}