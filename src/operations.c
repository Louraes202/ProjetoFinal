// operations.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

// --- Donos ---
/**
 * @brief Esta função percorre a lista de donos e imprime os dados de cada um deles no terminal.
 * Caso a lista esteja vazia, uma mensagem apropriada será exibida.
 * 
 * @param lista 
 */
void imprimirListaDonos(NodeDono* lista) {
    printf("\n--- Lista de Donos ---\n");
    if (!lista) {
        printf("Nenhum dono carregado.\n");
        return;
    }
    int i = 1;
    for (NodeDono* p = lista; p; p = p->next, i++) {
        printf("%2d) NIF=%d | Nome=\"%s\" | CP=%s\n",
               i,
               p->dono.numeroContribuinte,
               p->dono.nome,
               p->dono.codigoPostal);
    }
}

// --- Carros ---

/**
 * @brief Esta função percorre a lista de carros e imprime os dados de cada carro no terminal.
 * Se a lista estiver vazia, será impressa uma mensagem de aviso.
 * 
 * @param lista 
 */
void imprimirListaCarros(NodeCarro* lista) {
    printf("\n--- Lista de Carros ---\n");
    if (!lista) {
        printf("Nenhum carro carregado.\n");
        return;
    }
    int i = 1;
    for (NodeCarro* p = lista; p; p = p->next, i++) {
        printf("%2d) Mat=%s | Marca=%s | Modelo=%s | Ano=%d | DonoNIF=%d | ID=%d\n",
               i,
               p->carro.matricula,
               p->carro.marca,
               p->carro.modelo,
               p->carro.ano,
               p->carro.donoContribuinte,
               p->carro.idVeiculo);
    }
}

// --- Sensores ---

/**
 * @brief  A função imprime os pares de sensores e a distância entre eles. 
 * Caso a lista esteja vazia, informa o usuário.
 * 
 * @param lista 
 */
void imprimirListaSensores(NodeSensor* lista) {
    printf("\n--- Lista de Sensores ---\n");
    if (!lista) {
        printf("Nenhum sensor carregado.\n");
        return;
    }
    int i = 1;
    for (NodeSensor* p = lista; p; p = p->next, i++) {
        printf("%2d) ID=%d | %s | Lat=%s | Lon=%s\n",
               i,
               p->sensor.idSensor,
               p->sensor.designacao,
               p->sensor.latitude,
               p->sensor.longitude);
    }
}

// --- Distâncias ---

/**
 * @brief A função exibe o histórico de passagens dos veículos pelos sensores,
 * incluindo o tipo de registo ("entrada" ou "saída").
 * 
 * @param lista 
 */
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

// --- Passagens ---

/**
 * @brief Percorre a lista e desaloca cada nó, liberando toda a memória associada.
 * Ao final, define o ponteiro da lista como NULL.
 * 
 * @param lista 
 */
void imprimirListaPassagens(NodePassagem* lista) {
    printf("\n--- Lista de Passagens ---\n");
    if (!lista) {
        printf("Nenhuma passagem carregada.\n");
        return;
    }
    int i = 1;
    for (NodePassagem* p = lista; p; p = p->next, i++) {
        printf("%2d) SensorID=%d | VeiculoID=%d | DataHora=\"%s\" | Tipo=%s\n",
               i,
               p->passagem.idSensor,
               p->passagem.idVeiculo,
               p->passagem.dataHora,
               p->passagem.tipoRegisto == 0 ? "entrada" : "saída");
    }
}

// --- libertar Donos ---

/**
 * @brief Liberta toda a memória da lista ligada de carros e define o ponteiro como NULL.
 * 
 * @param lista 
 */
void libertarListaDonos(NodeDono** lista) {
    NodeDono *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Dono libertada.\n", cont);
}

// --- libertar Carros ---

/**
 * @brief A função percorre a lista e desaloca cada nó da estrutura ligada de sensores.
 * 
 * @param lista 
 */
void libertarListaCarros(NodeCarro** lista) {
    NodeCarro *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Carro libertada.\n", cont);
}

// --- libertar Sensores ---

/**
 * @brief Remove cada nó da lista de distâncias e libera a memória.
 * 
 * @param lista 
 */
void libertarListaSensores(NodeSensor** lista) {
    NodeSensor *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Sensor libertada.\n", cont);
}

// --- libertar Distâncias ---

/**
 * @brief Desaloca cada nó da lista ligada de passagens, limpando completamente a memória usada.
 * 
 * @param lista 
 */
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

// --- libertar Passagens ---

/**
 * @brief Cada nó armazena um ponteiro para uma passagem e ponteiros para os nós esquerdo e direito.
 * 
 * @param lista 
 */
void libertarListaPassagens(NodePassagem** lista) {
    NodePassagem *atual = *lista, *seguinte;
    int cont = 0;
    while (atual) {
        seguinte = atual->next;
        free(atual);
        atual = seguinte;
        cont++;
    }
    *lista = NULL;
    printf("\nMemória de %d nós Passagem libertada.\n", cont);
}

typedef struct TreeNode {
    Passagem *p;
    struct TreeNode *l, *r;
} TreeNode;

/**
 * @brief A função insere a nova passagem de forma ordenada na árvore binária,
 * usando o id do veículo como chave de ordenação.
 * 
 * @param root 
 * @param p 
 */
