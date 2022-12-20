# Dynamic connectivity

### README In Progress

### Acknowledgements
This work exists thanks to Institute of Mathematics and Statistics of University of São Paulo ([IME-USP](https://www.ime.usp.br/)), to [CNPq](https://www.gov.br/cnpq/pt-br) for the scholarship provided and to [Prof. Cristina Gomes Fernandes](https://www.ime.usp.br/~cris/).
### How to run
* $ make
* $ ./exe <test_name> <test_number> [flag_v_for_verbose_output]

Or
* $ chmod +x runtests.sh
* $ ./runtests.sh -t


Example of output after running ./runtests -t

```
$ ./runtests.sh -t
[CC] src/client.c
[CC] src/dynamic_forest.c
[CC] src/lct.c
[CC] src/splay.c
[CC] src/node.c
[CC] src/item.c
[INFO] Creating Binary Executable for Iterative File [exe]
------- Running function runningTests -------
--- Running test1 ---
Result test file name: tests/results/result_test1
Test with 10 vertices.
Time taken to run dynamicForest: 0.000003
Vertices 6 and 5 are NOT connected
Total amount of time taken to run addEdge, removeEdge and connected: 0.000010
Number of queries of type addEdge, removeEdge and connected: 10
Avg of time taken to run addEdge, removeEdge and connected: 1.000000e-06
--- Running test2 ---
Result test file name: tests/results/result_test2
Test with 6 vertices.
Time taken to run dynamicForest: 0.000002
Vertices 1 and 5 are NOT connected
Vertices 1 and 5 are connected
Vertices 1 and 5 are NOT connected
Vertices 1 and 5 are connected
Total amount of time taken to run addEdge, removeEdge and connected: 0.000013
Number of queries of type addEdge, removeEdge and connected: 11
Avg of time taken to run addEdge, removeEdge and connected: 1.181818e-06
```

### TO-DO
* Fazer um bom README orientando como executar
	* Como adicionar um novo test
* Explicação de como criar arquivo test
	* ter uma última linha vazia
	* o número de vértices que se acreescenta no arquivo deve contar o vértice zero: n = 6 -> 0, 1, 2, 3, 4, 5
    * deve ter o seguinte formato:
        - primeira linha é a quantidade de vértices
        - próximas linhas no padrão a seguir: "+ X Y" ou "- X Y" ou "c X Y"
		- última linha vazia
* Explicação de como criar um arquivo de answer:
	* criar um arquivo com NO and/or YES e sempre ter uma última linha vazia
	* ao criar será preciso mudar o arquivo sh
* Explicação de como executar runtests
	* chmod +x runtests.sh
	* ./runtests.sh -t
* Explicação de como executar seediff
	* chmod +x seediff.sh
	* ./seediff.sh -d (pra ver as diferenças)
	* ./seediff.sh -s (pra ver qual foi bem sucedido e qual não)
* Informação do compilador?
