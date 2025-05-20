// operations.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ctype.h>
#include <time.h>
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
    for (NodeDono* p = lista; p; p = p->next, i++) { // ALTERAR: ordenar implicitamente por nome ou nif (parametro)
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


// Funçao para determinar a memoria ocupada por todas as estruturas do programa
size_t calcularMemoriaTotal(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, NodeDistancia* listaDistancias, NodePassagem* listaPassagens) {
    size_t memoriaTotal = 0;
    for (NodeDono* p = listaDonos; p; p = p->next) {
        memoriaTotal += sizeof(NodeDono);
    }

    // Calcular memória ocupada pela lista de carros
    for (NodeCarro* p = listaCarros; p; p = p->next) {
        memoriaTotal += sizeof(NodeCarro);
    }

    // Calcular memória ocupada pela lista de sensores
    for (NodeSensor* p = listaSensores; p; p = p->next) {
        memoriaTotal += sizeof(NodeSensor);
    }

    // Calcular memória ocupada pela lista de distâncias
    for (NodeDistancia* p = listaDistancias; p; p = p->next) {
        memoriaTotal += sizeof(NodeDistancia);
    }

    // Calcular memória ocupada pela lista de passagens
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        memoriaTotal += sizeof(NodePassagem);
    }

    return memoriaTotal;
}



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

void ordenar_donos_NIF(Dono *dono, int total) {
    for (int i = 0; i < total - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < total; j++) {
            if (dono[j].numeroContribuinte < dono[min_index].numeroContribuinte) {
                min_index = j;
            }
        }
        if (min_index != i) {
            Dono temp = dono[i];
            dono[i] = dono[min_index];
            dono[min_index] = temp;
        }
    }
}

