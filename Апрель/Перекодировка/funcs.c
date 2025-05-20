#include "headers.h"


int delLine(FILE *input, FILE *output) {
    char ch, chPrev;
    int i = 0;

    chPrev = fgetc(input);
    if (chPrev == EOF) {
        return 0;
    }

    putc(chPrev, output);
    for (ch = fgetc(input); ch != EOF; chPrev = ch, ch = fgetc(input)) {
        if (ch == '\n' && chPrev == '\n') {
            continue;
        } 

        if (ch == chPrev && i) {
            putc(ch, output);
            i = 1;
        } else if (ch == chPrev) {
            continue;
        } else {
            putc(ch, output);
            i = 0;
        }
    }

    return 0;
}