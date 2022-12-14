# conexidade-dinamica

## Comentário de 12/12/2022
* Aproximei a versão "crua" da lct que está na main, com a versão "confusa" da lct que está na branch client-test-make
* Acredito que esteja certo o algoritmo, porém não adicionei prints de teste ou mesmo o código do cliente, e nem mesmo os testes.
* Próximo passo é fazer TESTES DE CONECTIVIDADE e não de caminho. Testes que verificam se as árvores estão de acordo são muito custosos, acredito que valha a pena começar apenas com testes de conectividade mesmo.

## Comentário 13/12/2022
* Compile: gcc -g client.c -o client
* Código client feito
    * Reconhece tests no padrão pré-determinado:
        - primeira linha é a quantidade de vértices
        - próximas linhas no padrão a seguir: "+ a b" ou "- c d"
    * Lê os testes que estão hard-codados no código e printa seu conteúdo.

### TO-DO
* Testes para conectividade
* Makefile