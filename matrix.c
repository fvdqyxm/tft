#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

int convert(matrix *a, int i, int j) {
    return i * (a -> c) + j;
}
matrix *matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }

    size_t elem_count = (size_t)rows * (size_t)cols;
    double *arr = malloc(elem_count * sizeof(double));
    if (arr == NULL) {
        return NULL;
    }

    matrix *ans = malloc(sizeof(matrix));
    if (ans == NULL) {
        free(arr);
        return NULL;
    }

    ans -> r = rows;
    ans -> c = cols;
    ans -> data = arr;
    return ans;
}
void _deallocate(matrix *a) {
    if (a == NULL) {
        return;
    }
    free (a -> data);
    free (a);
}
matrix *add(matrix *a, matrix *b) {
    if (a == NULL || b == NULL || a -> r != b -> r || a -> c != b -> c) {
        return NULL;
    }

    matrix *res = matrix_create(a -> r, a -> c);
    if (res == NULL) {
        return NULL;
    }

    int n = a -> r * a -> c;
    double *restrict dst = res -> data;
    double *restrict src_a = a -> data;
    double *restrict src_b = b -> data;
    for (int i = 0; i < n; i++) {
        dst[i] = src_a[i] + src_b[i];
    }

    return res;
}
matrix *mult_scalar(matrix *a, double b) {
    if (a == NULL) {
        return NULL;
    }

    matrix *res = matrix_create(a -> r, a -> c);
    if (res == NULL) {
        return NULL;
    }

    int n = a -> r * a -> c;
    double *restrict dst = res -> data;
    double *restrict src = a -> data;
    for (int i = 0; i < n; i++) {
        dst[i] = src[i] * b;
    }

    return res;
}
matrix *mult_matrix(matrix *a, matrix *b) {
    if (a == NULL || b == NULL || a -> c != b -> r) {
        return NULL;
    }

    int a_rows = a -> r;
    int a_cols = a -> c;
    int b_cols = b -> c;
    matrix *ans = matrix_create(a_rows, b_cols);
    if (ans == NULL) {
        return NULL;
    }

    int out_count = a_rows * b_cols;
    for (int i = 0; i < out_count; i++) {
        ans -> data[i] = 0.0;
    }

    double *restrict out = ans -> data;
    double *restrict lhs = a -> data;
    double *restrict rhs = b -> data;

    for (int i = 0; i < a_rows; i++) {
        double *restrict out_row = out + (i * b_cols);
        double *restrict lhs_row = lhs + (i * a_cols);
        for (int k = 0; k < a_cols; k++) {
            double a_ik = lhs_row[k];
            double *restrict rhs_row = rhs + (k * b_cols);
            for (int j = 0; j < b_cols; j++) {
                out_row[j] += a_ik * rhs_row[j];
            }
        }
    }

    return ans;
}

matrix *transpose(matrix *a) {
    if (a == NULL) {
        return NULL;
    }

    matrix *ans = matrix_create(a -> c, a -> r);
    if (ans == NULL) {
        return NULL;
    }

    int rows = a -> r;
    int cols = a -> c;
    for (int i = 0; i < rows; i++) {
        int row_offset = i * cols;
        for (int j = 0; j < cols; j++) {
            ans -> data[(j * rows) + i] = a -> data[row_offset + j];
        }
    }

    return ans;
}
double get(matrix *a, int i, int j) {
    return a -> data[(i * a -> c) + j];
}

void print(matrix *a) {
    for (int i = 0; i < a -> r; i++) {
        for (int j = 0; j < a -> c; j++) {
            printf("%g ", ((a -> data)[convert(a, i, j)]));
        }
        printf("\n");
    }
}
void set(matrix *a, int i, int j, double val) {
    a->data[convert(a, i, j)] = val;
}
