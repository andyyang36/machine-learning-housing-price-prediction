#ifndef MATRIX_H
#define MATRIX_H

double** allocate_space_for_a_matrix(int rows, int cols);
void freeMatrix(double** matrix, int rows);
double** createMatrix(int rows, int cols);

double* isolate_vector(double** matrix, int rows, int cols);
double** augment_matrix(double** training_matrix, int rows, int cols);
double** transpose_matrix(double** matrix, int rows, int cols);
double** multiply_matrix(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2);
double** invert_matrix(double** matrix, int n);
double** vector_to_matrix(double* vector, int n);

#endif /* MATRIX_H */
