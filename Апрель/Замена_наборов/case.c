#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char ch;
    void *next;
} List;


void clearList (List *list) {
    List *p = (List *)list->next;
    List *temp;

    while (p != NULL) {
        temp = p;
        p = (List *)p->next;
        free(temp);
    }
}

List readLine(FILE *file) {
    List list;
    List *buff;

    list.ch = fgetc(file);
    for (buff = &list; buff->ch != EOF && buff->ch != '\n'; buff->next = (List *)malloc(sizeof(List))) {
        buff = (List *)buff->next;
        if (buff->next == NULL) {
            clearList(&list);
            return (List){EOF, NULL};
        }
        getc(file);
    }
    buff->next = NULL;

    return list;
}

int equalLS();