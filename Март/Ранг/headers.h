#include "Matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ranlib.h>

// Function to generate a random double number
double randomDouble(double max);

//Function to find the rank of a matrix
int findMatRnak(double **A, unsigned n, unsigned m);