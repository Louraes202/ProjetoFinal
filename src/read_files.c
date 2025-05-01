#include "read_files.h" // Assume que declara lerDonos e inclui data.h
#include "data.h"       // Para NodeDono, Dono, e constantes de tamanho
#include <stdio.h>      // fopen, fgets, fclose, fprintf, stderr, printf
#include <stdlib.h>     // malloc, free, atoi
#include <string.h>     // strtok, strcpy, strncpy, strchr

// --- Função Auxiliar Estática ---
// Esta função só será visível dentro deste ficheiro (read_files.c)
// Serve para libertar a memória de uma lista de donos.
// É usada internamente por lerDonos em caso de erro de alocação.

/*
 * Liberta toda a memória alocada para uma lista ligada de Donos.
 * Função auxiliar para ser usada dentro de read_files.c.
 * Parâmetros:
 * lista: Ponteiro para o ponteiro da cabeça da lista (para poder anular o ponteiro original).
 */
static void libertarListaDonosParcial(NodeDono** lista) {
    NodeDono* atual = *lista;
    NodeDono* proximo;
    int count = 0;

    while (atual != NULL) {
        proximo = atual->next; // Guarda referência para o próximo nó
        free(atual);           // Liberta a memória do nó atual
        atual = proximo;       // Move para o próximo nó
        count++;
    }

    *lista = NULL; // Define o ponteiro original da lista como NULL
    if (count > 0) {
         fprintf(stderr, " -> Memória de %d nós libertada.\n", count);
    }
}

/*
 * Liberta toda a memória alocada para uma lista ligada de Carros.
 * Função auxiliar para ser usada dentro de read_files.c.
 */
static void libertarListaCarrosParcial(NodeCarro** lista) {
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
    if (count > 0) {
         fprintf(stderr, " -> Memória de %d nós Carro libertada.\n", count);
    }
}

// --- Função Auxiliar Estática para Liberar Sensores em Caso de Erro ---
static void libertarListaSensoresParcial(NodeSensor** lista) {
    NodeSensor *atual = *lista, *proximo;
    int count = 0;
    while (atual) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
        count++;
    }
    *lista = NULL;
    if (count > 0) {
        fprintf(stderr, " -> Memória de %d nós Sensor libertada.\n", count);
    }
}

/**
 * @brief Liberta todos os nós de NodeDistancia de uma lista.
 *        Usada internamente se ocorrer erro de malloc em lerDistancias().
 */
static void libertarListaDistanciasParcial(NodeDistancia** lista) {
    NodeDistancia *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    if (cont > 0) {
        fprintf(stderr, " -> Memória de %d nós Distancia libertada por erro.\n", cont);
    }
}

/* Função auxiliar para libertar parcialmente em caso de erro */
static void libertarListaPassagensParcial(NodePassagem** lista) {
    NodePassagem *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    if (cont > 0) {
        fprintf(stderr, " -> Memória de %d nós Passagem libertada por erro.\n", cont);
    }
}



// --- Função Principal de Leitura de Donos ---

/*
 * Função para ler os dados dos donos a partir de um ficheiro de texto
 * e armazená-los numa lista ligada.
 * (Versão com inicialização e libertação de memória em caso de erro no malloc)
 *
 * Parâmetros:
 * nomeFicheiro (const char*): O nome do ficheiro a ser lido (ex: "donos.txt").
 * listaDonos (NodeDono**): Ponteiro para o ponteiro da cabeça da lista ligada de donos.
 * A lista será modificada para incluir os donos lidos.
 */
