#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

double** allocate_space_for_a_matrix(int rows, int cols) {
    double** created_matrix = malloc(sizeof(double*) * rows);
    for (int i = 0; i < rows; i++){
        created_matrix[i] = malloc(sizeof(double) * cols);
    }
    return created_matrix; 
}

void freeMatrix(double** matrix, int rows){
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}

double** createMatrix(int rows, int cols){  
    double** matrix = allocate_space_for_a_matrix(rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            scanf("%lf", &matrix[i][j]);
        }
    }
    return matrix;
}

double* isolate_vector(double** matrix, int rows, int cols){
    double* vector = malloc(sizeof(double) * rows);
    for (int i = 0; i < rows; i++){
        vector[i] = matrix[i][cols - 1]; 
    }
    return vector;
}

double** augment_matrix(double** training_matrix, int rows, int cols){
    double** augmented_matrix = allocate_space_for_a_matrix(rows, cols + 1);
    for (int i = 0; i < rows; i++){
        augmented_matrix[i][0] = 1.0;
        for (int j = 1; j < cols + 1; j++){
            augmented_matrix[i][j] = training_matrix[i][j - 1];
        }
    }
    return augmented_matrix;
}

double** transpose_matrix(double** matrix, int rows, int cols){
    double** transposed_matrix = allocate_space_for_a_matrix(cols, rows);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            transposed_matrix[j][i] = matrix[i][j];
        }
    }
    return transposed_matrix;
}

double** multiply_matrix(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2) {
    if (cols1 != rows2) {
        printf("ERROR: Incompatible dimensions for matrix multiplication\n");
        return NULL;
    }
    double** result = allocate_space_for_a_matrix(rows1, cols2);
    for (int i = 0; i < rows1; i++){
        for (int j = 0; j < cols2; j++){
            result[i][j] = 0.0;
            for (int k = 0; k < cols1; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

double** invert_matrix(double** matrix, int n) {
    double** aug = allocate_space_for_a_matrix(n, 2 * n);
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            aug[i][j] = matrix[i][j];
        }
        for (int j = n; j < 2 * n; j++){
            aug[i][j] = (i == (j - n)) ? 1.0 : 0.0;
        }
    }
    
    for (int i = 0; i < n; i++){
        double pivot = aug[i][i];
        if (pivot == 0) {
            printf("Error: pivot is zero\n");
            freeMatrix(aug, n);
            return NULL;
        }
        for (int j = 0; j < 2 * n; j++){
            aug[i][j] /= pivot;
        }
        for (int k = 0; k < n; k++){
            if (k != i){
                double factor = aug[k][i];
                for (int j = 0; j < 2 * n; j++){
                    aug[k][j] -= factor * aug[i][j];
                }
            }
        }
    }
    
    double** inverse = allocate_space_for_a_matrix(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            inverse[i][j] = aug[i][j + n];
        }
    }
    freeMatrix(aug, n);
    return inverse;
}

double** vector_to_matrix(double* vector, int n) {
    double** mat = allocate_space_for_a_matrix(n, 1);
    for (int i = 0; i < n; i++){
        mat[i][0] = vector[i];
    }
    return mat;
}
