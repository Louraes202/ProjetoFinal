#include "read_files.h"   // Declaração da função
#include "data.h"         // Para saber o que é Dono e NodeDono
#include <stdio.h>        // fopen, fscanf, fclose
#include <stdlib.h>       // malloc, free
#include <string.h>       // strcpy


// /*
// Falta implementar a passagem dos dados para a estrutura
// */
void lerDonos(const char* nomeFicheiro, NodeDono** listaDonos) {

    // 1. Abrir o ficheiro
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        return;
    }

    // 2. Variáveis dos dados a passar para a estrutura
    int numero;
    char nome[200];
    char codigoPostal[10];
    char linha[255];

    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);


    while (fgets(linha, sizeof(linha), fp)) {

        // <numContribuinte>
        char *token = strtok(linha, "\t"); // separar o conteúdo da linha (<numContribuinte> <nomeDono> <codPostal>)
        if (token == NULL) continue; // verificar se a linha foi separada corretamente
        int numContribuinte = atoi(token);

        // <nomeDono>
        token = strtok(NULL, "\t"); // continuar a separar a string
        if (token == NULL) continue; // verificar se a linha foi separada corretamente
        char nome[200];
        strcpy(nome, token);

        // <codPostal>
        token = strtok(NULL, "\t\n\r"); // continuamos e apanhamos o pedaço final
        if (token == NULL) continue; // verificaçáo **
        char codigoPostal[10];
        strcpy(codigoPostal, token);

        // TESTE: Verificar se os dados estão a ser lidos corretamente
        printf("Lido: Contribuinte: %d, Nome: %s, Código Postal: %s\n", numero, nome, codigoPostal);

    }

    // 3. Fechar o ficheiro
    fclose(fp);
}

