#ifndef MATRIX_H
#define MATRIX_H

typedef struct{
    int r, c;
    double* data;//matrix of [r][c]
} matrix;
matrix *matrix_create(int rows, int cols);
void _deallocate(matrix *a); 
matrix *add(matrix *a, matrix* b);
matrix *mult_matrix(matrix *a, matrix *b);
matrix *mult_scalar(matrix *a, double b);
matrix *transpose(matrix *a);
int convert(matrix *a, int i, int j);
int compare(matrix *a, matrix *b);//-1 if <, 0 if same, 1 if bigger
double get(matrix *a, int i, int j);
void _clear(matrix *a);

#endif // !MATRIX_H
