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

### How to run seediff.sh file
* The file's goal is to indentify which test had the right output and those which had the wrong output, and to see what output was wrong.
* To run seediff.sh, you must do the following:
	* $ chmod +x seediff.sh
	* $ ./seediff.sh -d 
		* (To identify the differences bewteen the answer and the test output)
	* $ ./seediff.sh -s 
		* (to identify which test had the right output)


### How to create a new test
* Add a file in the directory "tests"
* The file's name must be "test<test_number>"
* The file's first line must be a integer between 1 and 2147483647
	* This line indicates the number of vertices
		* If the first line contains the number 3, so the number of vertices are 3, but these vertices are indicated as 0, 1 and 2. There is not a vertice labeled as 3.
* The other lines must follow the following pattern:
	1. \+ X Y
	2. \- X Y
	3. c X Y
	- Where X and Y are integers between 1 and the number of vertices, and
		- '\+' indicates add edge operation
		- \'-' indicates remove edge operation
		- 'c' indicates connected query
* The last line must be empty
* Example of a file named "test5"
```
6
+ 1 2
+ 4 5
c 4 5
c 4 1
c 1 2

```

### How to update the runtests.sh file
* After you added a new test, you can update the runtests.sh file, to run all the tests including the new one.
* You'll need to update the maximum test number you wanna run, in the loop:
```
    for i in {1..<MAX_TEST_NUMBER>}
```
### How to create a new answer file
* Add a file in the /tests/answers/ directory
* The file's name must be "answer_test<TEST_NUMBER>"
	* This is the answer of the test "test<TEST_NUMBER>
* This file contains the answers of the queries contained in the "test<TEST_NUMBER>".
	* So if there are 3 queries in the format "c X Y", your answer file requires 3 answers for those queries.
	* The answers are in the format "YES" or "NO"
* The last line must be empty
* Example of a file "answer_test5"
```
YES
NO
YES

``` 
### How to update the seediff.sh file
* After you added a new answer_test, you can update the seediff.sh file, to verify if the tests are returning the right output.
* You'll need to update the number of the tests number you wanna verify, in the loop:
```
    for i in {1..<TEST_NUMBER>}
```

```
function whichDifference() {
    mkdir ./tests/diff
    for i in {1..<TEST_NUMBER>}
    ...
}


function failedOrSucessed() {
    for i in {1..<TEST_NUMBER>}
    ...
}

```