void lerDonos(const char* nomeFicheiro, NodeDono** listaDonos) {

    // 1. Abrir o ficheiro
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaDonos = NULL; // Garante que a lista está vazia se o ficheiro não abrir
        return;
    }

    // 2. Variáveis para armazenar temporariamente os dados lidos de CADA linha
    int numContribuinteLido;
    char nomeLido[DONO_MAX_NOME];
    char codigoPostalLido[DONO_MAX_CODIGOPOSTAL];
    char linha[512];

    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);

    // *** INICIALIZAÇÃO DA LISTA ADICIONADA ***
    // Garante que começamos com uma lista vazia, descartando qualquer conteúdo anterior.
    *listaDonos = NULL;

    // 3. Ler o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), fp)) {

        // Ignorar linhas em branco ou que não contenham o delimitador tab
        if (strchr(linha, '\t') == NULL) {
            continue;
        }

        // --- Parsing da Linha ---
        char *token;

        token = strtok(linha, "\t");
        if (token == NULL) continue;
        numContribuinteLido = atoi(token);

        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        strncpy(nomeLido, token, DONO_MAX_NOME - 1);
        nomeLido[DONO_MAX_NOME - 1] = '\0';

        token = strtok(NULL, "\t\n\r");
        if (token == NULL) continue;
        strncpy(codigoPostalLido, token, DONO_MAX_CODIGOPOSTAL - 1);
        codigoPostalLido[DONO_MAX_CODIGOPOSTAL - 1] = '\0';

        // --- Armazenamento na Lista Ligada ---

        NodeDono* novoNode = (NodeDono*)malloc(sizeof(NodeDono));
        if (novoNode == NULL) {
            fprintf(stderr, "Erro Crítico: Falha ao alocar memória para novo Dono.\n");
            fclose(fp); // Fecha o ficheiro

            // *** LIBERTAÇÃO DE MEMÓRIA EM CASO DE ERRO ***
            // Chama a função auxiliar para libertar os nós já criados nesta chamada
            fprintf(stderr, " -> A libertar memória já alocada...\n");
            libertarListaDonosParcial(listaDonos); // Passa o ponteiro para a cabeça da lista

            return; // Sai da função após libertar a memória
        }

        // Preencher o Nó
        novoNode->dono.numeroContribuinte = numContribuinteLido;
        strcpy(novoNode->dono.nome, nomeLido);
        strcpy(novoNode->dono.codigoPostal, codigoPostalLido);

        // (Opcional) Confirmação de dados no nó
         printf("   -> Confirmado no nó: Contribuinte=%d, Nome='%s', CP='%s'\n",
                novoNode->dono.numeroContribuinte,
                novoNode->dono.nome,
                novoNode->dono.codigoPostal);

        // Ligar o Nó à Lista
        novoNode->next = *listaDonos;
        *listaDonos = novoNode;

    } // Fim do while (fgets)

    // 4. Fechar o ficheiro
    fclose(fp);
    printf(">> Ficheiro %s lido e dados dos donos carregados para a lista ligada.\n", nomeFicheiro);
}

void ordenar_por_nome(Dono *donos, int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            // compara nome[j] com nome[j+1]:
            if ( strcmp(donos[j].nome, donos[j+1].nome) > 0 ) {
                Dono tmp = donos[j];
                donos[j] = donos[j + 1];
                donos[j + 1] = tmp;
            }
        }
    }
}

void ordenar_donos(const char *ficheiro) {
    NodeDono* lista = NULL;
    lerDonos(ficheiro, &lista);
    if (!lista) {
        printf("Erro a ler ficheiro de donos ou lista vazia.\n");
        return;
    }

    Dono array[MAX_DONOS];
    int total = 0;
    for (NodeDono* p = lista; p && total < MAX_DONOS; p = p->next) {
        array[total++] = p->dono;
    }
    if (total == 0) {
        printf("Não foram lidos donos.\n");
        return;
    }

    ordenar_por_nome(array, total);

    printf("\n--- Donos ordenados alfabeticamente ---\n");
    for (int i = 0; i < total; i++) {
        printf("%2d) Nome: %s | NIF: %d | CP: %s\n",
               i + 1,
               array[i].nome,
               array[i].numeroContribuinte,
               array[i].codigoPostal);
    }

    libertarListaDonosParcial(&lista);
}

// --- Funções de Leitura Adicionais (Stubs - a implementar) ---
// (O código das outras funções lerXxx permanece aqui como stubs)

/*
 * Lê os dados dos carros do ficheiro especificado e preenche a lista ligada.
 */
