#include "headers.h"


double *Lagrange(double *pointsKn, size_t n, double *pointsUnk, size_t m) {
    double *x, *y;
    double dif;

    for (size_t i = 0; i < m; i += 2) {
        x = &pointsUnk[i];
        y = &pointsUnk[i+1];
        for (size_t j = 0; j < n; j += 2){
            if (fabs(pointsKn[j] - pointsUnk[i]) < 1E-10) {
                pointsUnk[i+1] = pointsKn[j+1];
            }
        }

        for (size_t j1 = 0; j1 < n; j1 += 2) {
            if (*x > pointsKn[n-2] || *x < pointsKn[0]) {
                return NULL;
            }
            dif = pointsKn[j1+1];
            for (size_t j2 = 0; j2 < n; j2 += 2) {
                if (j1 == j2 || fabs(pointsKn[j1] - pointsKn[j2]) < 1e-12) {continue;}
                dif *= (*x - pointsKn[j2]) / (pointsKn[j1] - pointsKn[j2]);
            }
            *y += dif;
        }
    }

    return pointsUnk;
}


double *linear(double *pointsKn, size_t n, double *pointsUnk, size_t m) {
    double *x, *y;
    double dif;

    for (size_t i = 0; i < m; i += 2) {
        x = &pointsUnk[i];
        y = &pointsUnk[i+1];
        for (size_t j = 0; j < n; j += 2){
            if (fabs(pointsKn[j] - pointsUnk[i]) < 1E-10) {
                pointsUnk[i+1] = pointsKn[j+1];
                goto cycle;
            }
        }
        
        for (size_t j1 = 0, j2 = 2; j2 < n; j1 += 2, j2 += 2) {
            if (*x > pointsKn[j1] && *x < pointsKn[j2]) {
                dif = (pointsKn[j2+1] - pointsKn[j1+1]) / (pointsKn[j2] - pointsKn[j1]);
                *y = pointsKn[j1+1] + dif * (*x - pointsKn[j1]);
                goto cycle;
            }
        }
        return NULL;

        cycle:
        continue;
    }
        return pointsUnk;
}

double *Hermite(double *pointsKn, size_t n, double *pointsUnk, size_t m) {
    double *x, *y;
    double dif;

    for (size_t i = 0; i < m; i += 2) {
        x = &pointsUnk[i];
        y = &pointsUnk[i+1];
        for (size_t j = 0; j < n; j += 2){
            if (fabs(pointsKn[j] - pointsUnk[i]) < 1E-10) {
                pointsUnk[i+1] = pointsKn[j+1];
            }
        }

        for (size_t j1 = 0; j1 < n; j1 += 2) {
            if (*x > pointsKn[n-2] || *x < pointsKn[0]) {
                return NULL;
            }
            dif = pointsKn[j1+1];
            for (size_t j2 = 0; j2 < n; j2 += 2) {
                if (j1 == j2 || fabs(pointsKn[j1] - pointsKn[j2]) < 1e-12) {continue;}
                dif *= (*x - pointsKn[j2]) / (pointsKn[j1] - pointsKn[j2]);
            }
            *y += dif;
        }
    }

    return pointsUnk;
}

double *Quadratic(double *pointsKn, size_t n, double *pointsUnk, size_t m) {
    double *x, *y;
    double dif;

    for (size_t i = 0; i < m; i += 2) {
        x = &pointsUnk[i];
        y = &pointsUnk[i+1];
        for (size_t j = 0; j < n; j += 2){
            if (pointsKn[j] == pointsUnk[i]) {
                pointsUnk[i+1] = pointsKn[j+1];
            }
        }

        for (size_t j1 = 0; j1 < n; j1 += 2) {
            if (*x > pointsKn[n-2] || *x < pointsKn[0]) {
                return NULL;
            }
            dif = pointsKn[j1+1];
            for (size_t j2 = 0; j2 < n; j2 += 2) {
                if (j1 == j2 || fabs(pointsKn[j1] - pointsKn[j2]) < 1e-12) {continue;}
                dif *= (*x - pointsKn[j2]) / (pointsKn[j1] - pointsKn[j2]);
            }
            *y += dif;
        }
    }

    return pointsUnk;
}
