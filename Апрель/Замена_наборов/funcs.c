#include "headers.h"


void shift_left(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = str[i+1];
        i++;
    }
    // '\0' автоматически окажется на месте
}


int swap(char *input_l, char *output_l, Dict *dict, int dict_size) {
    char **line, ch;
    int sum=0;
    int k = 0;
    int max=0;
    long told;
    FILE *input, *output;

    input = fopen(input_l, "r");
    output = fopen(output_l, "w");

    if (input == NULL || output == NULL) {
        return -1;
    }

    for (int i = 0; i < dict_size; i++) {
        if (dict[i].inLen > max) {
            max = dict[i].inLen;
        }
    }

    for (int i = 0; i < dict_size; i++) {
        sum += dict[i].inLen;
        sum += 1;
    }

    line = (char**)malloc(dict_size* sizeof(char*));
    
    for (int i = 0; i < dict_size; i++) {
        line[i] = (char*)malloc((dict[i].inLen + 1) * sizeof(char));
        if (line[i] == NULL) {
            return -1;
        }
    }
    
    for (int i = 0; i < dict_size; i++) {
        line[i][dict[i].inLen] = '\0';
    }
        
    for (int i = 0; i < max; i++) {
        ch = getc(input);
        if (ch == EOF) {
            break;
        }
        for (int j = 0; j < dict_size; j++) {
            if (i < dict[j].inLen) {
                line[j][i] = ch;
            }
        }
    }

    fseek(input, 0, SEEK_SET);
        
    for (; ch != EOF;) {
        
        for (int i = 0; i < dict_size; i++) {
            if (strcmp(line[i], dict[i].in) == 0) {
                fprintf(output, "%s", dict[i].out);
                k = dict[i].inLen;
                break;
            }
        }
        for (int i = 0; i < dict_size; i++) {
            shift_left(line[i]);
            told = ftell(input);
            fseek(input, dict[i].inLen, SEEK_CUR);
            line[i][dict[i].inLen - 1] = fgetc(input);
            fseek(input, told, SEEK_SET);
        }
        ch = fgetc(input);


        if (k == 0) {
            fputc(ch, output);
        } else k--;

        
    }


    for (int i = 0; i < dict_size; i++) {
        free(line[i]);
    }
    free(line);
    fclose(input);
    fclose(output);

    return 0;
        
}
