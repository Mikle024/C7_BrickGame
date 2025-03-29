#ifndef S21_UTILS_H
#define S21_UTILS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Создает двумерную матрицу целых чисел заданного размера.
 *
 * @param rows Количество строк матрицы.
 * @param column Количество столбцов матрицы.
 * @return int** Указатель на созданную матрицу или NULL в случае ошибки.
 */
int **createMatrix(int rows, int column);

/**
 * @brief Освобождает память, выделенную под двумерную матрицу.
 *
 * @param matrix Указатель на матрицу для освобождения.
 * @param rows Количество строк в матрице.
 */
void freeMatrix(int **matrix, int rows);

#endif 