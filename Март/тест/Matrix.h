#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define E(n)  EMatrix(n)
#define EPS 1e-14


/// Function to generate a random double
static inline double randab(unsigned max) {return pow(-1, rand()%2)*((double)(rand() % max)) + (1/(rand()+1));}


/// Struct to account operations
typedef struct {
    unsigned swaps;
    double mults;
    double norm;
} MatActs;

/// Struct to represent matrix operations
typedef struct FulActs FulActs;

/// Struct to represent a matrix
typedef struct {
    double **matrix;
    unsigned rows;
    unsigned cols;
    MatActs acts;
} Matrix;


/// Function to create a matrix
double **createMatrix(int n, int m);

/// Function to create an identity matrix of size n
Matrix EMatrix(unsigned n);

/// Function to create a row matrix with a given elements
Matrix createRow(unsigned n, double *dub);

/// Function to create a column matrix with a given elements
Matrix createCol(unsigned n, double *dub);

/// Function to read a matrix from a file
Matrix readMatrix(FILE *file);

/// Function to copy a matrix
Matrix copyMatrix(Matrix matrix);


/// Function to free a matrix
int freeMatrix(double **matrix, unsigned n, unsigned m);

static inline int freeSMatrix(Matrix matrix) {return freeMatrix(matrix.matrix, matrix.rows, matrix.cols);}


/// Function to swap two rows of a matrix
void swapRows(double** A, unsigned n, unsigned m,MatActs *acts);

/// Function to multiply a row by a factor
void multiplyRow(double **A, unsigned row, double factor, int m, MatActs *acts); 

/// Function to multiply a matrix by a factor
void multiplyMatrix(double **A, unsigned n, unsigned m, double factor, MatActs *acts);

/// Function to add rows with a factor by number of rows
void addRows(double **matrix, unsigned cols, double factor, unsigned in, unsigned out);


/// Function to multiply two matrices
Matrix multMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm);

Matrix addMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm);

Matrix subMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm);


/// Funcsions to reduce the margin of error
int _findRowMax(double **A, int n, int m, int row);

int _findRowAntiMax(double **A, int n, int m, int row);

/// Function to normalize the matrix
void normiseMatrix(double **A, unsigned n, unsigned m, MatActs *acts);



/// Function to perform Gaussian elimination and count operations
MatActs rungByGauss(double **A, int n, int m);

/// Function to bring the matrix to the lower triangular form
MatActs rungByantiGauss(double **A, int n, int m);

/// Function to calculate the determinant of a matrix
long double findMatDet(double **A, unsigned n, MatActs *acts);

/// Funcsion to find the rank of a matrix
int findMatRank(double **A, unsigned n, unsigned m, MatActs *acts);

/// Function to solve a system of linear equations
int sloveSLE(double **A, double *B, unsigned n, double *x);

Matrix findInv(double **A, unsigned n, MatActs *acts);



/// Function to view the matrix
void drawMatrix(double **A, unsigned n, unsigned m, FILE *output);
