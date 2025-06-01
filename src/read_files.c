#include <stdio.h>      // fopen, fgets, fclose, fprintf, , printf
#include <stdlib.h>     // malloc, free, atoi
#include <string.h>     // strtok, strcpy, strncpy, strchr
#include "read_files.h" 
#include "data.h"      
#include "operations.h"

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
 */
void lerDonos(const char* nomeFicheiro, NodeDono** listaDonos) {

    // 1. Abrir o ficheiro
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaDonos = NULL;
        return;
    }

    // 2. Variáveis para armazenar temporariamente os dados lidos de CADA linha
    int numContribuinteLido;
    char nomeLido[DONO_MAX_NOME];
    char codigoPostalLido[DONO_MAX_CODIGOPOSTAL];
    char linha[512];

    printf("\n>> A ler o ficheiro %s...\n", nomeFicheiro);
    *listaDonos = NULL;

    // 3. Ler o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), fp)) {

        // Ignorar linhas em branco ou que não contenham o delimitador tab
        if (strchr(linha, '\t') == NULL) {
            continue;
        }
        // --- Parsing da Linha ---
        char *token;

        // <numContribuinte>
        token = strtok(linha, "\t");
        if (token == NULL) continue;
        numContribuinteLido = atoi(token);

        // <nome>
        token = strtok(NULL, "\t");
        if (token == NULL) continue;
        strncpy(nomeLido, token, DONO_MAX_NOME - 1);
        nomeLido[DONO_MAX_NOME - 1] = '\0';

        // <codPostal>
        token = strtok(NULL, "\t\n\r");
        if (token == NULL) continue;
        strncpy(codigoPostalLido, token, DONO_MAX_CODIGOPOSTAL - 1);
        codigoPostalLido[DONO_MAX_CODIGOPOSTAL - 1] = '\0';

        // --- Inserção na Lista Ligada ---

        NodeDono* novoNode = (NodeDono*)malloc(sizeof(NodeDono));
        if (novoNode == NULL) {
            fprintf(stderr, "Erro Crítico: Falha ao alocar memória para novo Dono.\n");
            fclose(fp); 
            fprintf(stderr, " -> A libertar memória já alocada...\n");
            libertarListaDonosParcial(listaDonos);
            return; 
        }

        novoNode->dono.numeroContribuinte = numContribuinteLido;
        strcpy(novoNode->dono.nome, nomeLido);
        strcpy(novoNode->dono.codigoPostal, codigoPostalLido);

        novoNode->next = *listaDonos;
        *listaDonos = novoNode;

    } 

    fclose(fp);
    printf(">> Ficheiro %s lido e dados dos donos carregados para a lista ligada.\n", nomeFicheiro);
}
/**
 * @brief  Ordena um array de donos alfabeticamente pelo nome
 * 
 * @param donos 
 * @param total 
 */
void ordenar_por_nome(Dono *donos, int total){
    for(int i = 0; i < total - 1; i++){
        for(int j = 0; j < total - i - 1; j++){
            if ( strcmp(donos[j].nome, donos[j+1].nome) > 0 ) {
                Dono tmp = donos[j];
                donos[j] = donos[j + 1];
                donos[j + 1] = tmp;
            }
        }
    }
}

/**
 * @brief Lê os donos a partir de um ficheiro, ordena-os por nome e imprime no ecrã.
 * 
 * @param ficheiro 
 */
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

/**
 * @brief Lê os dados dos carros do ficheiro especificado e preenche a lista ligada.
 * 
 * @param nomeFicheiro 
 * @param listaCarros 
 */
void lerCarros(const char* nomeFicheiro, NodeCarro** listaCarros) {
    // 1. Abrir o ficheiro
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir ficheiro: %s\n", nomeFicheiro);
        *listaCarros = NULL;
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

        // --- Inserção na Lista Ligada ---

        NodeCarro* novoNode = (NodeCarro*)malloc(sizeof(NodeCarro));
        if (novoNode == NULL) {
            fprintf(stderr, "Erro Crítico: Falha ao alocar memória para novo Carro.\n");
            fclose(fp);
            fprintf(stderr, " -> A libertar memória já alocada...\n");
            libertarListaCarrosParcial(listaCarros); // Libertar memória
            return;
        }

        strcpy(novoNode->carro.matricula, matriculaLida);
        strcpy(novoNode->carro.marca, marcaLida);
        strcpy(novoNode->carro.modelo, modeloLido);  
        novoNode->carro.ano = anoLido;
        novoNode->carro.donoContribuinte = donoContribuinteLido;
        novoNode->carro.idVeiculo = idVeiculoLido;

        novoNode->next = *listaCarros;
        *listaCarros = novoNode;

    }

    fclose(fp);
    printf(">> Ficheiro %s lido e dados dos carros carregados.\n", nomeFicheiro);
}