void ordenar_carros(Carro *carros, int total, int (*comparar)(const Carro *, const Carro *)) {
    for (int i = 0; i < total - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < total; j++) {
            if (comparar(&carros[j], &carros[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            Carro temp = carros[i];
            carros[i] = carros[min_index];
            carros[min_index] = temp;
        }
    }
}

int comparar_matricula(const Carro *a, const Carro *b) {
    return strcmp(a->matricula, b->matricula);
}

int comparar_marca(const Carro *a, const Carro *b) {
    return strcmp(a->marca, b->marca);
}

int comparar_modelo(const Carro *a, const Carro *b) {
    return strcmp(a->modelo, b->modelo);
}

int verificacao_periodo(const char *dataHora, const char *inicio, const char *fim) {
    return strcmp(dataHora, inicio) >= 0 && strcmp(dataHora, fim) <= 0;
}

int veiculo_ja_adicionado(const int lista[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (lista[i] == id) {
            return 1;
        }
    }
    return 0;
}

void mostrar_veiculos_periodo(Passagem passagens[], int total_passagens, Carro carros[], int total_carros) {
    char inicio[PASSAGEM_MAX_DATAHORA];
    char fim[PASSAGEM_MAX_DATAHORA];

    printf("Introduza a data/hora de INÍCIO (formato DD-MM-AAAA_HH:MM:SS.xxx): ");
    scanf(" %24[^\n]", inicio);

    printf("Introduza a data/hora de FIM (formato DD-MM-AAAA_HH:MM:SS.xxx): ");
    scanf(" %24[^\n]", fim);

    int ids_unicos[MAX_CARROS];
    int total_ids = 0;

    for (int i = 0; i < total_passagens; i++) {
        if (verificacao_periodo(passagens[i].dataHora, inicio, fim)) {
            int id = passagens[i].idVeiculo;
            if (!veiculo_ja_adicionado(ids_unicos, total_ids, id)) {
                ids_unicos[total_ids++] = id;
            }
        }
    }

    Carro encontrados[MAX_CARROS];
    int totalEncontrados = 0;
    for (int i = 0; i < total_ids; i++) {
        for (int j = 0; j < total_carros; j++) {
            if (carros[j].idVeiculo == ids_unicos[i]) {
                encontrados[totalEncontrados++] = carros[j];
                break;
            }
        }
    }

    ordenar_carros(encontrados, totalEncontrados, comparar_matricula);

    printf("\n=== Veículos que circularam entre %s e %s ===\n", inicio, fim);
    for (int i = 0; i < totalEncontrados; i++) {
        printf("Matrícula: %s\tMarca: %s\tModelo: %s\n",
               encontrados[i].matricula,
               encontrados[i].marca,
               encontrados[i].modelo);
    }

    if (totalEncontrados == 0) {
        printf("Nenhum veículo encontrado neste intervalo.\n");
    }
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

/**
 * @brief Verifica se um NIF (9 dígitos) é válido (apenas formato).
 */
bool validarNIF(int nif) {
    return nif >= 100000000 && nif <= 999999999;
}

/**
 * @brief Verifica se a matrícula portuguesa está num dos formatos válidos:
 *   AA-00-00 ou 00-00-AA (2 letras/2 dígitos/2 dígitos).
 */
bool validarMatricula(const char *m) {
    if (strlen(m) != 8 || m[2] != '-' || m[5] != '-') return false;
    bool isLetDig = isalpha(m[0]) && isalpha(m[1]) &&
                    isdigit(m[3]) && isdigit(m[4]) &&
                    isdigit(m[6]) && isdigit(m[7]);
    bool isDigLet = isdigit(m[0]) && isdigit(m[1]) &&
                    isdigit(m[3]) && isdigit(m[4]) &&
                    isalpha(m[6]) && isalpha(m[7]);
    return isLetDig || isDigLet;
}

/**
 * @brief Verifica se o código postal português tem o formato "XXXX-XXX"
 *        onde X é dígito [0-9].
 * @param cp string terminada em '\0'
 * @return true se corresponder ao padrão, false caso contrário
 */
bool validarCodigoPostal(const char *cp) {
    // comprimento fixo: 8 caracteres + '\0'
    if (strlen(cp) != 8) return false;
    // posições 0..3 devem ser dígitos
    for (int i = 0; i < 4; i++)
        if (!isdigit((unsigned char)cp[i]))
            return false;
    // posição 4 deve ser hífen
    if (cp[4] != '-') return false;
    // posições 5..7 devem ser dígitos
    for (int i = 5; i < 8; i++)
        if (!isdigit((unsigned char)cp[i]))
            return false;
    return true;
}

// Função personalizada para analisar data e hora no formato "dd-mm-yyyy HH:MM:SS"
int parseTimestampCustom(const char *dataHora, struct tm *tm) {
    // Inicializa a estrutura tm com zeros
    memset(tm, 0, sizeof(struct tm));

    // Analisa a string no formato "dd-mm-yyyy HH:MM:SS"
    if (sscanf(dataHora, "%d-%d-%d %d:%d:%d",
               &tm->tm_mday, &tm->tm_mon, &tm->tm_year,
               &tm->tm_hour, &tm->tm_min, &tm->tm_sec) != 6) {
        return 0; // Retorna 0 se a análise falhar
    }

    // Ajusta os valores para o formato esperado pela struct tm
    tm->tm_mon -= 1;  // Meses vão de 0 a 11
    tm->tm_year -= 1900; // Anos são contados a partir de 1900

    // Validações adicionais para garantir que o timestamp é válido
    if (tm->tm_year < 0 || tm->tm_mon < 0 || tm->tm_mon > 11 ||
        tm->tm_mday < 1 || tm->tm_mday > 31 || tm->tm_hour < 0 ||
        tm->tm_hour > 23 || tm->tm_min < 0 || tm->tm_min > 59 ||
        tm->tm_sec < 0 || tm->tm_sec > 59) {
        return 0; // Retorna 0 se os valores estiverem fora dos limites
    }

    return 1; // Retorna 1 se a análise for bem-sucedida
}

time_t parseTimestamp(const char *dataHora) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    // Use a função personalizada para analisar a data e hora
    if (!parseTimestampCustom(dataHora, &tm)) {
        fprintf(stderr, "Erro: formato de data/hora inválido: %s\n", dataHora);
        return -1; // Retorna -1 em caso de erro
    }

    return mktime(&tm); // Converte struct tm para time_t
}

// Função para obter a distância entre dois sensores
double obterDistancia(NodeDistancia* lista, int id1, int id2) {
    for (NodeDistancia* d = lista; d; d = d->next) {
        if ((d->distancia.idSensor1 == id1 && d->distancia.idSensor2 == id2) ||
            (d->distancia.idSensor1 == id2 && d->distancia.idSensor2 == id1)) {
            return d->distancia.distancia;
        }
    }
    return 0.0;
}

// Função de comparação para qsort (ordem decrescente)
int cmpVeiculoRanking(const void *a, const void *b) {
    double diff = ((KmVeiculo*)b)->km - ((KmVeiculo*)a)->km;
    return (diff > 0) - (diff < 0);
}

// Definição da struct Infracao
typedef struct {
    char matricula[CARRO_MAX_MATRICULA];
    double velocidadeMedia;
} Infracao;


// Função para liberar a árvore binária
void liberarArvore(TreeNodeInfracao *root) {
    if (!root) return;
    liberarArvore(root->left);
    liberarArvore(root->right);
    free(root);
}

// Função para inserir na árvore binária
void inserirInfracao(TreeNodeInfracao **root, const char *matricula, double velocidadeMedia) {
    if (!*root) {
        *root = malloc(sizeof(TreeNodeInfracao));
        strncpy((*root)->matricula, matricula, CARRO_MAX_MATRICULA);
        (*root)->velocidadeMedia = velocidadeMedia;
        (*root)->left = (*root)->right = NULL;
    } else if (velocidadeMedia > (*root)->velocidadeMedia) {
        inserirInfracao(&(*root)->left, matricula, velocidadeMedia);
    } else {
        inserirInfracao(&(*root)->right, matricula, velocidadeMedia);
    }
}

    // Função para percorrer a árvore binária em ordem decrescente
void percorrerArvore(TreeNodeInfracao *root, Infracao *infracoes, int *index) {
    if (!root) return;
    percorrerArvore(root->left, infracoes, index);
    strncpy(infracoes[*index].matricula, root->matricula, CARRO_MAX_MATRICULA);
    infracoes[*index].velocidadeMedia = root->velocidadeMedia;
    (*index)++;
    percorrerArvore(root->right, infracoes, index);
}

// Função para listar infrações de velocidade com menu de páginas (otimizada com árvore binária)
// A função está a funcionar corretamente, mas pode ser melhorada a nível de eficiência
void listarInfracoes(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim) {

    TreeNodeInfracao *root = NULL;

    // 1. Processar passagens e calcular infrações
    printf("A carregar");
    int loadingDots = 0;
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        // Atualizar mensagem de carregamento
        printf("\rA carregar%s", (loadingDots++ % 4 == 0) ? "." : (loadingDots % 4 == 1) ? ".." : (loadingDots % 4 == 2) ? "..." : "....");
        fflush(stdout);

        time_t t = parseTimestamp(p->passagem.dataHora);
        if (t < inicio || t > fim) continue;

        int idV = p->passagem.idVeiculo;
        int idS = p->passagem.idSensor;
        int idS_ant = -1;
        time_t t_ant = -1;

        NodePassagem* ant = p->next;
        while (ant) {
            if (ant->passagem.idVeiculo == idV) {
                idS_ant = ant->passagem.idSensor;
                t_ant = parseTimestamp(ant->passagem.dataHora);
                break;
            }
            ant = ant->next;
        }
        if (idS_ant == -1 || t_ant == -1) continue;

        double dist = obterDistancia(listaDistancias, idS_ant, idS);
        double tempoHoras = difftime(t, t_ant) / 3600.0; // Converter tempo para horas
        if (tempoHoras <= 0) continue;

        double velocidadeMedia = dist / tempoHoras;
        if (velocidadeMedia > 120.0) {
            char matricula[CARRO_MAX_MATRICULA] = "";
            for (NodeCarro* c = listaCarros; c; c = c->next) {
                if (c->carro.idVeiculo == idV) {
                    strncpy(matricula, c->carro.matricula, CARRO_MAX_MATRICULA);
                    break;
                }
            }
            if (strlen(matricula) > 0) {
                inserirInfracao(&root, matricula, velocidadeMedia);
            }
        }
    }
    printf("\n");

    // 2. Transferir dados da árvore para um array
    int maxInfracoes = 1000; // Ajustar conforme necessário
    Infracao *infracoes = calloc(maxInfracoes, sizeof(Infracao));
    int nInfracoes = 0;
    percorrerArvore(root, infracoes, &nInfracoes);

    // 3. Paginação e exibição
    int pageSize = 10;
    int currentPage = 0;
    char opcao;

    do {
        printf("\n=== Listagem de Infrações (Página %d) ===\n", currentPage + 1);
        int start = currentPage * pageSize;
        int end = start + pageSize;
        if (end > nInfracoes) end = nInfracoes;

        for (int i = start; i < end; i++) {
            printf("%2d) Veículo com matrícula %s excedeu a velocidade média (%.2f km/h).\n",
                   i + 1, infracoes[i].matricula, infracoes[i].velocidadeMedia);
        }

        struct tm *tmInicio = localtime(&inicio);
        struct tm *tmFim = localtime(&fim);
        char inicioStr[20], fimStr[20];
        strftime(inicioStr, sizeof(inicioStr), "%d-%m-%Y %H:%M:%S", tmInicio);
        strftime(fimStr, sizeof(fimStr), "%d-%m-%Y %H:%M:%S", tmFim);
        printf("\nForam encontradas %d infrações no período entre %s e %s\n", nInfracoes, inicioStr, fimStr);

        printf("\nOpções:\n");
        printf("n - Próxima página\n");
        printf("p - Página anterior\n");
        printf("t - Alterar número de infrações por página (atual: %d)\n", pageSize);
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'n' && end < nInfracoes) {
            currentPage++;
        } else if (opcao == 'p' && currentPage > 0) {
            currentPage--;
        } else if (opcao == 't') {
            printf("Digite o novo número de infrações por página: ");
            scanf("%d", &pageSize);
            if (pageSize <= 0) {
                printf("Número inválido. Mantendo o valor anterior.\n");
                pageSize = 10;
            } else if (pageSize > nInfracoes) {
                printf("O número inserido (%d) é superior ao número de infrações encontradas (%d).\n", pageSize, nInfracoes);
                pageSize = nInfracoes;
            }
            currentPage = 0; // Reinicia na primeira página
        } else if (opcao != 's') {
            printf("Opção inválida.\n");
        }
    } while (opcao != 's');

    free(infracoes);

    liberarArvore(root);
}

