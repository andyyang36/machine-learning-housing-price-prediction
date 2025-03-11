#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_functions.h"

typedef struct {
    double* price_vector;
    double** training_matrix;
    double** X;
    double** X_transposed;
    double** XTX;
    double** inv_XTX;
    double** Y;
    double** XTY;
    double** W;
    double** test_matrix;
    double** X_test;
    double** predictions;
    // Include dimensions if needed for cleanup functions
    int n;
    int k;
    int m;
} ModelData;

void freeAll(ModelData *data) {
    if(data->price_vector)
        free(data->price_vector);
    if(data->training_matrix)
        freeMatrix(data->training_matrix, data->n);
    if(data->X)
        freeMatrix(data->X, data->n);
    if(data->X_transposed)
        freeMatrix(data->X_transposed, data->k + 1);
    if(data->XTX)
        freeMatrix(data->XTX, data->k + 1);
    if(data->inv_XTX)
        freeMatrix(data->inv_XTX, data->k + 1);
    if(data->Y)
        freeMatrix(data->Y, data->n);
    if(data->XTY)
        freeMatrix(data->XTY, data->k + 1);
    if(data->W)
        freeMatrix(data->W, data->k + 1);
    if(data->test_matrix)
        freeMatrix(data->test_matrix, data->m);
    if(data->X_test)
        freeMatrix(data->X_test, data->m);
    if(data->predictions)
        freeMatrix(data->predictions, data->m);
}

int main(int argc, char* argv[]){
    if(argc != 3) {
        fprintf(stderr, "check code\n");
        return 1;
    }

    ModelData data = {0};  // Zero initialize all pointers and ints

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
    data.k = k;
    data.n = n;

    data.training_matrix = allocate_space_for_a_matrix(n, k + 1);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < k + 1; j++){
            fscanf(trainFile, "%lf", &data.training_matrix[i][j]);
        }
    }
    fclose(trainFile);

    data.price_vector = isolate_vector(data.training_matrix, n, k + 1);
    data.X = augment_matrix(data.training_matrix, n, k);
    data.X_transposed = transpose_matrix(data.X, n, k + 1);
    data.XTX = multiply_matrix(data.X_transposed, data.X, k + 1, n, n, k + 1);
    data.inv_XTX = invert_matrix(data.XTX, k + 1);
    data.Y = vector_to_matrix(data.price_vector, n);
    data.XTY = multiply_matrix(data.X_transposed, data.Y, k + 1, n, n, 1);
    data.W = multiply_matrix(data.inv_XTX, data.XTY, k + 1, k + 1, k + 1, 1);

    FILE* dataFile = fopen(argv[2], "r");
    if(!dataFile) {
        fprintf(stderr, "error\n");
        freeAll(&data);
        return 1;
    }

    fscanf(dataFile, "%5s", buffer);
    if(strcmp(buffer, "data") != 0){
        fprintf(stderr, "error\n");
        fclose(dataFile);
        freeAll(&data);
        return 1;
    }

    int test_k, m;
    fscanf(dataFile, "%d", &test_k);  
    fscanf(dataFile, "%d", &m);
    data.m = m;

    if(test_k != k){
        fprintf(stderr, "error\n");
        fclose(dataFile);
        freeAll(&data);
        return 1;
    }

    data.test_matrix = allocate_space_for_a_matrix(m, test_k);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < test_k; j++){
            fscanf(dataFile, "%lf", &data.test_matrix[i][j]);
        }
    }
    fclose(dataFile);

    data.X_test = augment_matrix(data.test_matrix, m, test_k);
    data.predictions = multiply_matrix(data.X_test, data.W, m, k + 1, k + 1, 1);
    
    for (int i = 0; i < m; i++){
        printf("%.0f\n", data.predictions[i][0]);
    }

    freeAll(&data);
    return 0;
}
