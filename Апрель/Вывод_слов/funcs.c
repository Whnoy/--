#include "headers.h"


int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}


int word_length(FILE *input, char first_char) {
    int length = 0;
    char ch = first_char;
    int tell = ftell(input);

    while (ch != ' ' && ch != '\n' && ch != EOF) {
        length++;
        ch = fgetc(input);
    }

    fseek(input, tell, SEEK_SET);

    return length;
}

void addNode(Node **list, char *ch) {
    Node *newNode = malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
    } else {
        Node *cur = *list;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = newNode;
    }
}

int printW(FILE *input, FILE *output) {
    Node *list = NULL, *buff, *buff2;
    char *str;
    int i = 0, k;
    char **words;
    int wordSize = 0;
    char ch;

    while ((ch = fgetc(input)) != EOF) {
        if (ch != ' ' && ch != '\n') {
            k = word_length(input, ch);
            str = malloc((k + 1) * sizeof(char));
            str[0] = ch;
            for (int j = 1; j < k; j++) {
                str[j] = fgetc(input);
            }
            str[k] = '\0';
            addNode(&list, str);
            wordSize++;
        }
    }

    words = malloc(wordSize * sizeof(char*));
    buff = list;
    for (i = 0; i < wordSize; i++) {
        words[i] = buff->ch;
        buff2 = buff;
        buff = buff->next;
        free(buff2);
    }

    qsort(words, wordSize, sizeof(char*), cmp);
    fprintf(output, "%s\n", words[0]);
    for (int j = 1; j < wordSize; j++) {
        if (strcmp(words[j-1], words[j]) != 0) {
            fprintf(output, "%s\n", words[j]);
        }
        free(words[j-1]);
    }
    free(words[wordSize-1]);
    free(words);

    return 0;
}
