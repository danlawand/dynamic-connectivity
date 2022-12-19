# Dynamic connectivity

### README In Progress

### Acknowledgements
This work exists thanks to Institute of Mathematics and Statistics of University of São Paulo ([IME-USP](https://www.ime.usp.br/)), to [CNPq](https://www.gov.br/cnpq/pt-br) for the scholarship provided and to [Prof. Cristina Gomes Fernandes](https://www.ime.usp.br/~cris/).
### How to run
* $ make
* $ ./exe <test_name> <test_number> [flag_v_for_verbose_output]

Or
* $ make
* $ chmod +x runtests.sh
* $ ./runtests.sh -t

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
