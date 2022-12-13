#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "forest.h"

// Verifica se os argumentos de entrada estão corretos
void checkInputArgs(int argc) {
	if (argc < 2) {
		printf("- To run this file you need to execute as following:\n");
		printf("-    ./exe <test_name> <test_number> [flag_for_verbose_output]\n");
		printf("-    verbose flag is 'v'\n\n");
		exit(EXIT_FAILURE);
	}
	if (argc < 3) {
		printf("It needs the file's name and the test number.\n");
		exit(EXIT_FAILURE);
	}
    return;
}

// Lida com as informações do arquivo de entrada
void handleFile(FILE* fp) {
    char * line = NULL;
    size_t len = 0;
    ssize_t read;


    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }

    if (line) free(line);
    return;
}


int main(int argc, char * argv[])
{
    // Verifica se os argumentos de entrada estão corretos
    checkInputArgs(argc);

    // Verifica se os prints serão quiet ou verbosos
	char flag_output = 'q';
	if (argc == 4) flag_output = 'v';


    // Lê o arquivo de entrada e Verifica se o arquivo de entrada existe
    FILE * arquivo_entrada;
    arquivo_entrada = fopen("test1.txt", "r");
	if (arquivo_entrada == NULL) {
		perror("Error while opening the file of arquivo_entrada.\n");
		exit(EXIT_FAILURE);
	}

    // Lida com as informações do arquivo de entrada
    handleFile(arquivo_entrada);

    fclose(arquivo_entrada);
    exit(EXIT_SUCCESS);
}
