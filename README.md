# conexidade-dinamica

### TO-DO
* Fazer um bom README orientando como executar
	* Como adicionar um novo test

## Comentário 19/12/2022
* Criação de novos tests
* Explicação de como criar arquivo test
	* ter uma última linha vazia
	* o número de vértices que se acreescenta no arquivo deve contar o vértice zero: n = 6 -> 0, 1, 2, 3, 4, 5
* Explicação de como criar um arquivo de answer:
	* criar um arquivo com NO and/or YES e sempre ter uma última linha vazia
	* ao criar será preciso mudar o arquivo sh
* Explicação de como executar runtests
	* chmod +x runtests.sh
	* ./runtests.sh -t
* Remoção de erro no código da lct:
### Antigo
```
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = v;
		w->children[1]->parent = NULL;
	}
	// w se torna filho direito de v
	join(w, v);
	v->pathParent = NULL;
}
```

### NOVO
```
		w->children[1]->pathParent = w;
```


## Comentário 14/12/2022
* Criação do Makefile
* Teste com inserção, remoção e consulta 
* addEdge, deleteEdge e connected estão funcionando
* Remoção de erro no código da lct:
### Antigo
```
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = v;
		w->children[1]->parent = NULL;
	}
	// w se torna filho direito de v
	join(v, w);
	v->pathParent = NULL;
}
```

### NOVO
```
	// v se torna filho direito de w
	join(w, v);
```

## Comentário 13/12/2022
* Compile: gcc -g client.c -o client
* Código client feito
    * Reconhece tests no padrão pré-determinado:
        - primeira linha é a quantidade de vértices
        - próximas linhas no padrão a seguir: "+ a b" ou "- c d"
    * Lê os testes que estão hard-codados no código e printa seu conteúdo.
## Comentário de 12/12/2022
* Aproximei a versão "crua" da lct que está na main, com a versão "confusa" da lct que está na branch client-test-make
* Acredito que esteja certo o algoritmo, porém não adicionei prints de teste ou mesmo o código do cliente, e nem mesmo os testes.
* Próximo passo é fazer TESTES DE CONECTIVIDADE e não de caminho. Testes que verificam se as árvores estão de acordo são muito custosos, acredito que valha a pena começar apenas com testes de conectividade mesmo.
