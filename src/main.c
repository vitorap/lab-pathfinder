#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../header/pilha.h"
#include "../header/labirinto.h"

double getTimeElapsed(struct timeval start, struct timeval end) {
    return (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) / 1e6;
}

int main(void) {
    int lin, col, iteracoes, modo;
    struct timeval t1, t2;
    double totalTimeDFS = 0, totalTimeAStar = 0;

    printf("Escolha o modo de execução: \n");
    printf("1. Modo Gráfico \n2. Modo Relatório \n");
    scanf("%d", &modo);

    if (modo == 1) {
        printf("Digite o numero de linhas do labirinto: ");
        scanf("%d", &lin);
        printf("\nDigite o numero de colunas do labirinto: ");
        scanf("%d", &col);
        printf("\n");

        labirinto_t labrt;
        labrt_init(&labrt, lin, col);

        gettimeofday(&t1, NULL);
        labrt_findSaida(&labrt, PROFUNDIDADE);
        gettimeofday(&t2, NULL);

        labrt_print(&labrt);
        printf("Tempo tomado na busca DFS: %lfs\n", getTimeElapsed(t1, t2));

        gettimeofday(&t1, NULL);
        labrt_findSaida(&labrt, INFORMADA);
        gettimeofday(&t2, NULL);

        labrt_print(&labrt);
        printf("Tempo tomado na busca A*: %lfs\n", getTimeElapsed(t1, t2));

        labrt_destroy(&labrt);

    } else if (modo == 2) {
        printf("Digite o número de iterações para o relatório: ");
        scanf("%d", &iteracoes);
        printf("\nDigite o tamanho N do labirinto (N x N): ");
        scanf("%d", &lin);
        col = lin; // Labirinto será quadrado

        printf("\n| Iteração | Tempo da DFS (s) | Tempo A* (s) |\n");
        printf("|----------|------------------|--------------|\n");

        for (int i = 0; i < iteracoes; ++i) {
            labirinto_t labrt;
            labrt_init(&labrt, lin, col);

            gettimeofday(&t1, NULL);
            labrt_findSaida(&labrt, PROFUNDIDADE);
            gettimeofday(&t2, NULL);
            double timeDFS = getTimeElapsed(t1, t2);
            totalTimeDFS += timeDFS;

            gettimeofday(&t1, NULL);
            labrt_findSaida(&labrt, INFORMADA);
            gettimeofday(&t2, NULL);
            double timeAStar = getTimeElapsed(t1, t2);
            totalTimeAStar += timeAStar;

            printf("| %8d | %16.6lf | %12.6lf |\n", i+1, timeDFS, timeAStar);

            labrt_destroy(&labrt);
        }

        printf("\nTempo médio na busca DFS: %lfs\n", totalTimeDFS / iteracoes);
        printf("Tempo médio na busca A*: %lfs\n", totalTimeAStar / iteracoes);
    }

    return 0;
}
