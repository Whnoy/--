#include "headers.h"
#include <math.h>

#define EPS 1e-15

// Функция для вычисления гармонического среднего абсолютных значений строки
double harmonic_mean(const double* row, int m) {
    double sum;
    int has_zero;
    int i;
    sum = 0.0;
    has_zero = 0;
    for (i = 0; i < m; ++i) {
        double val = fabs(row[i]);
        if (val < EPS) {
            has_zero = 1;
            break;
        }
        sum += 1.0 / val;
    }
    if (has_zero) return 0.0;
    return m / sum;
}

// Меняет местами две строки матрицы
void swap_rows(double* a, double* b, int m) {
    int i;
    for (i = 0; i < m; ++i) {
        double tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

// Основная функция решения задачи
int solve() {
    FILE* fin;
    int n, m, i, j, k;
    double** A;
    double* b;
    double* c;
    FILE* fout;

    fin = fopen("input.txt", "r");
    if (!fin) return -1;

    if (fscanf(fin, "%d%d", &n, &m) != 2 || n <= 0 || m <= 0) {
        fclose(fin);
        return -1;
    }

    A = (double**)malloc(n * sizeof(double*));
    if (!A) {
        fclose(fin);
        return -1;
    }
    for (i = 0; i < n; ++i) {
        A[i] = (double*)malloc(m * sizeof(double));
        if (!A[i]) {
            for (k = 0; k < i; ++k) free(A[k]);
            free(A);
            fclose(fin);
            return -1;
        }
        for (j = 0; j < m; ++j) {
            if (fscanf(fin, "%lf", &A[i][j]) != 1) {
                for (k = 0; k <= i; ++k) free(A[k]);
                free(A);
                fclose(fin);
                return -1;
            }
        }
    }
    fclose(fin);

    // Сортировка строк по невозрастанию веса
    for (i = 0; i < n - 1; ++i) {
        int max_idx = i;
        double max_weight = harmonic_mean(A[i], m);
        for (j = i + 1; j < n; ++j) {
            double w = harmonic_mean(A[j], m);
            if (w > max_weight) {
                max_weight = w;
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap_rows(A[i], A[max_idx], m);
        }
    }

    // Получаем транспонированную последнюю строку (вектор-столбец)
    b = (double*)malloc(m * sizeof(double));
    if (!b) {
        for (i = 0; i < n; ++i) free(A[i]);
        free(A);
        return -1;
    }
    for (i = 0; i < m; ++i) b[i] = A[n-1][i];

    // Вычисляем c = A * b
    c = (double*)malloc(n * sizeof(double));
    if (!c) {
        free(b);
        for (i = 0; i < n; ++i) free(A[i]);
        free(A);
        return -1;
    }
    for (i = 0; i < n; ++i) {
        c[i] = 0.0;
        for (j = 0; j < m; ++j) {
            c[i] += A[i][j] * b[j];
        }
    }

    // Запись результата
    fout = fopen("output.txt", "w");
    if (!fout) {
        free(c); free(b);
        for (i = 0; i < n; ++i) free(A[i]);
        free(A);
        return -1;
    }
    fprintf(fout, "%d %d\n", n, m);
    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            fprintf(fout, "%.10g%c", A[i][j], (j == m-1) ? '\n' : ' ');
        }
    }
    fprintf(fout, "\n");
    for (i = 0; i < n; ++i) {
        fprintf(fout, "%.10g%c", c[i], (i == n-1) ? '\n' : ' ');
    }
    fclose(fout);

    free(c); free(b);
    for (i = 0; i < n; ++i) free(A[i]);
    free(A);

    return 0;
}