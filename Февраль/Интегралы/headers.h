#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


double linear(double x);

double quadratic(double x);

double cubic(double x);

double hyperbolic(double x);

double constant(double x);


int comp(const double a);


//Метод прямоугольников
unsigned slov1(double (*func)(double x), double a, double b, double eps, double *ans);

//Метод трапеций
unsigned slov2(double (*func)(double x), double a, double b, double eps, double *ans);

//Метод Симпсона
unsigned slov3(double (*func)(double x), double a, double b, double eps, double *ans);

//Метод Гаусса
unsigned slov4(double (*func)(double x), double a, double b, double eps, double *ans);
