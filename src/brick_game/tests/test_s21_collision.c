#include "s21_tests.h"

START_TEST(test_collision_bottom) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем фигуру I (индекс 0)
  context->currentFigure =
      createFigure(0);  // Используем createFigure для создания фигуры

  // Устанавливаем координаты фигуры так, чтобы она была ниже поля
  context->figureY = FIELD_HEIGHT;  // фигура "выпадает" за нижнюю границу

  // Проверяем, что есть столкновение
  ck_assert_int_eq(collision(), true);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

START_TEST(test_collision_left_right) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);

  // Создаем фигуру I (индекс 0)
  context->currentFigure =
      createFigure(0);  // Используем createFigure для создания фигуры

  // Устанавливаем координаты фигуры так, чтобы она находилась за пределами поля
  // по X
  context->figureX = -1;  // фигура выходит за левую границу

  // Проверяем, что есть столкновение
  ck_assert_int_eq(collision(), true);

  // Теперь проверим для правой границы
  context->figureX = FIELD_WIDTH;  // фигура выходит за правую границу
  ck_assert_int_eq(collision(), true);

  // Очистка памяти
  freeMatrix(context->currentFigure, FIGURE_SIZE);
}
END_TEST

// START_TEST(test_collision_with_other_blocks) {
//   GameContext_t *context = getCurrentContext();
//   ck_assert_ptr_nonnull(context);
//
//   // Создаем фигуру I (индекс 0)
//   context->currentFigure =
//       createFigure(0);  // Используем createFigure для создания фигуры
//
//   // Заполняем поле фигурами, с которыми будет столкновение
//   context->gameStateInfo.field[3][1] =
//       2;  // Столкновение с блоком на этом месте
//
//   // Устанавливаем координаты фигуры
//   context->figureY = 0;
//   context->figureX = 1;
//
//   // Проверяем, что есть столкновение с блоком
//   ck_assert_int_eq(collision(), true);
//
//   // Очистка памяти
//   freeMatrix(context->currentFigure, FIGURE_SIZE);
// }
// END_TEST
//
// START_TEST(test_collision_no_collision) {
//   GameContext_t *context = getCurrentContext();
//   ck_assert_ptr_nonnull(context);
//
//   // Создаем фигуру I (индекс 0)
//   context->currentFigure =
//       createFigure(0);  // Используем createFigure для создания фигуры
//
//   // Заполняем поле пустыми значениями, нет столкновений
//   for (int i = 0; i < FIELD_HEIGHT; i++) {
//     for (int j = 0; j < FIELD_WIDTH; j++) {
//       context->gameStateInfo.field[i][j] = 0;
//     }
//   }
//
//   // Устанавливаем координаты фигуры так, чтобы не было столкновений
//   context->figureY = 0;
//   context->figureX = 4;
//
//   // Проверяем, что нет столкновений
//   ck_assert_int_eq(collision(), false);
//
//   // Очистка памяти
//   freeMatrix(context->currentFigure, FIGURE_SIZE);
// }
// END_TEST

Suite *suiteCollision(void) {
  Suite *s = suite_create("suite_collision");
  TCase *tc_core = tcase_create("tc_collision");

  tcase_add_test(tc_core, test_collision_bottom);
  tcase_add_test(tc_core, test_collision_left_right);
//    tcase_add_test(tc_core, test_collision_with_other_blocks);
//    tcase_add_test(tc_core, test_collision_no_collision);

  suite_add_tcase(s, tc_core);
  return s;
}