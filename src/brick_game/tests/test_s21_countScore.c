#include "s21_tests.h"

// Тест подсчета очков для разного количества линий
START_TEST(test_countScore_lines) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalScore = context->gameStateInfo.score;
  int originalLevel = context->gameStateInfo.level;
  int originalSpeed = context->gameStateInfo.speed;
  int originalHighScore = context->gameStateInfo.high_score;
  
  // Устанавливаем начальное состояние
  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.high_score = 2000;
  
  // Тестируем очки за 1 линию
  countScore(1);
  ck_assert_int_eq(context->gameStateInfo.score, 100);
  
  // Тестируем очки за 2 линии
  countScore(2);
  ck_assert_int_eq(context->gameStateInfo.score, 100 + 300);
  
  // Тестируем очки за 3 линии
  countScore(3);
  ck_assert_int_eq(context->gameStateInfo.score, 100 + 300 + 700);
  
  // Тестируем очки за 4 линии
  countScore(4);
  ck_assert_int_eq(context->gameStateInfo.score, 100 + 300 + 700 + 1500);
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.score = originalScore;
  context->gameStateInfo.level = originalLevel;
  context->gameStateInfo.speed = originalSpeed;
  context->gameStateInfo.high_score = originalHighScore;
}
END_TEST

// Тест изменения уровня при наборе очков
START_TEST(test_countScore_level_change) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalScore = context->gameStateInfo.score;
  int originalLevel = context->gameStateInfo.level;
  int originalSpeed = context->gameStateInfo.speed;
  int originalHighScore = context->gameStateInfo.high_score;
  
  // Устанавливаем начальное состояние
  context->gameStateInfo.score = 0;
  context->gameStateInfo.level = 1;
  context->gameStateInfo.high_score = 10000;
  
  // Тестируем повышение уровня
  // В коде level = 1 + (score / 600)
  
  // Набираем 599 очков - уровень должен остаться 1
  countScore(4); // +1500 очков
  context->gameStateInfo.score = 599;
  countScore(0); // Обновляем уровень без добавления очков
  ck_assert_int_eq(context->gameStateInfo.level, 1);
  
  // Набираем 601 очко - уровень должен стать 2
  context->gameStateInfo.score = 601;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, 2);
  
  // Набираем 1201 очко - уровень должен стать 3
  context->gameStateInfo.score = 1201;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.level, 3);
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.score = originalScore;
  context->gameStateInfo.level = originalLevel;
  context->gameStateInfo.speed = originalSpeed;
  context->gameStateInfo.high_score = originalHighScore;
}
END_TEST

// Тест обновления высокого счета
START_TEST(test_countScore_high_score) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalScore = context->gameStateInfo.score;
  int originalLevel = context->gameStateInfo.level;
  int originalHighScore = context->gameStateInfo.high_score;
  
  // Устанавливаем начальное состояние
  context->gameStateInfo.score = 100;
  context->gameStateInfo.high_score = 1000;
  
  // Оставляем счет меньше рекорда - рекорд не должен измениться
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 1000);
  
  // Увеличиваем счет больше рекорда - рекорд должен обновиться
  context->gameStateInfo.score = 1100;
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.high_score, 1100);
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.score = originalScore;
  context->gameStateInfo.level = originalLevel;
  context->gameStateInfo.high_score = originalHighScore;
}
END_TEST

// Тест нулевых линий и обработки неправильных значений
START_TEST(test_countScore_edge_cases) {
  GameContext_t *context = getCurrentContext();
  ck_assert_ptr_nonnull(context);
  
  // Сохраняем исходное состояние
  int originalScore = context->gameStateInfo.score;
  
  // Устанавливаем начальное состояние
  context->gameStateInfo.score = 0;
  
  // Тест с нулевым количеством линий
  countScore(0);
  ck_assert_int_eq(context->gameStateInfo.score, 0);
  
  // Тест с отрицательным количеством линий (должен обрабатываться как 0)
  countScore(-1);
  ck_assert_int_eq(context->gameStateInfo.score, 0);
  
  // Тест со слишком большим количеством линий (индекс за пределами массива)
  int beforeScore = context->gameStateInfo.score;
  countScore(5); // Должен использовать безопасную индексацию
  ck_assert_int_ge(context->gameStateInfo.score, beforeScore); // Счет должен не уменьшиться
  
  // Восстанавливаем исходное состояние
  context->gameStateInfo.score = originalScore;
}
END_TEST

// Набор тестов для функции countScore
Suite *suiteCountScore(void) {
  Suite *s = suite_create("suite_countScore");
  TCase *tc = tcase_create("tc_countScore");
  
  tcase_add_test(tc, test_countScore_lines);
  tcase_add_test(tc, test_countScore_level_change);
  tcase_add_test(tc, test_countScore_high_score);
  tcase_add_test(tc, test_countScore_edge_cases);
  
  suite_add_tcase(s, tc);
  return s;
}
