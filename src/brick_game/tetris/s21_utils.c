#include "inc/s21_utils.h"

int **createMatrix(const int rows, const int column) {
  int **result = NULL;
  if (rows >= 0 && column >= 0) {
    int **newMatrix = (int **)malloc(rows * sizeof(int *));
    if (newMatrix) {
      bool allocationError = false;
      for (int i = 0; i < rows && !allocationError; i++) {
        newMatrix[i] = (int *)calloc(column, sizeof(int));
        if (!newMatrix[i]) {
          freeMatrix(newMatrix, i);
          allocationError = true;
        }
      }

      if (!allocationError) {
        result = newMatrix;
      }
    }
  }
  return result;
}

void freeMatrix(int **matrix, const int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) {
      free(matrix[i]);
    }
    free(matrix);
  }
}