#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// Lagrange interpolation function
double *Lagrange(double *pointsKn, size_t n, double *pointsUnk, size_t m);

// Linear interpolation function
double *linear(double *pointsKn, size_t n, double *pointsUnk, size_t m);

//Hermite interpolation function
double *Hermite(double *pointsKn, size_t n, double *pointsUnk, size_t m);

// Quadratic interpolation function
double *Quadratic(double *pointsKn, size_t n, double *pointsUnk, size_t m);