// Esboço da função rankingVeiculos com paginação e busca por ID
void rankingVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim) {
    int maxVeiculos = 40000; // Ajustar conforme necessário
    KmVeiculo *ranking = calloc(maxVeiculos, sizeof(KmVeiculo));
    int nVeiculos = 0;

    // 1. Processar passagens e calcular distâncias
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        time_t t = parseTimestamp(p->passagem.dataHora);
        if (t < inicio || t > fim) continue;

        int idV = p->passagem.idVeiculo;
        int idS = p->passagem.idSensor;
        int idS_ant = -1;

        NodePassagem* ant = p->next;
        while (ant) {
            if (ant->passagem.idVeiculo == idV) {
                idS_ant = ant->passagem.idSensor;
                break;
            }
            ant = ant->next;
        }
        if (idS_ant == -1) continue;

        int idx = -1;
        for (int i = 0; i < nVeiculos; i++) {
            if (ranking[i].idVeiculo == idV) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            idx = nVeiculos++;
            ranking[idx].idVeiculo = idV;
            ranking[idx].km = 0.0;
        }

        double dist = obterDistancia(listaDistancias, idS_ant, idS);
        ranking[idx].km += dist;
    }

    qsort(ranking, nVeiculos, sizeof(KmVeiculo), cmpVeiculoRanking);

    // 2. Paginação e busca
    int pageSize = 10;
    int currentPage = 0;
    char opcao;

    do {
        printf("\n=== Ranking de circulação (Página %d) ===\n", currentPage + 1);
        int start = currentPage * pageSize;
        int end = start + pageSize;
        if (end > nVeiculos) end = nVeiculos;

        for (int i = start; i < end; i++) {
            printf("%2d) Veículo %d: %.2f km\n", i + 1, ranking[i].idVeiculo, ranking[i].km);
        }

        struct tm *tmInicio = localtime(&inicio);
        struct tm *tmFim = localtime(&fim);
        char inicioStr[20], fimStr[20];
        strftime(inicioStr, sizeof(inicioStr), "%d-%m-%Y %H:%M:%S", tmInicio);
        strftime(fimStr, sizeof(fimStr), "%d-%m-%Y %H:%M:%S", tmFim);
        printf("\nPassaram %d veículos na estrada entre %s e %s\n", nVeiculos, inicioStr, fimStr);

        printf("\nOpções:\n");
        printf("n - Próxima página\n");
        printf("p - Página anterior\n");
        printf("b - Procurar veículo por ID\n");
        printf("t - Alterar número de veículos por página (atual: %d)\n", pageSize);
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);

        if (opcao == 'n' && end < nVeiculos) {
            currentPage++;
        } else if (opcao == 'p' && currentPage > 0) {
            currentPage--;
        } else if (opcao == 'b') {
            int idBusca;
            printf("Digite o ID do veículo: ");
            scanf("%d", &idBusca);
            int encontrado = 0;
            for (int i = 0; i < nVeiculos; i++) {
                if (ranking[i].idVeiculo == idBusca) {
                    printf("Veículo %d está na posição %d com %.2f km\n", idBusca, i + 1, ranking[i].km);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                printf("Veículo com ID %d não encontrado no ranking.\n", idBusca);
            }
            printf("Pressione Enter para continuar...");
            while (getchar() != '\n'); // Limpa o buffer
            getchar(); // Aguarda o Enter
        } else if (opcao == 't') {
            printf("Digite o novo número de veículos por página: ");
            scanf("%d", &pageSize);
            if (pageSize <= 0) {
                printf("Número inválido. Mantendo o valor anterior.\n");
                pageSize = 10;
            } else if (pageSize > nVeiculos) {
                printf("O número inserido (%d) é superior ao número de veículos que passaram (%d).\n", pageSize, nVeiculos);
                pageSize = nVeiculos;
            }
            currentPage = 0; // Reinicia na primeira página
        } else if (opcao != 's') {
            printf("Opção inválida.\n");
        }
    } while (opcao != 's');

    free(ranking);
}


