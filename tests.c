#include "matrix.h"
#include <assert.h>
#include <stdio.h>

int main() {
    matrix *a = matrix_create(2, 2);
    matrix *b = matrix_create(2, 2);

    a->data[convert(a, 0, 0)] = 1;
    a->data[convert(a, 0, 1)] = 2;
    a->data[convert(a, 1, 0)] = 3;
    a->data[convert(a, 1, 1)] = 4;

    b->data[convert(b, 0, 0)] = 5;
    b->data[convert(b, 0, 1)] = 6;
    b->data[convert(b, 1, 0)] = 7;
    b->data[convert(b, 1, 1)] = 8;

    matrix *c = mult_matrix(a, b);
    assert(c != NULL);

    assert(get(c, 0, 0) == 19.0);
    assert(get(c, 0, 1) == 22.0);
    assert(get(c, 1, 0) == 43.0);
    assert(get(c, 1, 1) == 50.0);

    printf("matrix multiplication test passed\n");

    _deallocate(a);
    _deallocate(b);
    _deallocate(c);

    return 0;
}