void lerCarros(const char* nomeFicheiro, NodeCarro** listaCarros) {
    // 1. Abrir o ficheiro
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaCarros = NULL; // Garante lista vazia em caso de erro
        return;
    }

    // 2. Variáveis temporárias
    char matriculaLida[CARRO_MAX_MATRICULA];
    char marcaLida[CARRO_MAX_MARCA];
    char modeloLido[CARRO_MAX_MODELO];
    int anoLido;
    int donoContribuinteLido;
    int idVeiculoLido;
    char linha[512];

    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);

    // Inicialização da lista
    *listaCarros = NULL;

    // 3. Ler linha a linha
    while (fgets(linha, sizeof(linha), fp)) {

        if (strchr(linha, '\t') == NULL) continue; // Ignora linhas sem tabulação

        // --- Parsing da Linha ---
        char *token;

        // <matrícula>
        token = strtok(linha, "\t");
        if (token == NULL) continue;
        strncpy(matriculaLida, token, CARRO_MAX_MATRICULA - 1);
        matriculaLida[CARRO_MAX_MATRICULA - 1] = '\0';

        // <marca>
        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        strncpy(marcaLida, token, CARRO_MAX_MARCA - 1);
        marcaLida[CARRO_MAX_MARCA - 1] = '\0';

        // <modelo>
        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        strncpy(modeloLido, token, CARRO_MAX_MODELO - 1);
        modeloLido[CARRO_MAX_MODELO - 1] = '\0';

        // <ano>
        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        anoLido = atoi(token);

        // <dono> (NIF do dono)
        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        donoContribuinteLido = atoi(token);

        // <codVeiculo> (ID do veículo)
        token = strtok(NULL, "\t\n\r"); // Apanha o último token
        if (token == NULL) continue;
        idVeiculoLido = atoi(token);

        // --- Armazenamento na Lista Ligada ---

        // Alocar memória
        NodeCarro* novoNode = (NodeCarro*)malloc(sizeof(NodeCarro));
        if (novoNode == NULL) {
            fprintf(stderr, "Erro Crítico: Falha ao alocar memória para novo Carro.\n");
            fclose(fp);
            fprintf(stderr, " -> A libertar memória já alocada...\n");
            libertarListaCarrosParcial(listaCarros); // Libertar memória
            return;
        }

        // Preencher o Nó
        strcpy(novoNode->carro.matricula, matriculaLida); // strcpy seguro após strncpy
        strcpy(novoNode->carro.marca, marcaLida);         // strcpy seguro após strncpy
        strcpy(novoNode->carro.modelo, modeloLido);       // strcpy seguro após strncpy
        novoNode->carro.ano = anoLido;
        novoNode->carro.donoContribuinte = donoContribuinteLido;
        novoNode->carro.idVeiculo = idVeiculoLido;

        // Confirmação (opcional)
        printf("   -> Confirmado no nó Carro: %s, %s %s (%d), Dono:%d, ID:%d\n",
                novoNode->carro.matricula, novoNode->carro.marca, novoNode->carro.modelo,
                novoNode->carro.ano, novoNode->carro.donoContribuinte, novoNode->carro.idVeiculo);

        // Ligar o Nó à Lista
        novoNode->next = *listaCarros;
        *listaCarros = novoNode;

    } // Fim while

    // 4. Fechar ficheiro
    fclose(fp);
    printf(">> Ficheiro %s lido e dados dos carros carregados.\n", nomeFicheiro);
}


// --- Implementação de lerSensores() ---
void lerSensores(const char* nomeFicheiro, NodeSensor** listaSensores) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaSensores = NULL;
        return;
    }

    *listaSensores = NULL;  // inicia lista vazia
    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);

    char linha[512];
    while (fgets(linha, sizeof(linha), fp)) {
        // ignora linhas sem tab
        if (!strchr(linha, '\t')) 
            continue;

        // buffers temporários para separar campos
        int  idSensorLido;
        char designacaoLida[SENSOR_MAX_DESIGNACAO];
        char latitudeLida[SENSOR_MAX_LATITUDE];
        char longitudeLida[SENSOR_MAX_LONGITUDE];

        // Parsing com strtok por '\t'
        char *token = strtok(linha, "\t");
        if (!token) continue;
        idSensorLido = atoi(token);

        token = strtok(NULL, "\t");
        if (!token) continue;
        strncpy(designacaoLida, token, SENSOR_MAX_DESIGNACAO-1);
        designacaoLida[SENSOR_MAX_DESIGNACAO-1] = '\0';

        token = strtok(NULL, "\t");
        if (!token) continue;
        strncpy(latitudeLida, token, SENSOR_MAX_LATITUDE-1);
        latitudeLida[SENSOR_MAX_LATITUDE-1] = '\0';

        token = strtok(NULL, "\t\n\r");
        if (!token) continue;
        strncpy(longitudeLida, token, SENSOR_MAX_LONGITUDE-1);
        longitudeLida[SENSOR_MAX_LONGITUDE-1] = '\0';

        // aloca e preenche o novo nó
        NodeSensor *novo = malloc(sizeof(NodeSensor));
        if (!novo) {
            fprintf(stderr, "Erro Crítico: falha malloc em lerSensores()\n");
            fclose(fp);
            libertarListaSensoresParcial(listaSensores);
            return;
        }
        novo->sensor.idSensor     = idSensorLido;
        strcpy(novo->sensor.designacao, designacaoLida);
        strcpy(novo->sensor.latitude,    latitudeLida);
        strcpy(novo->sensor.longitude,   longitudeLida);

        // (opcional) confirmação no nó
        printf("   -> Confirmado Sensor: ID=%d, %s, %s, %s\n",
               novo->sensor.idSensor,
               novo->sensor.designacao,
               novo->sensor.latitude,
               novo->sensor.longitude);

        // insere no início da lista ligada
        novo->next = *listaSensores;
        *listaSensores = novo;
    }

    fclose(fp);
    printf(">> Ficheiro %s lido e dados de sensores carregados.\n", nomeFicheiro);
}

