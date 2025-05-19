#include "headers.h"


int isZero(Matrix matrix, double eps) {
    for (unsigned i = 0; i < matrix.rows; i++) {
        for (unsigned j = 0; j < matrix.cols; j++) {
            if (fabs(matrix.matrix[i][j]) > eps) {
                return 0;
            }
        }
    }
    return 1;
}


double *evalSelf(Matrix matrix) {
    double *minax = (double*)malloc(sizeof(double) * 2);
    double sum;
    for (unsigned i = 0; i < matrix.rows; i++) {
         sum = 0;
         for (unsigned j = 0; j < matrix.cols; j++) {
            sum += fabs(matrix.matrix[i][j]);
         }
         sum -= fabs(matrix.matrix[i][i]);
 
         if (sum + matrix.matrix[i][i] > minax[1]) {
            minax[1] = sum + matrix.matrix[i][i];
         }
         if (matrix.matrix[i][i] - sum < minax[0]) {
            minax[0] = matrix.matrix[i][i] - sum;
         }
     }
     return minax;
 }


 double *IsiItRoots(double **A, unsigned n, double *B, double eps) {
    Matrix matrix = {A, n, n, {0, 1, 1}};
    Matrix freeTerms = createCol(n, B);
    Matrix diff1 = createCol(n, NULL), diff2 = createCol(n, NULL);
    double **diffm;

    if (findMatRank(matrix.matrix, matrix.rows, matrix.cols, &matrix.acts) != n) {
        return NULL;
    }

    double *ans;

    double *minax;
    
    double coff;


    Matrix x1 = {NULL, 0, 0, {0, 1, 1}};
    Matrix x2 = {NULL, 0, 0, {0, 1, 1}};

    

    minax = evalSelf(matrix);

    coff = 2 / (minax[1] + minax[0]);

    if (minax[0] < 0) {return NULL;}

    x1 = createCol(n, B);
    x2 = createCol(n, B);

    

    do {

        copyMatrix(x2, &x1);

        multMatrix(matrix.matrix, matrix.rows, matrix.cols, x1.matrix, x1.rows, x1.cols, &diff2);
        subMatrix(diff2.matrix, diff2.rows, diff2.cols, freeTerms.matrix, freeTerms.rows, freeTerms.cols, &diff1);

        multiplyMatrix(diff1.matrix, diff1.rows, diff1.cols, coff, &diff1.acts);

        subMatrix(x1.matrix, x1.rows, x1.cols, diff1.matrix, diff1.rows, diff1.cols, &x2);

        multiplyMatrix(diff1.matrix, diff1.rows, diff1.cols, 1/coff, &diff1.acts);

    } while (isZero(diff1, eps) == 0);

    ans = (double*)malloc(sizeof(double) * n);
    for (unsigned i = 0; i < n; i++) {
        ans[i] = x2.matrix[i][0];
    }
    freeSMatrix(diff1);
    freeSMatrix(diff2);
    freeSMatrix(freeTerms);
    freeSMatrix(x1);
    freeSMatrix(x2);
    free(minax);
    return ans;
}

