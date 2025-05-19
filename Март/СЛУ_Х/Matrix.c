#include "Matrix.h"
#include <stdlib.h>
#include <math.h>

double randab(unsigned max) {
    return (rand() % 2 ? 1 : -1) * ((double)(rand() % max)) + (1.0 / (rand() + 1));
}

double **createMatrix(unsigned n, unsigned m) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    if (!matrix) return NULL;
    for (unsigned i = 0; i < n; i++) {
        matrix[i] = (double *)calloc(m, sizeof(double));
        if (!matrix[i]) {
            for (unsigned j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

int freeMatrix(double **matrix, unsigned n, unsigned m) {
    if (!matrix) return 0;
    for (unsigned i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 1;
}

int freeSMatrix(Matrix matrix) {
    return freeMatrix(matrix.matrix, matrix.rows, matrix.cols);
}

Matrix EMatrix(unsigned n) {
    Matrix matrix = {createMatrix(n, n), n, n, {0, 1, 1}};
    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < n; j++)
            matrix.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    return matrix;
}

Matrix createRow(unsigned n, const double *dub) {
    Matrix matrix = {createMatrix(1, n), 1, n, {0, 1, 1}};
    if (dub)
        for (unsigned i = 0; i < n; i++)
            matrix.matrix[0][i] = dub[i];
    return matrix;
}

Matrix createCol(unsigned n, const double *dub) {
    Matrix matrix = {createMatrix(n, 1), n, 1, {0, 1, 1}};
    if (dub)
        for (unsigned i = 0; i < n; i++)
            matrix.matrix[i][0] = dub[i];
    return matrix;
}

Matrix copyMatrix(const Matrix matrix, Matrix *out) {
    if (!out) out = (Matrix *)malloc(sizeof(Matrix));
    if (out->matrix) freeSMatrix(*out);
    out->matrix = createMatrix(matrix.rows, matrix.cols);
    out->rows = matrix.rows;
    out->cols = matrix.cols;
    out->acts = (MatActs){0, 1, 1};
    for (unsigned i = 0; i < matrix.rows; i++)
        for (unsigned j = 0; j < matrix.cols; j++)
            out->matrix[i][j] = matrix.matrix[i][j];
    return *out;
}

Matrix readMatrix(FILE *file) {
    if (!file) return (Matrix){NULL, 0, 0, {0, 1, 1}};
    unsigned n = 0, m = 0, cols = 0;
    double tmp;
    char line[1024];
    long pos = ftell(file);
    while (fgets(line, sizeof(line), file)) {
        cols = 0;
        char *ptr = line;
        while (sscanf(ptr, "%lf", &tmp) == 1) {
            cols++;
            while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n') ptr++;
            while (*ptr == ' ' || *ptr == '\t') ptr++;
        }
        if (cols > m) m = cols;
        n++;
    }
    fseek(file, pos, SEEK_SET);
    Matrix matrix = {createMatrix(n, m), n, m, {0, 1, 1}};
    for (unsigned i = 0; i < n; i++)
        for (unsigned j = 0; j < m; j++)
            if (fscanf(file, "%lf", &matrix.matrix[i][j]) != 1)
                matrix.matrix[i][j] = 0;
    return matrix;
}

void swapRows(double **A, unsigned n, unsigned m, MatActs *acts) {
    double *temp = A[n];
    A[n] = A[m];
    A[m] = temp;
    acts->swaps++;
}

void multiplyRow(double **A, unsigned row, double factor, unsigned m, MatActs *acts) {
    acts->mults *= factor;
    for (unsigned j = 0; j < m; j++)
        A[row][j] *= factor;
}

void multiplyMatrix(double **A, unsigned n, unsigned m, double factor, MatActs *acts) {
    for (unsigned i = 0; i < n; i++)
        multiplyRow(A, i, factor, m, acts);
}

void addRows(double **matrix, unsigned cols, double factor, unsigned in, unsigned out) {
    for (unsigned j = 0; j < cols; j++)
        matrix[in][j] += matrix[out][j] * factor;
}

Matrix multMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C) {
    if (am != bn) return (Matrix){NULL, 0, 0, {0, 1, 1}};
    if (!C) {
        C = (Matrix *)malloc(sizeof(Matrix));
        C->matrix = createMatrix(an, bm);
        C->rows = an;
        C->cols = bm;
    } else if (!C->matrix || C->rows != an || C->cols != bm) {
        freeSMatrix(*C);
        C->matrix = createMatrix(an, bm);
        C->rows = an;
        C->cols = bm;
    }
    C->acts = (MatActs){0, 1, 1};
    for (unsigned i = 0; i < an; i++)
        for (unsigned j = 0; j < bm; j++) {
            C->matrix[i][j] = 0;
            for (unsigned k = 0; k < am; k++)
                C->matrix[i][j] += A[i][k] * B[k][j];
        }
    return *C;
}

Matrix addMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C) {
    if (an != bn || am != bm) return (Matrix){NULL, 0, 0, {0, 1, 1}};
    if (!C || !C->matrix || C->rows != an || C->cols != am) {
        if (C) freeSMatrix(*C);
        C = (Matrix *)malloc(sizeof(Matrix));
        C->matrix = createMatrix(an, am);
        C->rows = an;
        C->cols = am;
    }
    C->acts = (MatActs){0, 1, 1};
    for (unsigned i = 0; i < an; i++)
        for (unsigned j = 0; j < am; j++)
            C->matrix[i][j] = A[i][j] + B[i][j];
    return *C;
}

Matrix subMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C) {
    if (an != bn || am != bm) return (Matrix){NULL, 0, 0, {0, 1, 1}};
    if (!C || !C->matrix || C->rows != an || C->cols != am) {
        if (C) freeSMatrix(*C);
        C = (Matrix *)malloc(sizeof(Matrix));
        C->matrix = createMatrix(an, am);
        C->rows = an;
        C->cols = am;
    }
    C->acts = (MatActs){0, 1, 1};
    for (unsigned i = 0; i < an; i++)
        for (unsigned j = 0; j < am; j++)
            C->matrix[i][j] = A[i][j] - B[i][j];
    return *C;
}