// Função de comparação para qsort (ordem decrescente por quilómetros)
int cmpMarcaRanking(const void *a, const void *b) {
    double diff = ((KmMarca*)b)->km - ((KmMarca*)a)->km;
    return (diff > 0) - (diff < 0);
}

// Função para calcular o ranking por marca
void rankingPorMarca(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim) {
    int maxMarcas = 100; // Ajustar conforme necessário
    KmMarca *ranking = calloc(maxMarcas, sizeof(KmMarca));
    int nMarcas = 0;

    // 1. Processar passagens e calcular distâncias por marca
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        time_t t = parseTimestamp(p->passagem.dataHora);
        if (t < inicio || t > fim) continue;

        int idV = p->passagem.idVeiculo;
        int idS = p->passagem.idSensor;
        int idS_ant = -1;

        NodePassagem* ant = p->next;
        while (ant) {
            if (ant->passagem.idVeiculo == idV) {
                idS_ant = ant->passagem.idSensor;
                break;
            }
            ant = ant->next;
        }
        if (idS_ant == -1) continue;

        // Encontrar a marca do veículo
        char marca[CARRO_MAX_MARCA] = "";
        for (NodeCarro* c = listaCarros; c; c = c->next) {
            if (c->carro.idVeiculo == idV) {
                strncpy(marca, c->carro.marca, CARRO_MAX_MARCA);
                break;
            }
        }
        if (strlen(marca) == 0) continue;

        // Verificar se a marca já está no ranking
        int idx = -1;
        for (int i = 0; i < nMarcas; i++) {
            if (strcmp(ranking[i].marca, marca) == 0) {
                idx = i;
                break;
            }
        }
        if (idx == -1) {
            idx = nMarcas++;
            strncpy(ranking[idx].marca, marca, CARRO_MAX_MARCA);
            ranking[idx].km = 0.0;
        }

        double dist = obterDistancia(listaDistancias, idS_ant, idS);
        ranking[idx].km += dist;
    }

    qsort(ranking, nMarcas, sizeof(KmMarca), cmpMarcaRanking);

    // 2. Exibir o ranking
    printf("\n=== Ranking por Marca ===\n");
    for (int i = 0; i < nMarcas; i++) {
        printf("%2d) Marca: %s | Total de km: %.2f\n", i + 1, ranking[i].marca, ranking[i].km);
    }

    free(ranking);
}

