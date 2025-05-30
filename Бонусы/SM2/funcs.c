#include "headers.h"


char *getWord(FILE *input) {
    int size, tell;
    char *word, ch;
    fseek(input, -1, SEEK_CUR);
    tell = ftell(input);
    for (ch = getc(input), size = 0; ch != EOF && ch != '\n' && ch != ' '; size++, ch = getc(input));
    word = malloc((size+1)*sizeof(char));
    fseek(input, tell, SEEK_SET);
    for (int i = 0; i < size; word[i]= getc(input), i++);
    word[size]= '\0';
    return word;
}

int delete_line(FILE *input, FILE *output, char *word) {
    size_t i = 0, row;

    char *line, ch;
    double buff;

    while (1) {
        ch = getc(input);

        if (ch == EOF) {
            return 0;
        }
        if (ch == '\n') {
            break;
        } 
        
        if (ch == ' ') {
            continue;
        }
        i++;


        line = getWord(input);

        if (strcmp(line, word) == 0) {
            free(line);
            break;
            row = i;
        }
        else {
            fprintf(output, "%s ", line);
            free(line);
        }
    } fprintf(output, "\n");

    fscanf(input, "%lf", &buff);
    for (int k = 0; ; k++, fscanf(input, "%lf", &buff)) {
        if (k == i) {
            k = 0;
            fprintf(output, "\n");
        }

        if (k == row-1) {}
            fprintf(output, "%lf ", buff);
    }





}