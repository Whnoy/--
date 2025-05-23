#include "testSLE.h"


int main(void) {
    FILE *output;
    char filename[20];
    for(int i = 0; i < 20; i++) {
        filename[i] = '\0';
    }

    printf("Choose output: (std or filename)\n");
    scanf("%s", filename);
    if (filename[0] == 's' && filename[1] == 't' && filename[2] == 'd' && filename[3] == 0) {
        output = stdout;
    } else {
        output = fopen(filename, "w");
        if (output == NULL) {
            printf("Error opening file\n");
            return 1;
        }
    }
    
    fprintf(output, "\npre-defined test:\n");
    testRand(output);

    
    if (output != stdout) {
        fclose(output);
    }
    return 0;
}