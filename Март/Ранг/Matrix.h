#include <math.h>
#include <stdio.h>
#include <stdlib.h>


//Struct to account operations
typedef struct {
    unsigned swaps;
    double mults;
    double norm;
} MatActs;

//Struct to represent a matrix
typedef struct {
    double **matrix;
    unsigned rows;
    unsigned cols;
    MatActs acts;
} Matrix;

//Function to create a matrix
double **createMatrix(int n, int m);

int _findRowMax(double **A, int n, int m, int row);

void swapRows(double** A, unsigned n, unsigned m,MatActs *acts);

void multiplyRow(double **A, unsigned row, double factor, int m, MatActs *acts); 

void multiplyMatrix(double **A, unsigned n, unsigned m, double factor, MatActs *acts);

/// Function to add rows with a factor by number of rows
void addRows(double **matrix, unsigned cols, double factor, unsigned in, unsigned out);

/// Function to perform Gaussian elimination and count operations
MatActs rungByGauss(double **A, int n, int m);

void normiseMatrix(double **A, unsigned n, unsigned m, MatActs *acts);

void drawMatrix(double **A, unsigned n, unsigned m);

