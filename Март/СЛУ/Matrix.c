#include "Matrix.h"


double **createMatrix(int n, int m) {
    double **matrix = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
    }
    return matrix;
}

Matrix EMatrix(unsigned n) {
    Matrix matrix = {createMatrix(n, n), n, n, {0, 1, 1}};
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (i == j) {
                matrix.matrix[i][j] = 1;
            } else {
                matrix.matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

Matrix createRow(unsigned n, double *dub) {
    Matrix matrix = {createMatrix(1, n), 1, n, {0, 1, 1}};
    for (unsigned i = 0; i < n; i++) {
        matrix.matrix[0][i] = dub[i];
    }
    return matrix;
}

Matrix createCol(unsigned n, double *dub) {
    Matrix matrix = {createMatrix(n, 1), n, 1, {0, 1, 1}};
    for (unsigned i = 0; i < n; i++) {
        matrix.matrix[i][0] = dub[i];
    }
    return matrix;
}

Matrix readMatrix(FILE *file) {
    char ch;
    int i = 0;
    double b;

    if (file == NULL) {
        return (Matrix){NULL, 0, 0, {0, 1, 1}};
    }

    int n=1, m=1;
    for (m = 1; fscanf(file, "%lf", &b) == 1; m++) {
        ch = getc(file);
        if (ch == '\n') {
            break;
        }
    }

    for (;;) {
        ch = getc(file);
        if (ch == EOF) {
            if (i == 1) {
            n++;
            }
            
            break;
        }
        if (ch != '\n') {
            i = 1;
        }
        if (ch == '\n' && i == 0) {
            break;
        }
        if (ch == '\n' && i == 1) {
            n++;
            i = 0;
        }
        
        
    }
    
    rewind(file);


    Matrix matrix = {createMatrix(n, m), n, m, {0, 1, 1}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%lf", &matrix.matrix[i][j]);
        }
    }
    return matrix;
}

Matrix copyMatrix(Matrix matrix) {
    Matrix newMatrix = {createMatrix(matrix.rows, matrix.cols), matrix.rows, matrix.cols, matrix.acts};
    for (unsigned i = 0; i < matrix.rows; i++) {
        for (unsigned j = 0; j < matrix.cols; j++) {
            newMatrix.matrix[i][j] = matrix.matrix[i][j];
        }
    }
    return newMatrix;
}


int freeMatrix(double **matrix, unsigned n, unsigned m) {
    if (matrix == NULL) {
        return 0;
    }
    for (unsigned i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 1;
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


Matrix multMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm) {
    if (am != bn) {
        return (Matrix){NULL, 0, 0, {0, 1, 1}};
    }
    Matrix C = {createMatrix(an, bm), an, bm, {0, 1, 1}};
    for (unsigned i = 0; i < an; i++) {
        for (unsigned j = 0; j < bm; j++) {
            C.matrix[i][j] = 0;
            for (unsigned k = 0; k < am; k++) {
                C.matrix[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix addMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm) {
    if (an != bn || am != bm) {
        return (Matrix){NULL, 0, 0, {0, 1, 1}};
    }
    Matrix C = {createMatrix(an, am), an, am, {0, 1, 1}};
    for (unsigned i = 0; i < an; i++) {
        for (unsigned j = 0; j < am; j++) {
            C.matrix[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix subMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm) {
    if (an != bn || am != bm) {
        return (Matrix){NULL, 0, 0, {0, 1, 1}};
    }
    Matrix C = {createMatrix(an, am), an, am, {0, 1, 1}};
    for (unsigned i = 0; i < an; i++) {
        for (unsigned j = 0; j < am; j++) {
            C.matrix[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
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

int _findRowAntiMax(double **A, int n, int m, int row) {
    double max = fabs(A[m][row]);
    int maxRow = m;
    for (int i = m-1; i >= 0; i--) {
        if (fabs(A[i][row]) > max) {
            max = fabs(A[i][row]);
            maxRow = i;
        }
    }
    return maxRow;
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

MatActs rungByantiGauss(double **A, int n, int m) {
    MatActs acts = {0, 1, 1};
    for (int i = n-1; i >=0; i--) {

        if (fabs(A[i][i]) > 0) {
            multiplyRow(A, i, -1, m, &acts);
        }

        // Проверить, что ведущий элемент не равен нулю
        if (fabs(A[i][i]) < n*1e-14) {
            continue;
        }

        // Обнулить элементы ниже ведущего
        for (int j = i - 1; j >= 0; j--) {
            if (fabs(A[j][i]) < n*1e-15) { continue; }
            double factor = A[j][i] / A[i][i];
            addRows(A, m, -factor, j, i); // Используем -factor для вычитания
        }
    }
    return acts;
}


void drawMatrix(double **A, unsigned n, unsigned m, FILE *output) {
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < m; j++) {
            fprintf(output, "%lf ", A[i][j]);
        }
        fprintf(output, "\n");
    }
}

