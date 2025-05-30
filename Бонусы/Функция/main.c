#include "headers.h"

int main() {
    FILE *output = fopen("output.txt", "w");
    Node *points = findPoints(flower, 0, 1);
    double a = findArea(points), l = findLength(points);

    printf("Area:\t %.10f %e\n", a, fabs(a - M_PI));
    printf("Length:\t %.10f %e\n", l, fabs(l - (2 * M_PI)));
    
    double max_jump = 0.0;
    for (Node *current = points; current->next != NULL; current = current->next) {
        double dx = current->next->x - current->x;
        double dy = current->next->y - current->y;
        double d = sqrt(dx*dx + dy*dy);
        if (d > max_jump) max_jump = d;
    }
    printf("Max jump between points: %.3e\n", max_jump);

    for (Node *current = points, *buff = points; current != NULL; current = current->next, free(buff), buff = current) {
        fprintf(output,"%f %f\n", current->x, current->y);
    }
    fclose(output);
    return 0;
}