int _findRowMax(double **A, unsigned n, unsigned m, unsigned row) {
    double max = fabs(A[m][row]);
    unsigned maxRow = m;
    for (unsigned i = m + 1; i < n; i++)
        if (fabs(A[i][row]) > max) {
            max = fabs(A[i][row]);
            maxRow = i;
        }
    return maxRow;
}

int _findRowAntiMax(double **A, unsigned n, unsigned m, unsigned row) {
    double max = fabs(A[m][row]);
    int maxRow = m;
    for (int i = m - 1; i >= 0; i--)
        if (fabs(A[i][row]) > max) {
            max = fabs(A[i][row]);
            maxRow = i;
        }
    return maxRow;
}

void normiseMatrix(double **A, unsigned n, unsigned m, MatActs *acts) {
    double max = 0, maxNew = 0;
    for (unsigned j = 0; j < m; j++)
        max += fabs(A[0][j]);
    for (unsigned i = 1; i < n; i++) {
        for (unsigned j = 0; j < m; j++)
            maxNew += fabs(A[i][j]);
        if (maxNew > max) max = maxNew;
        maxNew = 0;
    }
    multiplyMatrix(A, n, m, 1 / max, acts);
    acts->norm *= max;
    acts->mults *= pow(max, n);
}

MatActs rungByGauss(double **A, unsigned n, unsigned m) {
    MatActs acts = {0, 1, 1};
    for (unsigned i = 0; i < m && i < n; i++) {
        unsigned maxRow = _findRowMax(A, n, i, i);
        if (maxRow != i) swapRows(A, i, maxRow, &acts);
        if (fabs(A[i][i]) > 0) multiplyRow(A, i, -1, m, &acts);
        if (fabs(A[i][i]) < n * EPS) continue;
        for (unsigned j = i + 1; j < n; j++) {
            if (fabs(A[j][i]) < n * EPS) continue;
            double factor = A[j][i] / A[i][i];
            addRows(A, m, -factor, j, i);
        }
    }
    return acts;
}

MatActs rungByantiGauss(double **A, unsigned n, unsigned m) {
    MatActs acts = {0, 1, 1};
    for (int i = n - 1; i >= 0; i--) {
        if (fabs(A[i][i]) > 0) multiplyRow(A, i, -1, m, &acts);
        if (fabs(A[i][i]) < n * EPS) continue;
        for (int j = i - 1; j >= 0; j--) {
            if (fabs(A[j][i]) < n * EPS) continue;
            double factor = A[j][i] / A[i][i];
            addRows(A, m, -factor, j, i);
        }
    }
    return acts;
}

void drawMatrix(const double **A, unsigned n, unsigned m, FILE *output) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++)
            fprintf(output, "%lf ", A[i][j]);
        fprintf(output, "\n");
    }
}

