#include "Matrix.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


//Генерирует матрицы коеффицентов размера 2^n и
//вектор свободных членов длинны п, такие, что система имеет единственное решение 1, 1, 1...
int testRand(FILE *output);

double compareX(double *x, unsigned n);

double compareRes(double **A, double *x,double *B, unsigned n);