#include "headers.h"


Matrix generateMatrix(int n, int m) {
    Matrix matrix;;
    double sum;

    if (n <= 0 || m <= 0) {
        return (Matrix){NULL, 0, 0, {0, 1, 1}};
    }
    matrix.matrix = createMatrix(n, m);
    matrix.rows = n;
    matrix.cols = m;
    matrix.acts = (MatActs){0, 1, 1};

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix.matrix[i][j] = randab(1000);
        }
    }

    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = 0; j < m; j++) {
            sum += fabs(matrix.matrix[i][j]);
        }
        matrix.matrix[i][i] = sum;
        matrix.matrix[i][i] += rand() & 10;
    }

    return matrix;
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


int test(double *func (Matrix, double *, double)) {
    int n = 2;
    Matrix A;
    double *B, *x, k;
    clock_t start, end;

    for (int i = 0; i < 12; i++, n *= 2) {

        A = generateMatrix(n, n);
        B = malloc(A.cols * sizeof(double));

        for (int j = 0; j < A.cols; j++) {
            B[j] = 0;
            for (int k = 0; k < A.rows; k++) {
                B[j] += A.matrix[j][k];
            }
        }
        
        printf("Матрица размера %d\t", n);

        start = clock();
        x = func(A, B, 1e-6);
        end = clock();

        printf("Время: %lf\t Тесты: %.20lf %.20lf\n", (double)(end - start) / CLOCKS_PER_SEC, compareX(x, n), compareRes(A.matrix, x, B, n));

        freeSMatrix(A);
        free(B);
        free(x);
    }
    return 0;

}