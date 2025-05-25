#include "headers.h"

double findQ(Matrix A) {
    double sum = 0;

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            sum += A.matrix[i][j]*A.matrix[i][j];
        }
    }
    sum /= A.rows;
    sum = sqrt(sum);

    return sum;
}

int isTTS(Matrix A, double eps) {
    double sum = 0;

    for (int i = 0; i < A.rows; i++) {
        sum += A.matrix[i][0] * A.matrix[i][0];
    }
    if (sqrt(sum) < eps) {
        return 1;
    }
    return 0;
}

double *findMinMax(Matrix A) {
    double *minax = (double *)malloc(2 * sizeof(double));

    double sum = 0;

    int n = 0;
    
    minax[0] = 0; // min
    minax[1] = 0; // max

    if (minax == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            sum += fabs(A.matrix[i][j]);
        }
        sum -= fabs(A.matrix[i][i]);
        if (n == 0) {
            minax[0] = A.matrix[i][i] - sum;
            minax[1] = A.matrix[i][i] + sum;
            n = 1;
        }
        if (A.matrix[i][i] - sum < minax[0]) {
            minax[0] = A.matrix[i][i] - sum;
        }
        if (A.matrix[i][i] + sum > minax[1]) {
            minax[1] = A.matrix[i][i] + sum;
        }
        sum = 0;
    }

    return minax; 
}

double scalcMult(Matrix A, Matrix B) {
    double sum = 0;

    if (A.cols != 1 || B.cols != 1) return nan("");

    for (int i = 0; i < A.rows; i++) {
        sum += A.matrix[i][0] * B.matrix[i][0];
    }

    return sum;
}


//Метод простой итерации
double *sloveSimle(Matrix A, double *fr, double eps) {
    int i = 0;
    int n = A.rows;
    Matrix B;
    Matrix X1;
    Matrix X2;

    Matrix Y;
    Matrix Z;
    Matrix id;

    double *minax = findMinMax(A); 
    double diff = 0;

    double *ans;

    if (minax[0] < 0) {
        return NULL;
    }

    if (fabs(minax[0] + minax[1]) < eps) {
        return NULL;
    }

    diff = 2/ (minax[1] + minax[0]);

    Z = createCol(n, NULL);
    Y = createCol(n, NULL);
    X2 = createCol(n, NULL);
    X1 = createCol(n, NULL);
    id = createCol(n, NULL);
    B = createCol(n, fr);
    ans = (double *)malloc(n * sizeof(double));

    int br;


    for (int i = 0; i < n; i++) {
        X1.matrix[i][0] = 0; 
        X2.matrix[i][0] = 0;
        Y.matrix[i][0] = 0;
        Z.matrix[i][0] = 0;
        id.matrix[i][0] = 1;
    }

    do {
        multMatrix(A.matrix, n, n, X1.matrix, n, 1, &Y);
        subMatrix(Y.matrix, n, 1, B.matrix, n, 1, &Z);
        
        br = isTTS(Z, eps);

        multiplyMatrix(Z.matrix, n, 1, diff, &(Z.acts));

        subMatrix(X1.matrix, n, 1, Z.matrix, n, 1, &X2);

        subMatrix(X2.matrix, n, 1, id.matrix, n, 1, &Z);
        subMatrix(X1.matrix, n, 1, id.matrix, n, 1, &Y);


        copyMatrix(X2, &X1);


    } while (br == 0);


    for (int i = 0; i < n; i++) {
        ans[i] = X1.matrix[i][0];
    }

    freeSMatrix(B);
    freeSMatrix(X1);
    freeSMatrix(X2);
    freeSMatrix(Y);
    freeSMatrix(Z);
    free(minax);

    return ans;
}

// Метод скорейшего спуска
double *sloveFast(Matrix A, double *fr, double eps) {
    int i = 0;
    int n = A.rows;
    Matrix B;
    Matrix X1;
    Matrix X2;

    Matrix Y;
    Matrix Z;
    Matrix id;
    Matrix tmp;

    double *minax = findMinMax(A); 
    double diff = 0;

    double *ans;

    if (minax[0] < 0) {
        return NULL;
    }

    Z = createCol(n, NULL);
    Y = createCol(n, NULL);
    X2 = createCol(n, NULL);
    X1 = createCol(n, NULL);
    id = createCol(n, NULL);
    B = createCol(n, fr);
    tmp = createCol(n, NULL);
    ans = (double *)malloc(n * sizeof(double));

    int br;


    for (int i = 0; i < n; i++) {
        X1.matrix[i][0] = 0; 
        X2.matrix[i][0] = 0;
        Y.matrix[i][0] = 0;
        Z.matrix[i][0] = 0;
        id.matrix[i][0] = 1;
    }

    do {
        multMatrix(A.matrix, n, n, X1.matrix, n, 1, &Y);
        subMatrix(Y.matrix, n, 1, B.matrix, n, 1, &Z);
        
        br = isTTS(Z, eps);

        multMatrix(A.matrix, n, n, Z.matrix, n, 1, &tmp);

        diff = scalcMult(Z, Z)/scalcMult(tmp, Z);

        multiplyMatrix(Z.matrix, n, 1, diff, &(Z.acts));

        subMatrix(X1.matrix, n, 1, Z.matrix, n, 1, &X2);

        subMatrix(X2.matrix, n, 1, id.matrix, n, 1, &Z);
        subMatrix(X1.matrix, n, 1, id.matrix, n, 1, &Y);

        
        copyMatrix(X2, &X1);


    } while (br == 0);


    for (int i = 0; i < n; i++) {
        ans[i] = X1.matrix[i][0];
    }

    freeSMatrix(B);
    freeSMatrix(X1);
    freeSMatrix(X2);
    freeSMatrix(Y);
    freeSMatrix(Z);
    free(minax);

    return ans;
}

// Метод Зейделя
double *sloveYeban(Matrix A, double *fr, double eps) {
    int n = A.rows;
    double *x = (double *)malloc(n * sizeof(double));
    double *x_prev = (double *)malloc(n * sizeof(double));
    if (!x || !x_prev) return NULL;

    // Начальное приближение
    for (int i = 0; i < n; i++) {
        x[i] = 0;
        x_prev[i] = 0;
    }

    int max_iter = 100000;
    int iter = 0;
    double norm;

    do {
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A.matrix[i][j] * x[j];
                }
            }
            x[i] = (fr[i] - sum) / A.matrix[i][i];
        }

        // Вычисляем норму разности
        norm = 0;
        for (int i = 0; i < n; i++) {
            norm += (x[i] - x_prev[i]) * (x[i] - x_prev[i]);
        }
        norm = sqrt(norm);

        // Копируем x в x_prev для следующей итерации
        for (int i = 0; i < n; i++) {
            x_prev[i] = x[i];
        }

        iter++;
        if (iter > max_iter) {
            free(x);
            free(x_prev);
            return NULL; // не сошлось
        }
    } while (norm > eps);

    free(x_prev);
    return x;
}