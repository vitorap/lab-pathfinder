# lab-pathfinder

1- Neste Problema, tenta-se determinar a rota entre a entrada e a saída de um labirinto que, com certeza, terá essa rota, como o da ilustração a baixo.

2Modelagem
do problema
O labirinto é representado através de um Grafo de Restrições , onde as
variáveis são os nós que representam cada posição do labirinto e os arcos tem
como restrição conectar dois nós que estejam nas posições Norte, Sul, Leste ou
Oeste entre si no labirinto, assim como ilustrado na Figura 2.
Figura 2
3 Métodos
de BUSCA:
3.1 Não
informada:
Utilizase
a busca em PROFUNDIDADE, uma vez que a árvore de
busca do grafo que representa as conexões do labirinto será mais profunda
que larga, fazendo com que este método seja mais eficiente quanto ao tempo
de execução.
3.2 Informada:
Utilizase
a busca A*, para que mesmo que não seja mais rápida,o
menor caminho possível seja encontrado caso haja mais que um. Neste
caso, cada aresta entre nós adjacentes possui uma distância com o valor de
uma unidade, que é somado à distância em linha reta na função de avaliação
da busca, seguindo a Fórmula I.
ab D = √(Xa − Xb) (Y ) (Fórmula I)
2 + a − Y b
2
4 Funcionamento
geral do código:
4.1 Estruturas
principais
O labirinto possui uma matriz de ponteiros para as posições de um
grafo, o qual representa cada posição do labirinto e permite que sejam feitas
conexões seguindo a modelagem de estados especificada de acordo com as
posições deles na matriz do labirinto.
O grafo é implementado utilizandose
um vetor com todas as posições
dele, sendo que em cada posição possui um pequeno vetor de quatro
posições, cada uma possibilitando uma conexão na ordem Norte(0), Sul(1),
Leste(2) e Oeste(3).
4.2 Passos
de execução
Primeiramente, é gerado o labirinto sem nenhuma conexão, então as
conexões são feitas a partir do nó de entrada com nós adjacentes que estão
isolados e, tomandose
esse novo nó como o de partida, continuase
a
geração de conexões até que haja pelo menos um caminho entre cada nó do
grafo do labirinto, ou seja, até que o grafo se torne conexo.
Então é feita a busca em profundidade no grafo pela saída a partir da
entrada e depois a busca A* seguindo a maneira como ja foi explicada.
5 Modo
de compilação e execução do programa:
Para compilar o programa, basta digitar o comando make no terminal a partir
do diretório do trabalho, onde se encontra o makefile.
Para execução, devese
apenas digitar o comando make run a partir do
mesmo diretório de compilação.
Obs.: O compilador utilizado para testes foi o gcc versão 4.8.4 no sistema
operacional Ubuntu versão 14.04.1.
6 Entradas
e saídas:
Após a execução do programa, basta informar as duas dimensões do
labirinto conforme são pedidas.
A saída consistirseá
em dois labirintos impressos com o caminho tomado
pelas buscas indicados pelos caracteres ‘+’, um para cada busca realizada, além o
tempo tomado para encontrar o dado caminho em cada busca.
7 Experimentos
Realizados:
Comparação dos dois métodos de busca utilizado
Tamanho do labirinto
Tempo da busca em profundidade (s) x Tempo da busca A* (s)
5x5 0.000003 0.000017
5x5 0.000004 0.000015
5x5 0.000003 0.000015
5x5 0.000002 0.000013
5x5 0.000003 0.000016
10x10 0.000011 0.000016
10x10 0.000010 0.000023
10x10 0.000010 0.000019
15x30 0.000048 0.000127
15x30 0.000039 0.000080
Média 0.000013 0.000034
Tabela 1

8Considerações
Finais:
Analisando os resultados obtidos, chegamos a conclusão de que a busca em
profundidade obtém, na maioria das vezes, um caminho até a saída em um menor
tempo. Em compensação, a busca A* obtém, apesar de em um tempo um pouco
maior, um caminho mais curto caso haja mais que um possível, que é o menor
caminho possível a ser percorrido no grafo.