void insertTree(TreeNode **root, Passagem *p) {
if (!*root) {
    *root = malloc(sizeof **root);
    (*root)->p = p; (*root)->l = (*root)->r = NULL;
} else if (p->idVeiculo < (*root)->p->idVeiculo)
    insertTree(&(*root)->l, p);
else
    insertTree(&(*root)->r, p);
}

// Funções de registar

/**
 * @brief Função de registar dono
 * 
 * @param listaDonos
 */
void registarDono(NodeDono** listaDonos) {
    int nif;
    char nome[DONO_MAX_NOME];
    char cp[DONO_MAX_CODIGOPOSTAL];
    printf("NIF: ");         
    scanf("%d", &nif);
    printf("Nome: ");        
    scanf(" %199[^\n]", nome);
    printf("Código postal: "); 
    scanf(" %9[^\n]", cp);

    NodeDono *novo = malloc(sizeof(NodeDono));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo->dono.numeroContribuinte = nif;
    strncpy(novo->dono.nome, nome, DONO_MAX_NOME);
    strncpy(novo->dono.codigoPostal, cp, DONO_MAX_CODIGOPOSTAL);

    novo->next = *listaDonos;
    *listaDonos = novo;

}

/**
 * @brief Função de registar carro
 * 
 * @param listaCarros
 */
void registarCarro(NodeCarro** listaCarros) {
    char matricula[CARRO_MAX_MATRICULA];
    char marca[CARRO_MAX_MARCA];
    char modelo[CARRO_MAX_MODELO];
    int ano, dono, id;

    printf("Matrícula: ");
    scanf(" %19[^\n]", matricula);
    printf("Marca: ");
    scanf(" %49[^\n]", marca);
    printf("Modelo: ");
    scanf(" %49[^\n]", modelo);
    printf("Ano: ");
    scanf("%d", &ano);
    printf("Dono (NIF): ");
    scanf("%d", &dono);
    printf("ID veículo: ");
    scanf("%d", &id);

    NodeCarro *novo = malloc(sizeof(NodeCarro));
    if (!novo) return;

    strncpy(novo->carro.matricula, matricula, CARRO_MAX_MATRICULA);
    strncpy(novo->carro.marca,     marca,     CARRO_MAX_MARCA);
    strncpy(novo->carro.modelo,    modelo,    CARRO_MAX_MODELO);
    novo->carro.ano = ano;
    novo->carro.donoContribuinte = dono;
    novo->carro.idVeiculo = id;

    novo->next = *listaCarros;
    *listaCarros = novo;
}



/**
 * @brief Função de registar sensor
 * 
 * @param listaSensores
 */

void registarSensor(NodeSensor** listaSensores) {
    int id;
    char designacao[SENSOR_MAX_DESIGNACAO];
    char lat[SENSOR_MAX_LATITUDE];
    char lon[SENSOR_MAX_LONGITUDE];

    printf("ID Sensor: ");
    scanf("%d", &id);
    printf("Designação: ");
    scanf(" %99[^\n]", designacao);
    printf("Latitude (texto): ");
    scanf(" %49[^\n]", lat);
    printf("Longitude (texto): ");
    scanf(" %49[^\n]", lon);

    NodeSensor *novo = malloc(sizeof(NodeSensor));
    if (!novo) return;

    novo->sensor.idSensor = id;
    strncpy(novo->sensor.designacao, designacao, SENSOR_MAX_DESIGNACAO);
    strncpy(novo->sensor.latitude, lat, SENSOR_MAX_LATITUDE);
    strncpy(novo->sensor.longitude, lon, SENSOR_MAX_LONGITUDE);

    novo->next = *listaSensores;
    *listaSensores = novo;
}

/**
 * @brief Função de registar distância
 * 
 * @param listaDistancias
 */
void registarDistancia(NodeDistancia** listaDistancias) {
    int a, b;
    float d;

    printf("Sensor A (ID): ");
    scanf("%d", &a);
    printf("Sensor B (ID): ");
    scanf("%d", &b);
    printf("Distância (km): ");
    scanf("%f", &d);

    NodeDistancia *novo = malloc(sizeof(NodeDistancia));
    if (!novo) return;

    novo->distancia.idSensor1 = a;
    novo->distancia.idSensor2 = b;
    novo->distancia.distancia    = d;

    novo->next = *listaDistancias;
    *listaDistancias = novo;
}

/**
 * @brief Função de registar passagem
 * 
 * @param listaPassagens
 */
void registarPassagem(NodePassagem** listaPassagens) {
    int idS, idV, tipo;
    char dataHora[PASSAGEM_MAX_DATAHORA];

    printf("ID Sensor: ");
    scanf("%d", &idS);
    printf("ID Veículo: ");
    scanf("%d", &idV);
    printf("Data e hora (texto): ");
    scanf(" %19[^\n]", dataHora);
    printf("Tipo (0=entrada,1=saída): ");
    scanf("%d", &tipo);

    NodePassagem *novo = malloc(sizeof(NodePassagem));
    if (!novo) return;

    novo->passagem.idSensor    = idS;
    novo->passagem.idVeiculo  = idV;
    strncpy(novo->passagem.dataHora, dataHora, PASSAGEM_MAX_DATAHORA);
    novo->passagem.tipoRegisto = tipo;

    novo->next = *listaPassagens;
    *listaPassagens = novo;
}