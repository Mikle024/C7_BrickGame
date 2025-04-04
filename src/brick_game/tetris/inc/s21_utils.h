#ifndef S21_UTILS_H
#define S21_UTILS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Creates a two-dimensional matrix of integers of the specified size.
 *
 * @param rows Number of rows in the matrix.
 * @param column Number of columns in the matrix.
 * @return int** Pointer to the created matrix or NULL in case of error.
 */
int **createMatrix(const int rows, const int column);

/**
 * @brief Frees memory allocated for a two-dimensional matrix.
 *
 * @param matrix Pointer to the matrix to be freed.
 * @param rows Number of rows in the matrix.
 */
void freeMatrix(int **matrix, const int rows);

#endif