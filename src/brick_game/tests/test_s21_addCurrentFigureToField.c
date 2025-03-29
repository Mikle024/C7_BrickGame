#include "s21_tests.h"

START_TEST(test_addCurrentFigureToField_positive) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Очищаем поле
  context->gameStateInfo.field = calloc(FIELD_HEIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    context->gameStateInfo.field[i] = calloc(FIELD_WIDTH, sizeof(int));
  }

  // Создаем фигуру и задаем координаты
  context->currentFigure = createFigure(2);
  context->figureX = 4;
  context->figureY = 6;

  // Вызываем функцию
  addCurrentFigureToField();

  // Проверяем, что фигура добавлена на поле
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (context->currentFigure[i][j] != 0 && context->figureY + i >= 0 &&
          context->figureY + i < FIELD_HEIGHT && context->figureX + j >= 0 &&
          context->figureX + j < FIELD_WIDTH) {
        ck_assert_int_eq(context->gameStateInfo
                             .field[context->figureY + i][context->figureX + j],
                         context->currentFigure[i][j]);
      }
    }
  }

  // Очищаем память
  freeMatrix(context->currentFigure, FIGURE_SIZE);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(context->gameStateInfo.field[i]);
  }
  free(context->gameStateInfo.field);
}
END_TEST

Suite *suiteAddCurrentFigureToField(void) {
  Suite *s = suite_create("suite_addCurrentFigureToField");
  TCase *tc_core = tcase_create("tc_addCurrentFigureToField");

  tcase_add_test(tc_core, test_addCurrentFigureToField_positive);

  suite_add_tcase(s, tc_core);
  return s;
}