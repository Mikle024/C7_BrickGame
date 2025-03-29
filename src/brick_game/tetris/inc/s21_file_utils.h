#ifndef S21_FILE_UTILS_H
#define S21_FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Инициализирует высокий счет из файла.
 *
 * @return int Загруженное значение высокого счета или 0, если ошибка.
 */
int initHighScore();

/**
 * @brief Обновляет высокий счет в файле.
 *
 * @param score Новое значение высокого счета.
 */
void updateScore(int score);

#endif 