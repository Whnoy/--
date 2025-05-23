#include "Matrix.h"


long double findMatDet(double **A, unsigned n, MatActs *acts) {
    long double det = 1;
    MatActs tmp = rungByGauss(A, n, n);
    (*acts).mults *= tmp.mults;
    (*acts).swaps += tmp.swaps;
    
    for (int i = 0; i < n; i++) {
        det *= A[i][i];
    }
    det *= pow(-1, (*acts).swaps);
    det /= (*acts).mults;
    det /= (*acts).norm;
    return det;
}

int findMatRank(double **A, unsigned n, unsigned m, MatActs *acts) {
    MatActs tmp = rungByGauss(A, n, m);
    (*acts).mults *= tmp.mults;
    (*acts).swaps += tmp.swaps;
    (*acts).norm *= tmp.norm;

    int rank = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) > n*1e-15) {
            rank++;
         }
        
    }

    return rank;
}

int sloveSLE(double **A, double *B, unsigned n, double *x) {
    Matrix matrix = {createMatrix(n, n+1), n, n+1, (MatActs){0, 1, 1}};
    

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            matrix.matrix[i][j] = A[i][j];
        }
        matrix.matrix[i][n] = B[i];
    }
    normiseMatrix(matrix.matrix, n, n+1, &matrix.acts);



    if (findMatRank(matrix.matrix, n, n+1, &matrix.acts) != findMatRank(matrix.matrix, n, n, &matrix.acts)) {return -1;}
    if (findMatRank(matrix.matrix, n, n, &matrix.acts) != n) {return 0;}

    for (int i = n-1; i >= 0; i--) {
        x[i] = matrix.matrix[i][n];
        for (unsigned j = i+1; j < n; j++) {
            x[i] -= matrix.matrix[i][j] * x[j];
        }
        x[i] /= matrix.matrix[i][i];
    }

    for (unsigned i = 0; i < n; i++) {
        free(matrix.matrix[i]);
    }
    free(matrix.matrix);

    return 1;
}


Matrix findInv(double **A, unsigned n, MatActs *acts) {
    Matrix matrix = {createMatrix(n, 2*n), n, 2*n, (MatActs){0, 1, 1}};
    double norm;
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            matrix.matrix[i][j] = A[i][j];
        }
        matrix.matrix[i][i+n] = 1;
    }

    //norm = normiseMatrix(matrix.matrix, n, 2*n, &matrix.acts);
    if (findMatRank(A, n, n, acts) != n) {
        for (unsigned i = 0; i < n; i++) {
            free(matrix.matrix[i]);
        }
        free(matrix.matrix);
        return (Matrix){NULL, 0, 0, {0, 0, 0}};
    }
    
    rungByGauss(matrix.matrix, n, 2*n);
    rungByantiGauss(matrix.matrix, n, 2*n);

    //multiplyMatrix(matrix.matrix, n, 2*n, norm, &matrix.acts);

    for (unsigned i = 0; i < n; i++) {
        multiplyRow(matrix.matrix, i, 1/matrix.matrix[i][i], 2*n, &matrix.acts);
    }

    Matrix mat = {createMatrix(n, n), n, n, (MatActs){0, 1, 1}};
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            mat.matrix[i][j] = matrix.matrix[i][j+n];
        }
    }

    return mat;
    
    

}
    