void lerDistancias(const char* nomeFicheiro, NodeDistancia** listaDistancias) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaDistancias = NULL;
        return;
    }

    *listaDistancias = NULL;
    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);

    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        // Se não tiver tabulação, ignora
        if (!strchr(linha, '\t')) 
            continue;

        // Extrai cada campo
        char *token = strtok(linha, "\t");
        if (!token) continue;
        int id1 = atoi(token);

        token = strtok(NULL, "\t");
        if (!token) continue;
        int id2 = atoi(token);

        token = strtok(NULL, "\t\n\r");
        if (!token) continue;
        float dist = atof(token);

        // Aloca novo nó
        NodeDistancia *no = malloc(sizeof(NodeDistancia));
        if (!no) {
            fprintf(stderr, "Erro crítico: falha malloc em lerDistancias()\n");
            fclose(fp);
            libertarListaDistanciasParcial(listaDistancias);
            return;
        }

        // Preenche campos
        no->distancia.idSensor1 = id1;
        no->distancia.idSensor2 = id2;
        no->distancia.distancia  = dist;

        // Confirmação (opcional)
        printf("   -> Confirmado Distancia: %d->%d = %.3f km\n",
               id1, id2, dist);

        // Insere no início da lista
        no->next = *listaDistancias;
        *listaDistancias = no;
    }

    fclose(fp);
    printf(">> Ficheiro %s lido e distâncias carregadas.\n", nomeFicheiro);
}

void lerPassagens(const char* nomeFicheiro, NodePassagem** listaPassagens) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaPassagens = NULL;
        return;
    }

    *listaPassagens = NULL;
    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);

    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        if (!strchr(linha, '\t')) 
            continue;

        char *token = strtok(linha, "\t");
        if (!token) continue;
        int idSensor = atoi(token);

        token = strtok(NULL, "\t");
        if (!token) continue;
        int idVeiculo = atoi(token);

        token = strtok(NULL, "\t");
        if (!token) continue;
        char dataHora[PASSAGEM_MAX_DATAHORA];
        strncpy(dataHora, token, PASSAGEM_MAX_DATAHORA-1);
        dataHora[PASSAGEM_MAX_DATAHORA-1] = '\0';

        token = strtok(NULL, "\t\n\r");
        if (!token) continue;
        int tipo = atoi(token);

        NodePassagem *no = malloc(sizeof(NodePassagem));
        if (!no) {
            fprintf(stderr, "Erro crítico: malloc em lerPassagens()\n");
            fclose(fp);
            libertarListaPassagensParcial(listaPassagens);
            return;
        }

        no->passagem.idSensor     = idSensor;
        no->passagem.idVeiculo    = idVeiculo;
        strcpy(no->passagem.dataHora, dataHora);
        no->passagem.tipoRegisto  = tipo;

        printf("   -> Confirmado Passagem: Sensor %d, Veículo %d, %s, Tipo=%s\n",
               idSensor, idVeiculo, dataHora,
               tipo==0 ? "entrada" : "saída");

        no->next = *listaPassagens;
        *listaPassagens = no;
    }

    fclose(fp);
    printf(">> Ficheiro %s lido e passagens carregadas.\n", nomeFicheiro);
}
