#include "headers.h"

int main(void) {
    FILE *output = fopen("output.txt", "w");
    Node *points = findPoints(func, -4.0, 4.0, -1.0, 0.0);
    if (!output) {
        perror("output.txt");
        return 1;
    }
    insertRectanglePoints(&points, -4.0, 4.0, -1.0, 0.0, 0.01, 0.01);

    printf("%lf\n", findLength(points));
    printf("%lf\n", findArea(points));

    for (Node *cur = points; cur; cur = cur->next)
        fprintf(output, "%.20f %.20f\n", cur->x, cur->y);
    fclose(output);
    freePoints(points);
    return 0;
}