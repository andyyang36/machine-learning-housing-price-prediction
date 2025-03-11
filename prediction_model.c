#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char* argv[]){
    if(argc != 3) {
        fprintf(stderr, "check code\n");
        return 1;
    }

    FILE* trainFile = fopen(argv[1], "r");
    if(!trainFile) {
        fprintf(stderr, "no file error check code\n");
        return 1;
    }

    char buffer[6];
    fscanf(trainFile, "%5s", buffer);

    if(strcmp(buffer, "train") != 0){
        fprintf(stderr, "error\n");
        fclose(trainFile);
        return 1;
    }

    int k, n;
    fscanf(trainFile, "%d", &k);  
    fscanf(trainFile, "%d", &n);  

    double** training_matrix = allocate_space_for_a_matrix(n, k + 1);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < k + 1; j++){
            fscanf(trainFile, "%lf", &training_matrix[i][j]);
        }
    }
    fclose(trainFile);

    double* price_vector = isolate_vector(training_matrix, n, k + 1);
    double** X = augment_matrix(training_matrix, n, k);
    double** X_transposed = transpose_matrix(X, n, k + 1);
    double** XTX = multiply_matrix(X_transposed, X, k + 1, n, n, k + 1);
    double** inv_XTX = invert_matrix(XTX, k + 1);
    double** Y = vector_to_matrix(price_vector, n);
    double** XTY = multiply_matrix(X_transposed, Y, k + 1, n, n, 1);
    double** W = multiply_matrix(inv_XTX, XTY, k + 1, k + 1, k + 1, 1);

    FILE* dataFile = fopen(argv[2], "r");
    if(!dataFile) {
        fprintf(stderr, "error\n");
        return 1;
    }

    fscanf(dataFile, "%5s", buffer);
    if(strcmp(buffer, "data") != 0){
        fprintf(stderr, "error\n");
        fclose(dataFile);
        return 1;
    }

    int test_k, m;
    fscanf(dataFile, "%d", &test_k);  
    fscanf(dataFile, "%d", &m);       

    if(test_k != k){
        fprintf(stderr, "error\n");
        fclose(dataFile);
        return 1;
    }

    double** test_matrix = allocate_space_for_a_matrix(m, test_k);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < test_k; j++){
            fscanf(dataFile, "%lf", &test_matrix[i][j]);
        }
    }
    fclose(dataFile);

    double** X_test = augment_matrix(test_matrix, m, test_k);
    double** predictions = multiply_matrix(X_test, W, m, k + 1, k + 1, 1);
    
    for (int i = 0; i < m; i++){
        printf("%.0f\n", predictions[i][0]);
    }

    free(price_vector);
    freeMatrix(training_matrix, n);
    freeMatrix(X, n);
    freeMatrix(XTY, k + 1);
    freeMatrix(W, k + 1);
    freeMatrix(test_matrix, m);
    freeMatrix(X_test, m);
    freeMatrix(predictions, m);
    freeMatrix(X_transposed, k + 1);
    freeMatrix(XTX, k + 1);
    freeMatrix(inv_XTX, k + 1);
    freeMatrix(Y, n);


    return 0;
}