/**
 * @brief Lê os dados dos sensores a partir de um ficheiro e constrói uma lista ligada.
 * 
 * @param nomeFicheiro 
 * @param listaSensores 
 */
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

        int  idSensorLido;
        char designacaoLida[SENSOR_MAX_DESIGNACAO];
        char latitudeLida[SENSOR_MAX_LATITUDE];
        char longitudeLida[SENSOR_MAX_LONGITUDE];

        // <idSensor>
        char *token = strtok(linha, "\t");
        if (!token) continue;
        idSensorLido = atoi(token);

        // <designacao>
        token = strtok(NULL, "\t");
        if (!token) continue;
        strncpy(designacaoLida, token, SENSOR_MAX_DESIGNACAO-1);
        designacaoLida[SENSOR_MAX_DESIGNACAO-1] = '\0';

        // <latitude>
        token = strtok(NULL, "\t");
        if (!token) continue;
        strncpy(latitudeLida, token, SENSOR_MAX_LATITUDE-1);
        latitudeLida[SENSOR_MAX_LATITUDE-1] = '\0';

        // <longitude>
        token = strtok(NULL, "\t\n\r");
        if (!token) continue;
        strncpy(longitudeLida, token, SENSOR_MAX_LONGITUDE-1);
        longitudeLida[SENSOR_MAX_LONGITUDE-1] = '\0';

        NodeSensor *novo = malloc(sizeof(NodeSensor));
        if (!novo) {
            fprintf(stderr, "Erro Crítico: falha malloc em lerSensores()\n");
            fclose(fp);
            libertarListaSensoresParcial(listaSensores);
            return;
        }
        novo->sensor.idSensor = idSensorLido;
        strcpy(novo->sensor.designacao, designacaoLida);
        strcpy(novo->sensor.latitude,    latitudeLida);
        strcpy(novo->sensor.longitude,   longitudeLida);

        novo->next = *listaSensores;
        *listaSensores = novo;
    }

    fclose(fp);
    printf(">> Ficheiro %s lido e dados de sensores carregados.\n", nomeFicheiro);
}
/**
 * @brief Lê distâncias entre sensores de um ficheiro e armazena numa lista ligada.
 * 
 * @param nomeFicheiro 
 * @param listaDistancias 
 */
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

        NodeDistancia *no = malloc(sizeof(NodeDistancia));
        if (!no) {
            fprintf(stderr, "Erro crítico: falha malloc em lerDistancias()\n");
            fclose(fp);
            libertarListaDistanciasParcial(listaDistancias);
            return;
        }

        no->distancia.idSensor1 = id1;
        no->distancia.idSensor2 = id2;
        no->distancia.distancia  = dist;

        no->next = *listaDistancias;
        *listaDistancias = no;
    }

    fclose(fp);
    printf(">> Ficheiro %s lido e distâncias carregadas.\n", nomeFicheiro);
}


// Pool de nós do tipo NodePassagem
static NodePassagem *passPool = NULL;
static size_t poolPos = 0, poolSize = 0;

// Inicializa o pool para N nós de NodePassagem
/**
 * @brief Inicializa um pool de memória para armazenar nós de passagens.
 * 
 * @param N 
 */
static void pool_init_passagens(size_t N) {
    passPool = malloc(N * sizeof(*passPool));
    poolPos  = 0;
    poolSize = N;
}

/**
 * @brief Aloca um novo nó do pool de passagens.
 * 
 * @return NodePassagem* 
 */
static NodePassagem *pool_alloc_passagem(void) {
    if (poolPos >= poolSize) return NULL;
    return &passPool[poolPos++];
}

/**
 * @brief Lê os registos de passagens de um ficheiro e armazena-os numa lista ligada.
 * Usa um pool para alocação eficiente de memória.
 * 
 * @param nomeFicheiro 
 * @param listaPassagens 
 */
void lerPassagens(const char* nomeFicheiro, NodePassagem** listaPassagens) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (!fp) {
        fprintf(stderr, "Erro ao abrir %s\n", nomeFicheiro);
        *listaPassagens = NULL;
        return;
    }

    // 1) Contar linhas úteis
    size_t lines = 0;
    char buf[256];
    while (fgets(buf, sizeof buf, fp))
       if (strchr(buf, '\t')) lines++;
    rewind(fp);

    // 2) Prepara pool
    pool_init_passagens(lines);

    *listaPassagens = NULL;
    NodePassagem *tail = NULL;

    // 3) Faz o parsing e insere em O(1) do pool
    while (fgets(buf, sizeof buf, fp)) {
        if (!strchr(buf, '\t')) continue;
        char *tok = strtok(buf, "\t");
        int s = tok ? atoi(tok) : 0;
        tok = strtok(NULL, "\t");     int v = tok ? atoi(tok) : 0;
        tok = strtok(NULL, "\t");     char dt[PASSAGEM_MAX_DATAHORA] = "";
                                       if (tok) strncpy(dt, tok, sizeof dt-1);
        tok = strtok(NULL, "\t\n");   int t = tok ? atoi(tok) : 0;

        NodePassagem *no = pool_alloc_passagem();
        no->passagem.idSensor     = s;
        no->passagem.idVeiculo    = v;
        strcpy(no->passagem.dataHora, dt);
        no->passagem.tipoRegisto  = t;
        no->passagem.ts = parseTimestamp(no->passagem.dataHora);
        no->next = NULL;

        if (!*listaPassagens) {
            *listaPassagens = tail = no;
        } else {
            tail->next = no;
            tail = no;
        }
    }
    fclose(fp);
    printf("Lidas %zu passagens (pool de %zu nós).\n", poolPos, poolSize);
}

