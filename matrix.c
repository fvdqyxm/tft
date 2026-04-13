#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

int convert(matrix *a, int i, int j) {
    return i * (a -> c) + j;
}
matrix *matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {return NULL;}

    double *arr = malloc(rows * cols * sizeof(double));
    matrix *ans = malloc(sizeof(matrix));
    ans -> r = rows;
    ans -> c = cols;
    ans -> data = arr;
    return ans;
}
void _deallocate(matrix *a) {
    free (a -> data);
    free (a);
}
matrix *add(matrix *a, matrix *b) {
    if(a -> r != b -> r || a -> c != b -> c) {
        return NULL;
    }
    matrix *res = matrix_create(a -> r, a -> c);
    for(int i = 0; i < a -> r; i++) {
        for(int j = 0; j < a -> c; j++) {
            int index = (a -> c) * i + j;
            (res -> data)[index] = (a -> data)[index] + (b -> data)[index];
        }
    }
    return res;
}
matrix *mult_scalar(matrix *a, double b) {
    matrix *res = matrix_create(a -> r, a -> c);
    for(int i = 0; i < a -> r; i++) {
        for(int j = 0 ; j < a -> c; j++) {
            (res -> data)[(i * (a -> c) + j)] = ((a -> data)[i * (a -> c) + j]) * b;
        }
    }
    return res;
}
matrix *mult_matrix(matrix *a, matrix *b) {
    if(a -> c != b -> r) {
        return NULL;
    }
    //a is r x c, b is c x w -> result is r x w 
    matrix *ans = matrix_create(a -> r, b -> c);
    //first iterate along the rows of B, for each column of b, we'll executive multiplication
    for(int i = 0; i < a -> r; i++) {
        for(int j = 0; j < b -> c; j++) {
            double sum = 0;
            for(int k = 0; k < a -> c; k++) {
                sum = sum + (a -> data)[convert(a, i, k)] * (b -> data)[convert(b, k, j)];
            }
            ans -> data[convert(ans, i, j)] = sum;
        }
    }
    return ans;
}

matrix *transpose(matrix *a) {
    matrix *ans = matrix_create(a -> c, a -> r);
    for(int i = 0; i < a -> r; i++) {
        for(int j = 0; j < a -> c; j++) {
            (ans -> data)[convert(ans, j, i)] = (a -> data)[convert(a, i, j)];
        }
    }
    return ans;
}
double get(matrix *a, int i, int j) {
    return a -> data[convert(a, i, j)];
}

void print(matrix *a) {
    for(int i = 0; i < a -> r; i++) {
        for(int j = 0; j < a -> c; j++) {
            printf("%d ", ((a -> data)[convert(a, i, j)]));
        }
        printf("\n");
    }
}
void set(matrix *a, int i, int j, double val) {
    a->data[convert(a, i, j)] = val;
}

