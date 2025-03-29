#include "inc/s21_utils.h"

/**
 * @brief Создает двумерную матрицу целых чисел заданного размера.
 *
 * @param rows Количество строк матрицы.
 * @param column Количество столбцов матрицы.
 * @return int** Указатель на созданную матрицу или NULL в случае ошибки.
 */
int **createMatrix(int rows, int column) {
  int **newMatrix = (int **)malloc(rows * sizeof(int *));
  if (newMatrix) {
    for (int i = 0; i < rows; i++) {
      newMatrix[i] = (int *)malloc(column * sizeof(int));
      if (newMatrix[i]) {
        for (int j = 0; j < column; j++) {
          newMatrix[i][j] = 0;
        }
      } else {
        // Если не удалось выделить память для строки, освобождаем ранее выделенную память
        for (int j = 0; j < i; j++) {
          free(newMatrix[j]);
        }
        free(newMatrix);
        return NULL;
      }
    }
    return newMatrix;
  }
  return NULL;
}

/**
 * @brief Освобождает память, выделенную под двумерную матрицу.
 *
 * @param matrix Указатель на матрицу для освобождения.
 * @param rows Количество строк в матрице.
 */
void freeMatrix(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
} 