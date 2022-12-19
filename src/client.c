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
void executeOperation(char * first_word, char * second_word, char * third_word) {
    int vertice1, vertice2;

    // Verifica qual é a operação desejada pela linha e executa a operação
    if (strcmp(first_word,"+") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        printf("Operação addEdge entre: %d e %d\n", vertice1, vertice2);

        addEdge(vertice1, vertice2);

    } else if (strcmp(first_word,"-") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        printf("Operação removeEdge entre: %d e %d\n", vertice1, vertice2);

        deleteEdge(vertice1, vertice2);

    } else if (strcmp(first_word,"c") == 0)
    {
        vertice1 = atoi(second_word);
        vertice2 = atoi(third_word);
        printf("Operação Connected entre: %d e %d\n", vertice1, vertice2);

        if (connected(vertice1, vertice2)) printf("Vertices %d  e %d estão conectados\n", vertice1, vertice2);
        else printf("Vertices %d e %d NÃO estão conectados\n", vertice1, vertice2);
        
    } else {
        perror("Erro no handleFile caracter não identificado. Não é '+', '-' ou 'c'.\n");
        exit(EXIT_FAILURE);
    }
    return;
}


// Lida com as informações do arquivo de entrada
void handleFile(FILE* fp) {
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
    while ((read = getline(&line, &len, fp)) != -1) {

        // Depois retiro essas duas próximas linhas
        printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);

        // se for a primeira linha do arquivo eu leio o número de vértices
        if (primeira_linha)
        {
            n_vertices =  atoi(line);
            printf("n: %d\n", n_vertices);
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
                    printf("->'%s'\n", first_word);
                } else if (j == 1) {
                    second_word = ptr;
                    printf("->'%s'\n", second_word);
                } else if (j == 2) {
                    third_word = ptr;

                    //remove a newline do fim da third_word
                    third_word[strlen(third_word)-1] = '\0';
                    printf("->'%s'\n", third_word);
                }
                ptr = strtok(NULL, delim);
                j++;
            }

            // Executa a operação desejada
            executeOperation(first_word, second_word, third_word);
        }
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
    arquivo_entrada = fopen(argv[1], "r");
	if (arquivo_entrada == NULL) {
		perror("Error while opening the file of arquivo_entrada.\n");
		exit(EXIT_FAILURE);
	}

    // Lida com as informações do arquivo de entrada
    handleFile(arquivo_entrada);

    fclose(arquivo_entrada);
    exit(EXIT_SUCCESS);
}
