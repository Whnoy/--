#include <math.h>
#include <stdio.h>
#include <stdlib.h>


//Метод деления пополам
int slov1(double (*func)(double x), double a, double b, double eps, double *ans);

//Метод Ньютона
int slov2(double (*func)(double x), double a, double b, double eps, double *ans);

//Метод секущих
int slov3(double (*func)(double x), double a, double b, double eps, double *ans);

