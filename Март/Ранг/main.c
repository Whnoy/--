#include "headers.h"


int main(void) {
    FILE *output;
    unsigned n = rand() % 5 + 1;
    unsigned m = rand() % 5 + 1;
    Matrix matrix;


    matrix.matrix = createMatrix(n, m);
    matrix.rows = n;
        matrix.cols = n;
        matrix.acts = (MatActs){0, 1, 1};

    for (unsigned k = 0; k < n; k++) {
        for (unsigned j = 0; j < m; j++) {
            matrix.matrix[k][j] = randomDouble(10);
            printf("%lf ", matrix.matrix[k][j]);
        } printf("\n");
    } printf("\n");

    normiseMatrix(matrix.matrix, n, m, &matrix.acts);
    printf("Matrix rank: %d\n", findMatRnak(matrix.matrix, n, m));

    for (int i = 0; i < n; i++) {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);  

    return 0;
}