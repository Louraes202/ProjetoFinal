#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "read_files.h"
#include "operations.h"

#ifdef _WIN32
  #include <windows.h>   // SetConsoleCP, SetConsoleOutputCP
#endif


int main(void) {
    NodePassagem* lista = NULL;
    const char *ficheiro = "passagem.txt";

    // Início da medição
    clock_t inicio = clock();

    // Chama a função que queremos medir
    lerPassagens(ficheiro, &lista);

    // Fim da medição
    clock_t fim = clock();

    // Calcula o tempo (em segundos)
    double tempo_cpu = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de CPU gasto pela lerPassagens(): %.3f s\n", tempo_cpu);

    // (opcional) se quiser tempo real de relógio em POSIX:
    // struct timespec t1, t2;
    // clock_gettime(CLOCK_MONOTONIC, &t1);
    // lerPassagens(...);
    // clock_gettime(CLOCK_MONOTONIC, &t2);
    // double real = (t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec)/1e9;
    // printf("Tempo real gasto: %.3f s\n", real);

    // … imprimir ou libertar lista …

    libertarListaPassagens(&lista);
    return 0;
}