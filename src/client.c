#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "forest.h"

void handleFile(FILE* fp) {
    char * line = NULL;
    size_t len = 0;
    ssize_t read;


    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    if (line) free(line);
}


int main(int argc, char * argv[])
{
    FILE * fp;
    fp = fopen("test1.txt", "r");
    if (fp == NULL) exit(EXIT_FAILURE);

    handleFile(fp);

    fclose(fp);
    exit(EXIT_SUCCESS);
}
