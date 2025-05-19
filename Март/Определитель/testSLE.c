#include "testSLE.h"


int testRand(FILE *output) {
    unsigned n = 2;

    clock_t start=0, end=0;
    double *x;

    Matrix matrix;
    double *B;

    int res = 0;

    if (output == NULL) {
        return -1;
    }

    for (int i = 0; ((double)(end - start)) / CLOCKS_PER_SEC <= 4; i++, n *= 2) {
        matrix.matrix = createMatrix(n, n);
        matrix.rows = n;
        matrix.cols = n;
        matrix.acts = (MatActs){0, 1, 1};

        x = (double *)malloc(n * sizeof(double));
        B = (double *)malloc(n * sizeof(double));

        for (unsigned k = 0; k < n; k++) {
            B[k] = 0;
            x[k] = 0;
            for (unsigned j = 0; j < n; j++) {
                matrix.matrix[k][j] = randomDouble(10);
                B[k] += matrix.matrix[k][j];
            }
        }

        start = clock();
        res = sloveSLE(matrix.matrix, B, n, x);
        end = clock();
        if (res != 1) {
            n /= 2;
            for (int i = 0; i < n; i++) {
                free(matrix.matrix[i]);
            }
            free(matrix.matrix);
            continue;
        }
        fprintf(output, "%dx%d: %lf, %lf, %lf\n", n, n, ((double)(end - start)) / CLOCKS_PER_SEC, compareX(x, n), compareRes(matrix.matrix, x, B, n));


        for (int i = 0; i < n; i++) {
            free(matrix.matrix[i]);
        }
        free(matrix.matrix);
        free(x);
        free(B);
    }    
    
    return 0;
}

double compareX(double *x, unsigned n) {
    double res = 0;
    for (unsigned i = 0; i < n; i++) {
        res += (x[i]-1)*(x[i]-1);
    }
    return sqrt(res);
}

double compareRes(double **A, double *x,double *B, unsigned n) {
    double res = 0;
    double sum;
    for (unsigned i = 0; i < n; i++) {
        sum = 0;
        for (unsigned j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        res += (sum - B[i])*(sum - B[i]);
    }
    return sqrt(res);
}
