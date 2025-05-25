#ifndef HEADERS_H
#define HEADERS_H

#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

double findQ(Matrix A);
int isTTS(Matrix A, double eps);
double *findMinMax(Matrix A);
double *sloveSimle(Matrix A, double *fr, double eps);
double *sloveFast(Matrix A, double *fr, double eps);

// Новые функции из test.c
Matrix generateMatrix(int n, int m);
double compareX(double *x, unsigned n);
double compareRes(double **A, double *x, double *B, unsigned n);
int test(double *func(Matrix, double *, double));
double *sloveYeban(Matrix A, double *fr, double eps);

#endif // HEADERS_H