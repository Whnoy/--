#ifndef HNF_H
#define HNF_H

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
    double x, y;
    struct Node *next;
} Node;

double cyrcle(double x, double y);
double flower(double x, double y);

void find_initial_point(double (*func)(double, double), double *x0, double *y0);

Node *findPoints(double (*func)(double, double), double x, double y);

double findLength(Node *head);
double findArea(Node *head);

#endif // HNF_H