#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forest.h"
#include <analisaLct.h>

static void *mallocSafe(size_t);
#define TAMANHO_MAX 200


int main(int argc, char * argv[]) {
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
	char flag_output = 'q';
	if (argc == 4) flag_output = 'v';

	FILE *arquivo_entrada;
	FILE * arquivo_de_saida;

	// Lê o arquivo de entrada
	arquivo_entrada = fopen(argv[1], "r");

	// Verifica se o arquivo de entrada existe
	if (arquivo_entrada == NULL) {
		perror("Error while opening the file of arquivo_entrada.\n");
		exit(EXIT_FAILURE);
	}

	// Operacao para gerar o nome do arquivo do resultado do i-ésimo teste
	char output_file_name[] = "test/result_test/result_test";
    strcat(output_file_name,argv[2]);
    printf("\n Result test file name: %s\n", output_file_name);

	// Abre o arquivo de saída
	arquivo_de_saida = fopen (output_file_name, "w");

	// Verifica se a criação do arquivo de saída foi bem sucedida
	if (arquivo_de_saida == NULL) {
		perror("Error while opening the file arquivo_de_saida.\n");
		exit(EXIT_FAILURE);
	}


	//buffer para o arquivo de entrada
	char buffer[TAMANHO_MAX];


	// variavel que armazena quantos nós teremos
	int n_vertices;

	//variáveis auxiliares
	int indice[2], tag_link = 2, tag_cut = 2, i = 1;
	indice[0] = 0;
	indice[1] = 0;

	LCT linkCutTree;

	/* le do arquivo */
    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){

    	//Se for a primeira iteração, pegaremos a primeira linha do arquivo que é a quantidade de nós
    	if (i == 1){
    		n_vertices = atoi(buffer);

    		//Crio 'n_vertices' árvores com apenas um vértice cada (Cada linkCutTree->nodes[i] é a raiz de sua árvore)
    		linkCutTree = dynamicForest(n_vertices);

			// if (flag_output == 'v') printf("%d Vertices Criados\n",n_vertices);
    	}
    	i = 0;


    	//Vou pegar de dois em dois vértices para fazer a operação.
    	//tag_link indica qual vértice eu estou me referindo, se for zero equivale ao primeiro, se for 1 ao segundo
    	if (tag_link < 2) {
    		//Identifico o índice do vértice que realizaremos a operação, e atribuo no indice[0] ou indice[1]
    		indice[tag_link] = atoi(buffer);

    		//Quando identificarmos o segundo nó, façamos:
    		if (tag_link == 1) {

				// Print Verboso ou não
    			if (flag_output == 'v') printf("------------------------------ Link dos Vertices %d e %d ------------------------------\n",indice[tag_link-1], indice[tag_link]);

                // ADD EDGE
                addEdge(linkCutTree, indice[tag_link-1], indice[tag_link]);

				if (flag_output == 'v') {
					printf("\n*********** Depois do Link ***********\n");
					for (int i = 0; i < n_vertices; i++) {
						printf("\n");
						analisaSplay(linkCutTree->nodes[i]);
						printf("\n");
					}
				}

				// // Print Verboso ou não
				// if (flag_output == 'v') {
				// 	printf("ANALISANDO %d\n", indice[tag_link-1]);
				// 	analisaSplay(linkCutTree->nodes[indice[tag_link-1]]);
				// 	printf("\n");
				// 	// printSPLAY(linkCutTree->nodes[indice[tag_link-1]], 1);
				// 	printf("\n");
				// }
    		}
    		tag_link++;
    	}

    	//tag_cut indica se haverá cut ou não
    	if (tag_cut < 2) {
    		//Identifico o índice do vértice que realizaremos a operação, e atribuo no indice[0]
    		indice[tag_cut] = atoi(buffer);

			// Print verbose ou não

			if (tag_cut == 1) {
				// DELETE EDGE (O SEGUNDO ARGUMENTO É ZERO PORQUE JÁ SABEMOS QUE QUEREMOS CORTAR O NÓ COM O SEU PAI)

    			if (flag_output == 'v') printf("------------------------------ Cut dos Vertices %d e %d ------------------------------\n",indice[0], indice[1]);

				if (flag_output == 'v') {

					printf("\n*********** ANTES do Delete ***********\n");
					for (int i = 0; i < n_vertices; i++) {
						printf("\n");
						analisaSplay(linkCutTree->nodes[i]);
						printf("\n");
					}
				}

				deleteEdge(linkCutTree, indice[tag_cut-1], indice[tag_cut]);

				// Print Verboso ou não
				if (flag_output == 'v') {

					printf("\n*********** Depois do Delete ***********\n");
					for (int i = 0; i < n_vertices; i++) {
						printf("\n");
						analisaSplay(linkCutTree->nodes[i]);
						printf("\n");
					}
				}
				// if (flag_output == 'v') {
				// 	printf("\nDepois do Delete\n");
				// 	analisaSplay(linkCutTree->nodes[indice[0]]);
				// 	printf("\n");
				// 	// printSPLAY(linkCutTree->nodes[indice[0]], 1);
				// 	printf("\n");

				// 	analisaSplay(linkCutTree->nodes[indice[1]]);
				// 	printf("\n");
				// 	// printSPLAY(linkCutTree->nodes[indice[1]], 1);
				// 	printf("\n");
				// }
			}
    		tag_cut++;
    	}


    	if (buffer[0] == '+') {
    		tag_link = 0;
    		tag_cut = 2;
    	}

    	if (buffer[0] == '-') {
    		tag_cut = 0;
    		tag_link = 2;
    	}

    }

	if (flag_output == 'v') printf("\n------------- Print Final for Test %s ------------- \n\n",argv[2]);
	else printf("\n--------------------- Test %s --------------------- \n\n",argv[2]);
	for (int i = 0; i < n_vertices; ++i)
	{
		//Analiso cada nó, para ver como foi seu comportamento.
		analisaNode(linkCutTree->nodes[i], arquivo_de_saida);
	}

	// for (int i = 0; i < n_vertices; i++) {
	// 	printf("Chamada de %d:\n", i);
	// 	traversal(linkCutTree, i);
	// 	printf("\n\n");

	// }

	fclose(arquivo_de_saida);
	fclose (arquivo_entrada);
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}