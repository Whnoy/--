#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double x, y;
    struct Node *next;
} Node;

double func(double x, double y);
Node *findPoints(double (*func)(double, double), double xmin, double xmax, double ymin, double ymax);
void freePoints(Node *head);

void insertRectanglePoints(Node **head, double xmin, double xmax, double ymin, double ymax, double step, double threshold);

double findLength(Node *head);
double findArea(Node *head);