#include "Matrix.h"


double **createMatrix(int n, int m) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }
    return matrix;
}

void swapRows(double** A, unsigned n, unsigned m,MatActs *acts) {
    double *temp = A[n];
    A[n] = A[m];
    A[m] = temp;
    acts->swaps++;
    
}

void multiplyRow(double **A, unsigned row, double factor, int m, MatActs *acts) {
    acts->mults *= factor;
    for (int j = 0; j < m; j++) {
        A[row][j] *= factor;
    }
}

void multiplyMatrix(double **A, unsigned n, unsigned m, double factor, MatActs *acts) {
    for (unsigned i = 0; i < n; i++) {
        multiplyRow(A, i, factor, m, acts);
    }
}

void addRows(double **matrix, unsigned cols, double factor, unsigned in, unsigned out) {
    for (unsigned j = 0; j < cols; j++) {
        matrix[in][j] += matrix[out][j] * factor;
    }
}  

int _findRowMax(double **A, int n, int m, int row) {
    double max = fabs(A[m][row]);
    int maxRow = m;
    for (int i = m+1; i < n; i++) {
        if (fabs(A[i][row]) > max) {
            max = fabs(A[i][row]);
            maxRow = i;
        }
    }
    return maxRow;
}


MatActs rungByGauss(double **A, int n, int m) {
    MatActs acts = {0, 1, 1};
    for (int i = 0; i < m && i < n; i++) {
        // Найти строку с максимальным элементом в текущем столбце
        int maxRow = _findRowMax(A, n, i, i);
        if (maxRow != i) {
            swapRows(A, i, maxRow, &acts);
        }
        if (fabs(A[i][i]) > 0) {
            multiplyRow(A, i, -1, m, &acts);
        }

        // Проверить, что ведущий элемент не равен нулю
        if (fabs(A[i][i]) < n*1e-14) {
            continue;
        }

        // Обнулить элементы ниже ведущего
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[j][i]) < n*1e-15) { continue; }
            double factor = A[j][i] / A[i][i];
            addRows(A, m, -factor, j, i); // Используем -factor для вычитания
        }
    }
    return acts;
}


void normiseMatrix(double **A, unsigned n, unsigned m, MatActs *acts) {
    double max = 0, maxNew = 0;
    for (unsigned j = 0; j < m; j++) {
        max += fabs(A[0][j]);
    }
    for (unsigned i = 1; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            maxNew += fabs(A[i][j]);
        }
        if (maxNew > max) {
            max = maxNew;
        }
        maxNew = 0;
    }

    multiplyMatrix(A, n, m, 1 / max, acts);
}


void drawMatrix(double **A, unsigned n, unsigned m) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            printf("%lf ", A[i][j]);
        }
        printf("\n");
    }
}