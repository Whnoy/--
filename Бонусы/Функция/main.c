#include "headers.h"

int main() {
    FILE *output;
    Node *points;
    double a, l, x0 = NAN, y0 = NAN;
    double max_jump = 0, dx, dy, d;

    output = fopen("output.txt", "w");

    if (!output) {
        fprintf(stderr, "Error opening output file.\n");
        return EXIT_FAILURE;
    }

    points = findPoints(example, x0, y0);

    a = findArea(points);
    l = findLength(points);

    printf("Area:\t %.10f %e\n", a, fabs(a - M_PI));
    printf("Length:\t %.10f %e\n", l, fabs(l - (2 * M_PI)));
    
    max_jump = 0.0;
    for (Node *current = points; current->next != NULL; current = current->next) {
        dx = current->next->x - current->x;
        dy = current->next->y - current->y;
        d = sqrt(dx*dx + dy*dy);
        if (d > max_jump) max_jump = d;
    }
    printf("Max jump between points: %.3e\n", max_jump);

    for (Node *current = points, *buff = points; current != NULL; current = current->next, free(buff), buff = current) {
        fprintf(output,"%f %f\n", current->x, current->y);
    }
    fclose(output);
    return 0;
}