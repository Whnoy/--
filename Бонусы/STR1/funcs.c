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
int isNum(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] > '9' && word[i] < '0') {return 0;}
    }
    return 1;
}
int isWord(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!(word[i] >= 'A' && word[i] <= 'z')) {return 0;}
    }
    return 1;
}

int count(FILE *input) {
    char ch, *word;
    int sum = 0;
    int i = 0;

    for (ch = getc(input);; ch = getc(input)) {
        if (ch == EOF) break;
        if (ch == ' ' ||  ch == '\n') continue;
        word = getWord(input);
        if (i == 1 && isNum(word)) {
            sum += strtol(word, NULL, 10);
            i = 0;
        }
        else if (isWord(word)) {i = 1;}
        else {i = 0;}
        free(word);
    }

    return sum;
}