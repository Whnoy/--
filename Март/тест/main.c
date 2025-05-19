#include "Matrix.h"


int main() {
    Matrix matrix = E(3);

    drawMatrix(matrix.matrix, matrix.rows, matrix.cols, stdout);
    printf("\n");

    printf("%lf\n", randab(100));

    freeSMatrix(matrix);

    return 0;
}

