#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "read_files.h"

#ifdef _WIN32
  #include <windows.h>   // SetConsoleCP, SetConsoleOutputCP
#endif


// Imprime a lista de distâncias
void imprimirListaDistancias(NodeDistancia* lista) {
    printf("\n--- Lista de Distâncias ---\n");
    if (!lista) {
        printf("Nenhuma distância carregada.\n");
        return;
    }
    int i = 1;
    for (NodeDistancia* p = lista; p; p = p->next, i++) {
        printf("%2d) %d -> %d : %.3f km\n",
               i,
               p->distancia.idSensor1,
               p->distancia.idSensor2,
               p->distancia.distancia);
    }
}

// Liberta a memória da lista de distâncias
void libertarListaDistancias(NodeDistancia** lista) {
    NodeDistancia *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Distancia libertada.\n", cont);
}

int main(void) {
    printf("=== Teste de lerDistancias() ===\n");

    NodeDistancia* listaDistancias = NULL;

    // 1) Lê distâncias
    printf("\n1) A ler distancias.txt...\n");
    lerDistancias("Dados-Portagens-Trab-Pratico/distancias.txt", &listaDistancias);

    // 2) Imprime para verificar
    imprimirListaDistancias(listaDistancias);

    // 3) Liberta memória
    printf("\nA libertar memória de distâncias...\n");
    libertarListaDistancias(&listaDistancias);

    printf("\n=== Fim do Teste ===\n");
    return 0;
}