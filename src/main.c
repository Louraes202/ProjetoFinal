#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para free, NULL
#include "data.h"       // Para NodeDono, Dono, NodeCarro, Carro
#include "read_files.h" // Para lerDonos, lerCarros (e outras declaradas)

// --- Funções Auxiliares para Teste (Donos) ---

/*
 * Imprime o conteúdo da lista ligada de Donos.
 */
void imprimirListaDonos(NodeDono* lista) {
    printf("\n--- Lista de Donos Carregada ---\n");
    if (lista == NULL) {
        printf("A lista de Donos está vazia.\n");
        return;
    }
    NodeDono* atual = lista;
    int count = 0;
    while (atual != NULL) {
        // Imprime apenas alguns para não sobrecarregar o output
        if (count < 5 || atual->next == NULL) { // Imprime os 5 primeiros e o último
             printf("Dono %d: Contribuinte=%d, Nome='%s', CP='%s'\n",
                   count + 1,
                   atual->dono.numeroContribuinte,
                   atual->dono.nome,
                   atual->dono.codigoPostal);
        } else if (count == 5) {
            printf("   ... (mais donos) ...\n");
        }
        atual = atual->next;
        count++;
    }
    printf("--- Fim da Lista (%d donos) ---\n", count);
}

/*
 * Liberta toda a memória alocada para a lista ligada de Donos.
 */
void libertarListaDonos(NodeDono** lista) {
    NodeDono* atual = *lista;
    NodeDono* proximo;
    int count = 0;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
        count++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Dono libertada.\n", count);
}

// --- Funções Auxiliares para Teste (Carros) ---

/*
 * Imprime o conteúdo da lista ligada de Carros.
 */
void imprimirListaCarros(NodeCarro* lista) {
    printf("\n--- Lista de Carros Carregada ---\n");
    if (lista == NULL) {
        printf("A lista de Carros está vazia.\n");
        return;
    }
    NodeCarro* atual = lista;
    int count = 0;
    while (atual != NULL) {
         // Imprime apenas alguns para não sobrecarregar o output
        if (count < 5 || atual->next == NULL) { // Imprime os 5 primeiros e o último
            printf("Carro %d: Matricula=%s, Marca=%s, Modelo=%s, Ano=%d, Dono=%d, ID=%d\n",
                   count + 1,
                   atual->carro.matricula,
                   atual->carro.marca,
                   atual->carro.modelo,
                   atual->carro.ano,
                   atual->carro.donoContribuinte,
                   atual->carro.idVeiculo);
        } else if (count == 5) {
             printf("   ... (mais carros) ...\n");
        }
        atual = atual->next; // Avança para o próximo nó
        count++;
    }
    printf("--- Fim da Lista (%d carros) ---\n", count);
}

/*
 * Liberta toda a memória alocada para a lista ligada de Carros.
 */
void libertarListaCarros(NodeCarro** lista) {
    NodeCarro* atual = *lista;
    NodeCarro* proximo;
    int count = 0;
    while (atual != NULL) {
        proximo = atual->next; // Guarda referência para o próximo nó
        free(atual);           // Liberta a memória do nó atual
        atual = proximo;       // Move para o próximo nó
        count++;
    }
    *lista = NULL; // Define o ponteiro original da lista como NULL
    printf("\nMemória de %d nós Carro libertada.\n", count);
}


// --- Função Principal ---

int main() {
    printf("Iniciando programa de teste de leitura de ficheiros...\n");

    // 1. Inicializar ponteiros das listas
    NodeDono* listaDeDonos = NULL;
    NodeCarro* listaDeCarros = NULL;
    // NodeSensor* listaDeSensores = NULL; // Para testes futuros
    // NodeDistancia* listaDeDistancias = NULL; // Para testes futuros
    // NodePassagem* listaDePassagens = NULL; // Para testes futuros


    // 2. Chamar as funções de leitura implementadas
    printf("\nA chamar lerDonos...\n");
    // *** CAMINHO CORRIGIDO ***
    lerDonos("Dados-Portagens-Trab-Pratico/donos.txt", &listaDeDonos);

    printf("\nA chamar lerCarros...\n");
    // *** CAMINHO CORRIGIDO ***
    lerCarros("Dados-Portagens-Trab-Pratico/carros.txt", &listaDeCarros);


    // 3. Imprimir as listas para verificar (opcional para donos, importante para carros agora)
    // imprimirListaDonos(listaDeDonos); // Podes descomentar se quiseres ver os donos também
    imprimirListaCarros(listaDeCarros);


    // 4. Libertar a memória alocada para TODAS as listas
    printf("\nA libertar memória...\n");
    libertarListaDonos(&listaDeDonos);
    libertarListaCarros(&listaDeCarros);
    // libertarListaSensores(&listaDeSensores); // Adicionar quando implementado
    // libertarListaDistancias(&listaDeDistancias); // Adicionar quando implementado
    // libertarListaPassagens(&listaDePassagens); // Adicionar quando implementado


    printf("\nPrograma de teste concluído.\n");

    return 0; // Indica que o programa terminou com sucesso
}
