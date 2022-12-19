#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_forest.h"

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

// Executa a operação desejada
void executeOperation(char * first_word, char * second_word, char * third_word, FILE* output_file, char flag_output) {
    int vertice1, vertice2;

    // Verifica qual é a operação desejada pela linha e executa a operação
    if (strcmp(first_word,"+") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        if (flag_output == 'v') printf("Operation addEdge between: %d and %d\n", vertice1, vertice2);

        addEdge(vertice1, vertice2);

    } else if (strcmp(first_word,"-") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        if (flag_output == 'v') printf("Operation removeEdge between: %d and %d\n", vertice1, vertice2);

        deleteEdge(vertice1, vertice2);

    } else if (strcmp(first_word,"c") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        if (flag_output == 'v') printf("Operation connected between: %d and %d\n", vertice1, vertice2);

        if (connected(vertice1, vertice2)) {
            printf("Vertices %d and %d are connected\n", vertice1, vertice2);
            fprintf(output_file, "true\n");
        } else {
            printf("Vertices %d and %d are NOT connected\n", vertice1, vertice2);
            fprintf(output_file, "false\n");
        }
        
    } else {
        perror("Error in handleFile unidentified character. It is not '+', '-' or 'c'.\n");
        exit(EXIT_FAILURE);
    }
    return;
}


// Lida com as informações do arquivo de entrada
void handleFile(FILE* input_file, FILE* output_file, char flag_output) {
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int primeira_linha = 1;
    int j = 0;
    int n_vertices = 0;


    char * first_word = NULL;
    char * second_word = NULL;
    char * third_word = NULL;
    char delim[] = " ";
    char *ptr = NULL;


    // Todas as linhas terão 3 palavras, com exceção da primeira linha que só tem uma palavra
    while ((read = getline(&line, &len, input_file)) != -1) {

        // Depois retiro essas duas próximas linhas
        // printf("Retrieved line of length %zu:\n", read);
        // printf("%s", line);

        // se for a primeira linha do arquivo eu leio o número de vértices
        if (primeira_linha)
        {
            n_vertices =  atoi(line);
            // printf("n: %d\n", n_vertices);
            primeira_linha = 0;

            // Cria a dynamic Forest com n_vertices
            dynamicForest(n_vertices);
        } 
        // caso contrário eu vejo quais são as operações
        else
        {
            j = 0;
            first_word = NULL;
            second_word = NULL;
            third_word = NULL;
            
            // Split string 'line' in words
            ptr = strtok(line, delim);
            while (ptr != NULL)
            {   
                if (j == 0) {
                    first_word = ptr;
                } else if (j == 1) {
                    second_word = ptr;
                } else if (j == 2) {
                    third_word = ptr;
                    
                    //remove a newline do fim da third_word
                    third_word[strlen(third_word)-1] = '\0';
                }
                ptr = strtok(NULL, delim);
                j++;
            }

            // Executa a operação desejada
            executeOperation(first_word, second_word, third_word, output_file, flag_output);
        }
    }

    if (line) free(line);
    return;
}


int main(int argc, char * argv[])
{
    // Verifica se os argumentos de entrada estão corretos
    checkInputArgs(argc);

    // flag for verbose output
	char flag_output = 'q';
	if (argc == 4) flag_output = 'v';

    // Lê o arquivo de entrada e Verifica se o arquivo de entrada existe
    FILE * input_file;
    input_file = fopen(argv[1], "r");
	if (input_file == NULL) {
		perror("Error while opening the file of input_file.\n");
		exit(EXIT_FAILURE);
	}

	// Gera o nome do arquivo do resultado do i-ésimo teste
	FILE * output_file;
	char output_file_name[] = "tests/results/result_test";
    strcat(output_file_name,argv[2]);
    printf("Result test file name: %s\n", output_file_name);

	// Abre o arquivo de saída
	output_file = fopen (output_file_name, "w");

	// Verifica se a criação do arquivo de saída foi bem sucedida
	if (output_file == NULL) {
		perror("Error while opening the file output_file.\n");
		exit(EXIT_FAILURE);
	}

    // Lida com as informações do arquivo de entrada
    handleFile(input_file, output_file, flag_output);

    fclose(input_file);
    fclose(output_file);
    exit(EXIT_SUCCESS);
}
