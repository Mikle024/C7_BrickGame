#include "inc/s21_file_utils.h"

/**
 * @brief Инициализирует высокий счет из файла.
 *
 * @return int Загруженное значение высокого счета или 0, если ошибка.
 */
int initHighScore() {
  FILE *fp = fopen("highScore.txt", "r");
  int highScore = 0;

  if (fp) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';

      char *endPtr;
      long score = strtol(buffer, &endPtr, 10);

      if (endPtr == buffer || *endPtr != '\0' || score <= 0) {
        highScore = 0;
      } else {
        highScore = (int)score;
      }
    }
    fclose(fp);
  }

  return highScore;
}

/**
 * @brief Обновляет высокий счет в файле.
 *
 * @param score Новое значение высокого счета.
 */
void updateScore(int score) {
  FILE *fp = fopen("highScore.txt", "w");
  if (fp) {
    fprintf(fp, "%d", score);
    fclose(fp);
  }
} 