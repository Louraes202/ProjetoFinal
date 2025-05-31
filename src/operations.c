// operations.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <ctype.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h> 
#endif



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
    novo->passagem.ts = parseTimestamp(novo->passagem.dataHora);

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

// Função de comparação para qsort (ordem decrescente)
int cmpVeiculoRanking(const void *a, const void *b) {
    double diff = ((KmVeiculo*)b)->km - ((KmVeiculo*)a)->km;
    return (diff > 0) - (diff < 0);
}


/**
 * @brief Lista as infrações ocorridas num intervalo de tempo especificado.
 *
 * Analisa as listas de carros, passagens e medições de distâncias para identificar e
 * listar as infrações que aconteceram entre os tempos indicados por @p inicio e @p fim.
 *
 * @note Enunciado: 10. Listagem de infrações. Contém a matrícula dos veículos que
 * circularam com velocidade média superior a 120 km/h durante
 * determinado período.
 *
 * @param listaCarros Lista dos carros registados.
 * @param listaPassagens Lista das passagens registadas.
 * @param listaDistancias Lista das medições de distâncias.
 * @param inicio O instante de início do intervalo a considerar.
 * @param fim O instante de fim do intervalo a considerar.
 */


 // Polyfill simples de strptime para Windows
char* strptime(const char* s, const char* format, struct tm* tm) {
    // Supomos o formato "%d-%m-%Y %H:%M:%S"
    int d, m, y, H, M, S;
    if (sscanf(s, "%d-%d-%d %d:%d:%d", &d, &m, &y, &H, &M, &S) == 6) {
        tm->tm_mday = d;
        tm->tm_mon  = m - 1;
        tm->tm_year = y - 1900;
        tm->tm_hour = H;
        tm->tm_min  = M;
        tm->tm_sec  = S;
        tm->tm_isdst = -1;
        return (char*)s + strlen(s);
    }
    return NULL;
}

// Função auxiliar para contar nós na árvore
static void contarInfracoes(TreeNodeInfracao* arv, int* count) {
    if (arv) {
        (*count)++;
        contarInfracoes(arv->left, count);
        contarInfracoes(arv->right, count);
    }
}

// Função auxiliar para armazenar nós da árvore em um vetor (in‑order)
static void armazenarInfracoesAux(TreeNodeInfracao* arv, TreeNodeInfracao** arr, int* idx) {
    if (arv) {
        armazenarInfracoesAux(arv->left, arr, idx);
        arr[*idx] = arv;
        (*idx)++;
        armazenarInfracoesAux(arv->right, arr, idx);
    }
}

/**
 * @brief Transforma a árvore de infrações numa lista (vetor) dinâmico.
 * @param arvInfra Raiz da árvore de infrações.
 * @param total Endereço de uma variável que receberá o número total de infrações.
 * @return Vetor de ponteiros para TreeNodeInfracao ou NULL se nenhum.
 */
TreeNodeInfracao** armazenarInfracoes(TreeNodeInfracao* arvInfra, int* total) {
    int count = 0;
    contarInfracoes(arvInfra, &count);
    *total = count;
    if (count == 0)
        return NULL;
    TreeNodeInfracao** arr = malloc(count * sizeof(TreeNodeInfracao*));
    if (!arr) {
        perror("Erro ao alocar memória para vetor de infrações");
        *total = 0;
        return NULL;
    }
    int idx = 0;
    armazenarInfracoesAux(arvInfra, arr, &idx);
    return arr;
}

/**
 * @brief Libera a árvore de infrações recursivamente.
 * @param arvInfra Raiz da árvore de infrações.
 */
void libertarArvoreInfracoes(TreeNodeInfracao* arvInfra) {
    if (!arvInfra)
        return;
    libertarArvoreInfracoes(arvInfra->left);
    libertarArvoreInfracoes(arvInfra->right);
    free(arvInfra);
}




// Função de parsing da timesstamp
// Função de parsing da timesstamp (CORRIGIDA)
time_t parseTimestamp(const char *dataHora) {
    struct tm tm = {0}; // Inicializar a struct a zeros
    char buffer[25]; // Espaço suficiente para a string

    // Copiar a string original para um buffer modificável
    strncpy(buffer, dataHora, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // Procurar o underscore '_' e substituí-lo por um espaço ' '
    char *underscore_pos = strchr(buffer, '_');
    if (underscore_pos) {
        *underscore_pos = ' ';
    }

    // Usar strptime no buffer modificado, lendo apenas a parte sem milissegundos
    if (strptime(buffer, "%d-%m-%Y %H:%M:%S", &tm) == NULL) {
        // Se ainda assim falhar, pode ser um formato inesperado.
        // fprintf(stderr, "Aviso: Nao foi possivel analisar a data/hora: %s\n", dataHora);
        return -1; // Retorna -1 em caso de erro
    }

    // Assegurar que o DST (Daylight Saving Time) é determinado automaticamente
    tm.tm_isdst = -1; 
    
    return mktime(&tm);
}

// Função para obter distâncias entre sensores
double obterDistancia(NodeDistancia* lista, int id1, int id2) {
    for (NodeDistancia* p = lista; p; p = p->next) {
        if ((p->distancia.idSensor1 == id1 && p->distancia.idSensor2 == id2) ||
            (p->distancia.idSensor1 == id2 && p->distancia.idSensor2 == id1)) {
            return p->distancia.distancia;
        }
    }
    return -1.0; // Distância não encontrada
}

// Função para calcular a velocidade média total de um veículo (VERSÃO CORRIGIDA)
double calcularVelocidadeMediaPonderada(NodePassagem* passagens, NodeDistancia* listaDistancias) {
    // A lista de passagens para um veículo já deve vir ordenada por data
    if (!passagens) return -1.0;

    double somaVelocidadesPonderadas = 0.0;
    double tempoTotalViagem = 0.0;
    int viagensValidas = 0;

    // Percorre a lista à procura de uma ENTRADA
    for (NodePassagem* pEntrada = passagens; pEntrada; pEntrada = pEntrada->next) {
        if (pEntrada->passagem.tipoRegisto == 0) { // Encontrou uma entrada (tipo 0)
            
            // Agora, a partir desta entrada, procure a PRÓXIMA saída
            NodePassagem* pSaida = NULL;
            for (pSaida = pEntrada->next; pSaida; pSaida = pSaida->next) {
                if (pSaida->passagem.tipoRegisto == 1) { // Encontrou uma saída (tipo 1)
                    break; // Encontrou o par, sai do loop interno
                }
            }

            // Se um par Entrada->Saída foi encontrado
            if (pSaida) {
                double distancia = obterDistancia(listaDistancias, pEntrada->passagem.idSensor, pSaida->passagem.idSensor);
                double tempo_s = difftime(pSaida->passagem.ts, pEntrada->passagem.ts);

                // Define um tempo máximo razoável para uma viagem (ex: 24 horas = 86400s)
                const double MAX_TEMPO_VIAGEM = 86400.0; 

                if (distancia > 0 && tempo_s > 0 && tempo_s < MAX_TEMPO_VIAGEM) {
                    double velocidade_kmh = (distancia / tempo_s) * 3600.0;
                    
                    somaVelocidadesPonderadas += velocidade_kmh * tempo_s;
                    tempoTotalViagem += tempo_s;
                    viagensValidas++;
                }
                
                // Move o ponteiro principal para depois da saída encontrada para não reprocessar
                pEntrada = pSaida; 
            }
        }
    }

    if (viagensValidas > 0 && tempoTotalViagem > 0) {
        return somaVelocidadesPonderadas / tempoTotalViagem;
    }

    return -1.0; // Nenhuma viagem válida encontrada
}

double calcularVelocidadeInfracao(NodePassagem* passagens,
                                  NodeDistancia* listaDistancias)
{
    double maxVel = 0.0;
    NodePassagem* pendente = NULL;

    for (NodePassagem* p = passagens; p; p = p->next) {
        if (p->passagem.tipoRegisto == 0) {
            // marca este registo de entrada
            pendente = p;
        }
        else if (p->passagem.tipoRegisto == 1 && pendente) {
            // quando aparece a saída correspondente
            double d  = obterDistancia(listaDistancias,
                                       pendente->passagem.idSensor,
                                       p->passagem.idSensor);
            double dt = difftime(p->passagem.ts,
                                 pendente->passagem.ts);

            if (d >= 0 && dt > 0 && dt <= 86400) {
                double vel = (d / dt) * 3600.0;  // km/h
                if (vel > maxVel) maxVel = vel;
            }
            // esgota o par entrada→saída
            pendente = NULL;
        }
    }

    return maxVel;
}

// Função auxiliar para filtrar passagens dentro do intervalo [inicio, fim]
NodePassagem* filtrarPassagens(NodePassagem* lista, time_t inicio, time_t fim) {
    NodePassagem* filtradas = NULL;
    NodePassagem* ultimo = NULL;
    for (NodePassagem* p = lista; p; p = p->next) {
        // Se o campo ts já estiver preenchido, use-o
        time_t t = p->passagem.ts;  
        // Caso contrário, use parseTimestamp
        // time_t t = (p->passagem.ts != 0 ? p->passagem.ts : parseTimestamp(p->passagem.dataHora));
        if (t >= inicio && t <= fim) {
            NodePassagem* nova = malloc(sizeof(NodePassagem));
            if (!nova) {
                perror("Erro ao alocar memória para passagem filtrada");
                return filtradas;
            }
            nova->passagem = p->passagem;
            nova->next = NULL;
            if (filtradas == NULL) {
                filtradas = nova;
                ultimo = nova;
            } else {
                ultimo->next = nova;
                ultimo = nova;
            }
        }
    }
    return filtradas;
}

// Função hash simples: módulo do idVeiculo com o número de buckets
static size_t hashFunction(int idVeiculo, size_t numBuckets) {
    return ((size_t)idVeiculo) % numBuckets;
}

// Cria a tabela hash com um número especificado de buckets
HashTablePassagens* criarHashTablePassagens(size_t numBuckets) {
    HashTablePassagens* ht = malloc(sizeof(HashTablePassagens));
    if (!ht) {
        perror("Erro ao alocar memória para HashTablePassagens");
        return NULL;
    }
    ht->numBuckets = numBuckets;
    ht->buckets = calloc(numBuckets, sizeof(PassagemGroup*));
    if (!ht->buckets) {
        perror("Erro ao alocar memória para os buckets da tabela hash");
        free(ht);
        return NULL;
    }
    return ht;
}

// Insere uma passagem na tabela hash, agrupando-a pelo idVeiculo
void inserirPassagemHash(HashTablePassagens* ht, const Passagem* passagem) {
    if (!ht) return;
    size_t index = hashFunction(passagem->idVeiculo, ht->numBuckets);
    PassagemGroup* grupo = ht->buckets[index];

    // Procura se já existe um grupo para esse veículo
    while (grupo) {
        if (grupo->idVeiculo == passagem->idVeiculo)
            break;
        grupo = grupo->next;
    }
    // Se não existe, cria um novo grupo
    if (!grupo) {
        grupo = malloc(sizeof(PassagemGroup));
        if (!grupo) {
            perror("Erro ao alocar memória para PassagemGroup");
            return;
        }
        grupo->idVeiculo = passagem->idVeiculo;
        grupo->passagens = NULL;
        grupo->next = ht->buckets[index];
        ht->buckets[index] = grupo;
    }
    // Insere a passagem no início da lista ligada do grupo
    NodePassagem* novoNo = malloc(sizeof(NodePassagem));
    if (!novoNo) {
        perror("Erro ao alocar memória para NodePassagem");
        return;
    }
    novoNo->passagem = *passagem;
    novoNo->next = grupo->passagens;
    grupo->passagens = novoNo;
}

// Busca a lista de passagens para um veículo específico
NodePassagem* pesquisarPassagensParaVeiculo(HashTablePassagens* ht, int idVeiculo) {
    if (!ht) return NULL;
    size_t index = hashFunction(idVeiculo, ht->numBuckets);
    PassagemGroup* grupo = ht->buckets[index];
    while (grupo) {
        if (grupo->idVeiculo == idVeiculo)
            return grupo->passagens;
        grupo = grupo->next;
    }
    return NULL;
}

// Libera toda a tabela hash e as passagens agrupadas
void libertarHashTablePassagens(HashTablePassagens* ht) {
    if (!ht) return;
    for (size_t i = 0; i < ht->numBuckets; i++) {
        PassagemGroup* grupo = ht->buckets[i];
        while (grupo) {
            PassagemGroup* temp = grupo;
            // Libera a lista de passagens do grupo
            NodePassagem* p = grupo->passagens;
            while (p) {
                NodePassagem* tempNo = p;
                p = p->next;
                free(tempNo);
            }
            grupo = grupo->next;
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

// Função auxiliar para mesclar duas listas ordenadas de passagens por data/hora
static NodePassagem* mergePassagens(NodePassagem* left, NodePassagem* right) {
    if (!left)  return right;
    if (!right) return left;

    NodePassagem* result;
    // compara time_t (ts) em vez de string
    if (left->passagem.ts <= right->passagem.ts) {
        result = left;
        result->next = mergePassagens(left->next, right);
    } else {
        result = right;
        result->next = mergePassagens(left, right->next);
    }
    return result;
}


// Função auxiliar para aplicar merge sort na lista de passagens
static NodePassagem* mergeSortPassagens(NodePassagem* head) {
    if (!head || !head->next)
        return head;
    
    // Encontrar o meio da lista usando o método do ponteiro lento/rápido
    NodePassagem* slow = head;
    NodePassagem* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    NodePassagem* mid = slow->next;
    slow->next = NULL;
    
    NodePassagem* left = mergeSortPassagens(head);
    NodePassagem* right = mergeSortPassagens(mid);
    
    return mergePassagens(left, right);
}

NodeCarro* pesquisarCarroPorId(NodeCarro* listaCarros, int idVeiculo) {
    for (NodeCarro* p = listaCarros; p; p = p->next) {
        if (p->carro.idVeiculo == idVeiculo)
            return p;
    }
    return NULL;
}

// --- Função auxiliar para inserir uma infração na árvore ---
void inserirInfracao(TreeNodeInfracao** root, const char* matricula, double velocidadeMedia) {
    if (*root == NULL) {
        *root = malloc(sizeof(TreeNodeInfracao));
        if (!*root) {
            perror("Erro ao alocar memória para infração");
            return;
        }
        strncpy((*root)->matricula, matricula, CARRO_MAX_MATRICULA);
        (*root)->velocidadeMedia = velocidadeMedia;
        (*root)->left = (*root)->right = NULL;
        return;
    }
    int cmp = strcmp(matricula, (*root)->matricula);
    if (cmp < 0) {
        inserirInfracao(&((*root)->left), matricula, velocidadeMedia);
    } else if (cmp > 0) {
        inserirInfracao(&((*root)->right), matricula, velocidadeMedia);
    } else {
        // Se já houver infração para esse veículo, guarda a maior velocidade
        if (velocidadeMedia > (*root)->velocidadeMedia)
            (*root)->velocidadeMedia = velocidadeMedia;
    }
}



// Função de listar infraçoes
void listarInfracoes(NodeCarro*     listaCarros,
                     NodePassagem*  listaPassagens,
                     NodeDistancia* listaDistancias,
                     time_t         inicio,
                     time_t         fim)
{
    TreeNodeInfracao* arvInfra = NULL;
    clock_t start = clock();

    // --- Módulo 1: filtrar passagens no intervalo ---
    NodePassagem* passagensFiltradas = filtrarPassagens(listaPassagens, inicio, fim);
    if (!passagensFiltradas) {
        printf("Nenhuma passagem encontrada no intervalo especificado.\n");
        return;
    }

    // --- Módulo 2: agrupar por veículo numa hash table ---
    HashTablePassagens* ht = criarHashTablePassagens(10);
    if (!ht) {
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    for (NodePassagem* p = passagensFiltradas; p; p = p->next)
        inserirPassagemHash(ht, &p->passagem);

    // --- Módulo 3: ordenar cronologicamente cada grupo ---
    for (size_t i = 0; i < ht->numBuckets; i++) {
        for (PassagemGroup* g = ht->buckets[i]; g; g = g->next) {
            g->passagens = mergeSortPassagens(g->passagens);
        }
    }

    // --- Módulo 4: detectar infrações e construir árvore ---
    for (size_t i = 0; i < ht->numBuckets; i++) {
        for (PassagemGroup* g = ht->buckets[i]; g; g = g->next) {
            double maxVel = calcularVelocidadeInfracao(g->passagens, listaDistancias);
            if (maxVel > 120.0 && maxVel < 300.0) {
                NodeCarro* carro = pesquisarCarroPorId(listaCarros, g->idVeiculo);
                if (carro)
                    inserirInfracao(&arvInfra, carro->carro.matricula, maxVel);
            }
        }
    }

    // --- Módulo 5: converter árvore em array e medir tempo ---
    int totalInfra = 0;
    TreeNodeInfracao** infraArray = armazenarInfracoes(arvInfra, &totalInfra);
    double processingTime = (double)(clock() - start) / CLOCKS_PER_SEC;

    // --- Módulo 6: exibir resultados ou mensagem de “nenhuma infração” ---
    if (!infraArray || totalInfra == 0) {
        printf("Nenhuma infração encontrada no período especificado.\n");
    } else {
        int pageSize    = 5;
        int currentPage = 0;
        char opcao;
        do {
            int startIdx = currentPage * pageSize;
            int endIdx   = startIdx + pageSize;
            if (endIdx > totalInfra) endIdx = totalInfra;

            printf("\n=== Resumo de Infrações ===\n");
            printf("Total: %d infrações | Tempo: %.3f s\n", totalInfra, processingTime);
            printf("Exibindo [%d - %d]:\n", startIdx+1, endIdx);
            for (int i = startIdx; i < endIdx; i++) {
                printf("%2d) Matrícula: %s | Vel. Máx.: %.2f km/h\n",
                       i+1,
                       infraArray[i]->matricula,
                       infraArray[i]->velocidadeMedia);
            }

            printf("\nOpções:\n"
                   " n - Próxima página\n"
                   " p - Página anterior\n"
                   " t - Alterar itens por página (atual: %d)\n"
                   " b - Buscar matrícula\n"
                   " s - Sair\n"
                   "Escolha: ",
                   pageSize);
            scanf(" %c", &opcao);

            if      (opcao=='n' && endIdx < totalInfra) currentPage++;
            else if (opcao=='p' && currentPage > 0)     currentPage--;
            else if (opcao=='t') {
                printf("Novo número de itens por página: ");
                scanf("%d", &pageSize);
                if (pageSize <= 0) pageSize = 5;
                currentPage = 0;
            }
            else if (opcao=='b') {
                char busca[CARRO_MAX_MATRICULA];
                printf("Matrícula: ");
                scanf("%s", busca);
                int found = 0;
                for (int i = 0; i < totalInfra; i++) {
                    if (strcmp(infraArray[i]->matricula, busca) == 0) {
                        printf("Encontrado no índice %d: %.2f km/h\n",
                               i+1, infraArray[i]->velocidadeMedia);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("Matrícula '%s' não encontrada.\n", busca);
                printf("Pressione Enter para continuar...");
                while (getchar()!='\n');
                getchar();
            }
        } while (opcao != 's');
    }

    // --- Módulo 7: libertar memória ---
    free(infraArray);
    libertarArvoreInfracoes(arvInfra);
    libertarHashTablePassagens(ht);
    libertarListaPassagens(&passagensFiltradas);
}

int cmpRanking(const void* a, const void* b) {
    RankingInfra* r1 = (RankingInfra*)a;
    RankingInfra* r2 = (RankingInfra*)b;
    return r2->infraCount - r1->infraCount;
}

void rankingInfraVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim) {
    // 1. Filtrar as passagens dentro do intervalo

    NodePassagem* passagensFiltradas = filtrarPassagens(listaPassagens, inicio, fim);
    if (!passagensFiltradas) {
        printf("Nenhuma passagem encontrada no intervalo especificado.\n");
        return;
    }
    
    // 2. Criar uma tabela hash para agrupar as passagens por veículo
    HashTablePassagens* ht = criarHashTablePassagens(10);
    if (!ht) {
        printf("Erro ao criar a tabela hash para passagens.\n");
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    for (NodePassagem* p = passagensFiltradas; p; p = p->next) {
        inserirPassagemHash(ht, &p->passagem);
    }
    
    // 3. Preparar estrutura para ranking
    RankingInfra* ranking = malloc(sizeof(RankingInfra) * MAX_CARROS);
    if (!ranking) {
        perror("Erro ao alocar ranking");
        libertarHashTablePassagens(ht);
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    int nRanking = 0;
    
    // 4. Para cada grupo na tabela hash, ordenar passagens e contar infrações
    for (size_t i = 0; i < ht->numBuckets; i++) {
        PassagemGroup* grupo = ht->buckets[i];
        while (grupo) {
            printf("Ordenar grupo do veículo %d - Passagens:\n", grupo->idVeiculo);
            for (NodePassagem* p = grupo->passagens; p; p = p->next) {
                printf("    dataHora = \"%s\"\n", p->passagem.dataHora);
            }   

            // Ordena as passagens do grupo (assumindo que foram inseridas sem ordem)
            grupo->passagens = mergeSortPassagens(grupo->passagens);

            int count = 0;
            // Percorre as passagens consecutivas e calcula a velocidade média de cada par
            for (NodePassagem* p = grupo->passagens; p && p->next; p = p->next) {
                double d = obterDistancia(listaDistancias, p->passagem.idSensor, p->next->passagem.idSensor);
                if (d < 0)
                    continue; // ignora se a distância não for encontrada
    
                double dt = difftime(p->next->passagem.ts, p->passagem.ts);
                if (dt > 0) {
                    double speed = (d / dt) * 3600.0;
                    if (speed > 120.0)
                        count++;
                }
            }

    
            if (count > 0) {
                // Buscar os dados do veículo para obter a matrícula
                NodeCarro* carro = pesquisarCarroPorId(listaCarros, grupo->idVeiculo);
                if (!carro) {
                    printf("Erro: Veículo com ID %d não encontrado.\n", grupo->idVeiculo);
                    continue;
                }                
                if (carro) {
                    ranking[nRanking].idVeiculo = grupo->idVeiculo;
                    strncpy(ranking[nRanking].matricula, carro->carro.matricula, CARRO_MAX_MATRICULA);
                    ranking[nRanking].infraCount = count;
                    nRanking++;
                }
            }
            grupo = grupo->next;
        }
    }
    
    // Se nenhum veículo teve infração, informa e encerra a função
    if (nRanking == 0) {
        printf("Nenhuma infração encontrada no período especificado.\n");
        free(ranking);
        libertarHashTablePassagens(ht);
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    
    // 5. Ordenar o ranking (ordem decrescente de infrações)
    qsort(ranking, nRanking, sizeof(RankingInfra), cmpRanking);
    
    // 6. Exibir ranking com paginação
    int pageSize = 10;
    int currentPage = 0;
    char opcao;
    do {
        int start = currentPage * pageSize;
        int end = start + pageSize;
        if (end > nRanking)
            end = nRanking;
    
        printf("\n=== Ranking de Infrações por Veículo (Página %d) ===\n", currentPage + 1);
        for (int i = start; i < end; i++) {
            printf("%2d) Veículo %d | Matrícula: %s | Infrações: %d\n", 
                   i + 1, ranking[i].idVeiculo, ranking[i].matricula, ranking[i].infraCount);
        }
    
        printf("\nOpções:\n");
        printf("n - Próxima página\n");
        printf("p - Página anterior\n");
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
    
        if (opcao == 'n' && end < nRanking)
            currentPage++;
        else if (opcao == 'p' && currentPage > 0)
            currentPage--;
    } while(opcao != 's');
    
    // 7. Liberar recursos
    free(ranking);
    libertarHashTablePassagens(ht);
    libertarListaPassagens(&passagensFiltradas);
}



/**
 * @brief Gera e apresenta um ranking de veículos com base na distância percorrida e um periodo de tempo.
 *
 * @param listaPassagens Um ponteiro para o início de uma lista ligada que contém os dados de passagens dos veículos.
 * @param listaDistancias Um ponteiro para uma lista ligada que contém informações sobre as distâncias entre os sensores.
 * @param inicio Um valor time_t que representa o início do intervalo de tempo.
 * @param fim Um valor time_t que representa o fim do intervalo de tempo.
 */
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

void velocidadesMedias(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim) {
    // 1. Filtrar as passagens no intervalo
    NodePassagem* passagensFiltradas = filtrarPassagens(listaPassagens, inicio, fim);
    if (!passagensFiltradas) {
        printf("Nenhuma passagem encontrada no intervalo especificado.\n");
        return;
    }
    
    // 2. Agrupar passagens por veículo usando a tabela hash existente
    HashTablePassagens* ht = criarHashTablePassagens(100);
    if (!ht) {
        printf("Erro ao criar a tabela hash para passagens.\n");
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    for (NodePassagem* p = passagensFiltradas; p; p = p->next) {
        inserirPassagemHash(ht, &p->passagem);
    }
    
    // 3. Para cada grupo, ordenar as passagens e calcular a velocidade média

    size_t capacidade = 1000;
    VelocidadeMedia* ranking = malloc(sizeof(VelocidadeMedia) * capacidade);
    if (!ranking) {
        perror("Erro ao alocar memoria para ranking de velocidades");
        libertarHashTablePassagens(ht);
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    int nVeiculos = 0;
    
    for (size_t i = 0; i < ht->numBuckets; i++) {
        PassagemGroup* grupo = ht->buckets[i];
        while (grupo) {
            // Ordena as passagens do grupo para garantir que estão ordenadas por data/hora
            grupo->passagens = mergeSortPassagens(grupo->passagens);
            double velMedia = calcularVelocidadeMediaPonderada(grupo->passagens, listaDistancias);
            if (velMedia > 0) {
                // Expande o array se necessário
                if (nVeiculos >= capacidade) {
                    capacidade *= 2;
                    VelocidadeMedia* temp = realloc(ranking, sizeof(VelocidadeMedia) * capacidade);
                    if (!temp) {
                        perror("Erro ao realocar ranking");
                        free(ranking);
                        libertarHashTablePassagens(ht);
                        libertarListaPassagens(&passagensFiltradas);
                        return;
                    }
                    ranking = temp;
                }
                ranking[nVeiculos].idVeiculo = grupo->idVeiculo;
                ranking[nVeiculos].velocidadeMedia = velMedia;
                nVeiculos++;
            }
            grupo = grupo->next;
        }
    }
    
    if (nVeiculos == 0) {
        printf("Nenhum veículo com velocidade calculada no período especificado.\n");
        free(ranking);
        libertarHashTablePassagens(ht);
        libertarListaPassagens(&passagensFiltradas);
        return;
    }
    
    // 4. Exibir os resultados com menu de paginação e pesquisa por matrícula
    int pageSize = 10;
    int currentPage = 0;
    char opcao;
    do {
        int startIdx = currentPage * pageSize;
        int endIdx = startIdx + pageSize;
        if (endIdx > nVeiculos) endIdx = nVeiculos;
        
        printf("\n=== Velocidades Médias por Veículo (Página %d) ===\n", currentPage + 1);
        for (int i = startIdx; i < endIdx; i++) {
            // Obtemos a matrícula do veículo usando pesquisarCarroPorId
            NodeCarro* carro = pesquisarCarroPorId(listaCarros, ranking[i].idVeiculo);
            printf("%2d) Veículo %d | Matrícula: %s | Velocidade Média: %.2f km/h\n",
                   i + 1,
                   ranking[i].idVeiculo,
                   carro ? carro->carro.matricula : "Desconhecida",
                   ranking[i].velocidadeMedia);
        }
        
        printf("\nOpções:\n");
        printf("n - Próxima página\n");
        printf("p - Página anterior\n");
        printf("b - Pesquisar por matrícula\n");
        printf("t - Alterar itens por página (atual: %d)\n", pageSize);
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &opcao);
        
        if (opcao == 'n' && endIdx < nVeiculos)
            currentPage++;
        else if (opcao == 'p' && currentPage > 0)
            currentPage--;
        else if (opcao == 'b') {
            char matriculaBusca[CARRO_MAX_MATRICULA];
            printf("Digite a matrícula para busca: ");
            scanf("%s", matriculaBusca);
            int encontrado = 0;
            for (int i = 0; i < nVeiculos; i++) {
                NodeCarro* carro = pesquisarCarroPorId(listaCarros, ranking[i].idVeiculo);
                if (carro && strcmp(carro->carro.matricula, matriculaBusca) == 0) {
                    printf("Veículo encontrado: ID %d | Matrícula: %s | Velocidade Média: %.2f km/h\n",
                           ranking[i].idVeiculo,
                           carro->carro.matricula,
                           ranking[i].velocidadeMedia);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
                printf("Matrícula '%s' não encontrada.\n", matriculaBusca);
            printf("Pressione Enter para continuar...");
            while(getchar() != '\n');
            getchar();
        } else if (opcao == 't') {
            printf("Digite o novo número de itens por página: ");
            scanf("%d", &pageSize);
            if (pageSize <= 0) pageSize = 10;
            currentPage = 0;
        }
    } while(opcao != 's');
    
    // 5. Liberar recursos
    free(ranking);
    libertarHashTablePassagens(ht);
    libertarListaPassagens(&passagensFiltradas);
}

// Função de comparação para qsort (ordem decrescente de velocidade média)
static int cmpMarcaVelocidade(const void* a, const void* b) {
    MarcaVelocidade* marcaA = (MarcaVelocidade*)a;
    MarcaVelocidade* marcaB = (MarcaVelocidade*)b;

    // Calcular a velocidade média final para cada marca antes de comparar
    double mediaA = (marcaA->numVeiculos > 0) ? (marcaA->somaVelocidades / marcaA->numVeiculos) : 0;
    double mediaB = (marcaB->numVeiculos > 0) ? (marcaB->somaVelocidades / marcaB->numVeiculos) : 0;

    if (mediaB > mediaA) return 1;
    if (mediaB < mediaA) return -1;
    return 0;
}

/**
 * @brief Requisito 13: Qual a marca dos carros que circulam a maior velocidade média?
 * Calcula e exibe um ranking de marcas de veículos com base na sua velocidade média 
 * num determinado período.
 */
void rankingMarcasVelocidade(NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim) {
    // --- Módulo 1: Filtrar passagens no intervalo de tempo ---
    NodePassagem* passagensFiltradas = filtrarPassagens(listaPassagens, inicio, fim);
    if (!passagensFiltradas) {
        printf("Nenhuma passagem encontrada no intervalo especificado.\n");
        return;
    }

    // --- Módulo 2: Agrupar passagens por veículo numa hash table ---
    HashTablePassagens* ht = criarHashTablePassagens(100); // 100 buckets, ajuste se necessário
    for (NodePassagem* p = passagensFiltradas; p; p = p->next) {
        inserirPassagemHash(ht, &p->passagem);
    }
    
    // --- Módulo 3: Calcular velocidade por veículo e agregar por marca ---
    int capacidadeMarcas = 50; // Capacidade inicial para o array de marcas
    MarcaVelocidade* rankingMarcas = malloc(sizeof(MarcaVelocidade) * capacidadeMarcas);
    int nMarcas = 0;

    for (size_t i = 0; i < ht->numBuckets; i++) {
        for (PassagemGroup* g = ht->buckets[i]; g; g = g->next) {
            
            // Ordenar passagens do veículo e calcular sua velocidade média
            g->passagens = mergeSortPassagens(g->passagens);
            double velMediaVeiculo = calcularVelocidadeMediaPonderada(g->passagens, listaDistancias);

            if (velMediaVeiculo > 0) {
                // Obter a marca do veículo
                NodeCarro* carro = pesquisarCarroPorId(listaCarros, g->idVeiculo);
                if (!carro) continue; // Pula se o carro não for encontrado

                // Procurar se a marca já existe no nosso array de ranking
                int idxMarca = -1;
                for (int j = 0; j < nMarcas; j++) {
                    if (strcmp(rankingMarcas[j].marca, carro->carro.marca) == 0) {
                        idxMarca = j;
                        break;
                    }
                }

                if (idxMarca != -1) { // Marca já existe, atualiza os valores
                    rankingMarcas[idxMarca].somaVelocidades += velMediaVeiculo;
                    rankingMarcas[idxMarca].numVeiculos++;
                } else { // Nova marca, adiciona ao array
                    if (nMarcas >= capacidadeMarcas) { // Realocar se necessário
                        capacidadeMarcas *= 2;
                        rankingMarcas = realloc(rankingMarcas, sizeof(MarcaVelocidade) * capacidadeMarcas);
                    }
                    strncpy(rankingMarcas[nMarcas].marca, carro->carro.marca, CARRO_MAX_MARCA);
                    rankingMarcas[nMarcas].somaVelocidades = velMediaVeiculo;
                    rankingMarcas[nMarcas].numVeiculos = 1;
                    nMarcas++;
                }
            }
        }
    }

    // --- Módulo 4: Ordenar o ranking de marcas ---
    if (nMarcas > 0) {
        qsort(rankingMarcas, nMarcas, sizeof(MarcaVelocidade), cmpMarcaVelocidade);
    }

    // --- Módulo 5: Exibir os resultados ---
    printf("\n=== Ranking de Marcas por Velocidade Média ===\n");
    if (nMarcas == 0) {
        printf("Não foi possível calcular a velocidade média para nenhuma marca no período indicado.\n");
    } else {
        for (int i = 0; i < nMarcas; i++) {
            double velMediaFinal = rankingMarcas[i].somaVelocidades / rankingMarcas[i].numVeiculos;
            printf("%2d) Marca: %-15s | Velocidade Média: %.2f km/h  (%d veículos)\n",
                   i + 1,
                   rankingMarcas[i].marca,
                   velMediaFinal,
                   rankingMarcas[i].numVeiculos);
        }
    }

    // --- Módulo 6: Libertar memória ---
    free(rankingMarcas);
    libertarHashTablePassagens(ht);
    libertarListaPassagens(&passagensFiltradas);
}

// --- Função auxiliar para pesquisar um Dono por NIF ---
static NodeDono* pesquisarDonoPorNIF(NodeDono* listaDonos, int nif) {
    for (NodeDono* p = listaDonos; p; p = p->next) {
        if (p->dono.numeroContribuinte == nif) {
            return p;
        }
    }
    return NULL;
}

// --- Função de comparação para qsort (por velocidade média do dono) ---
static int cmpDonoVelocidade(const void* a, const void* b) {
    DonoVelocidade* donoA = (DonoVelocidade*)a;
    DonoVelocidade* donoB = (DonoVelocidade*)b;

    double mediaA = (donoA->numVeiculos > 0) ? (donoA->somaVelocidades / donoA->numVeiculos) : 0;
    double mediaB = (donoB->numVeiculos > 0) ? (donoB->somaVelocidades / donoB->numVeiculos) : 0;

    if (mediaB > mediaA) return 1;
    if (mediaB < mediaA) return -1;
    return 0;
}

/**
 * @brief Requisito 14: Qual o condutor (dono) que circula a maior velocidade média?
 * Calcula e exibe um ranking de donos com base na velocidade média dos seus veículos.
 */
void rankingDonosVelocidade(NodeDono* listaDonos, NodeCarro* listaCarros, NodePassagem* listaPassagens, 
                          NodeDistancia* listaDistancias, time_t inicio, time_t fim) {
    
    // Módulo 1: Filtrar e agrupar passagens (igual à função anterior)
    NodePassagem* passagensFiltradas = filtrarPassagens(listaPassagens, inicio, fim);
    if (!passagensFiltradas) {
        printf("Nenhuma passagem encontrada no intervalo especificado.\n");
        return;
    }
    HashTablePassagens* ht = criarHashTablePassagens(100);
    for (NodePassagem* p = passagensFiltradas; p; p = p->next) {
        inserirPassagemHash(ht, &p->passagem);
    }
    
    // Módulo 2: Calcular velocidade por veículo e agregar por DONO
    int capacidadeDonos = 500; // Capacidade inicial para o array de donos
    DonoVelocidade* rankingDonos = malloc(sizeof(DonoVelocidade) * capacidadeDonos);
    int nDonos = 0;

    for (size_t i = 0; i < ht->numBuckets; i++) {
        for (PassagemGroup* g = ht->buckets[i]; g; g = g->next) {
            
            g->passagens = mergeSortPassagens(g->passagens);
            double velMediaVeiculo = calcularVelocidadeMediaPonderada(g->passagens, listaDistancias);

            if (velMediaVeiculo > 0) {
                // Obter o NIF do dono do veículo
                NodeCarro* carro = pesquisarCarroPorId(listaCarros, g->idVeiculo);
                if (!carro) continue;
                int nifDono = carro->carro.donoContribuinte;

                // Procurar se o dono já existe no nosso array de ranking
                int idxDono = -1;
                for (int j = 0; j < nDonos; j++) {
                    if (rankingDonos[j].nifDono == nifDono) {
                        idxDono = j;
                        break;
                    }
                }

                if (idxDono != -1) { // Dono já existe, atualiza os valores
                    rankingDonos[idxDono].somaVelocidades += velMediaVeiculo;
                    rankingDonos[idxDono].numVeiculos++;
                } else { // Novo dono, adiciona ao array
                    NodeDono* dono = pesquisarDonoPorNIF(listaDonos, nifDono);
                    if (!dono) continue; // Pula se não encontrar os dados do dono

                    if (nDonos >= capacidadeDonos) { // Realocar se necessário
                        capacidadeDonos *= 2;
                        rankingDonos = realloc(rankingDonos, sizeof(DonoVelocidade) * capacidadeDonos);
                    }
                    rankingDonos[nDonos].nifDono = nifDono;
                    strncpy(rankingDonos[nDonos].nomeDono, dono->dono.nome, DONO_MAX_NOME);
                    rankingDonos[nDonos].somaVelocidades = velMediaVeiculo;
                    rankingDonos[nDonos].numVeiculos = 1;
                    nDonos++;
                }
            }
        }
    }

    // Módulo 3: Ordenar o ranking de donos
    if (nDonos > 0) {
        qsort(rankingDonos, nDonos, sizeof(DonoVelocidade), cmpDonoVelocidade);
    }

    // Módulo 4: Exibir os resultados
    printf("\n=== Ranking de Donos por Velocidade Média ===\n");
    if (nDonos == 0) {
        printf("Não foi possível calcular a velocidade média para nenhum dono no período indicado.\n");
    } else {
        int limite = nDonos < 20 ? nDonos : 20; // Mostra o Top 20 para não inundar o ecrã
        printf("(A apresentar os primeiros %d resultados)\n", limite);
        for (int i = 0; i < limite; i++) {
            double velMediaFinal = rankingDonos[i].somaVelocidades / rankingDonos[i].numVeiculos;
            printf("%2d) Dono: %-25s (NIF: %d) | Vel. Média: %.2f km/h (%d veículos)\n",
                   i + 1,
                   rankingDonos[i].nomeDono,
                   rankingDonos[i].nifDono,
                   velMediaFinal,
                   rankingDonos[i].numVeiculos);
        }
    }

    // Módulo 5: Libertar memória
    free(rankingDonos);
    libertarHashTablePassagens(ht);
    libertarListaPassagens(&passagensFiltradas);
}

// --- Funções Auxiliares para a Exportação CSV ---

// --- Funções Auxiliares para a Exportação CSV ---

static void exportarDonosCSV(NodeDono* head, const char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }
    // Header com uma coluna para cada variável da struct Dono
    fprintf(fp, "NumeroContribuinte,Nome,CodigoPostal\n");
    for (NodeDono* p = head; p; p = p->next) {
        fprintf(fp, "%d,\"%s\",\"%s\"\n", 
                p->dono.numeroContribuinte, 
                p->dono.nome, 
                p->dono.codigoPostal);
    }
    fclose(fp);
    printf("Ficheiro %s exportado com sucesso.\n", filepath);
}

static void exportarCarrosCSV(NodeCarro* head, const char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }
    // Header com uma coluna para cada variável da struct Carro
    fprintf(fp, "Matricula,Marca,Modelo,Ano,DonoContribuinte,IdVeiculo\n");
    for (NodeCarro* p = head; p; p = p->next) {
        fprintf(fp, "\"%s\",\"%s\",\"%s\",%d,%d,%d\n",
                p->carro.matricula,
                p->carro.marca,
                p->carro.modelo,
                p->carro.ano,
                p->carro.donoContribuinte,
                p->carro.idVeiculo);
    }
    fclose(fp);
    printf("Ficheiro %s exportado com sucesso.\n", filepath);
}

static void exportarSensoresCSV(NodeSensor* head, const char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }
    // Header com uma coluna para cada variável da struct Sensor
    fprintf(fp, "IdSensor,Designacao,Latitude,Longitude\n");
    for (NodeSensor* p = head; p; p = p->next) {
        fprintf(fp, "%d,\"%s\",\"%s\",\"%s\"\n",
                p->sensor.idSensor,
                p->sensor.designacao,
                p->sensor.latitude,
                p->sensor.longitude);
    }
    fclose(fp);
    printf("Ficheiro %s exportado com sucesso.\n", filepath);
}

static void exportarDistanciasCSV(NodeDistancia* head, const char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }
    // Header com uma coluna para cada variável da struct Distancia
    fprintf(fp, "IdSensor1,IdSensor2,Distancia\n");
    for (NodeDistancia* p = head; p; p = p->next) {
        fprintf(fp, "%d,%d,%.2f\n",
                p->distancia.idSensor1,
                p->distancia.idSensor2,
                p->distancia.distancia);
    }
    fclose(fp);
    printf("Ficheiro %s exportado com sucesso.\n", filepath);
}

static void exportarPassagensCSV(NodePassagem* head, const char* filepath) {
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }
    // Header com uma coluna para cada variável da struct Passagem
    fprintf(fp, "IdSensor,IdVeiculo,DataHora,TipoRegisto\n");
    for (NodePassagem* p = head; p; p = p->next) {
        fprintf(fp, "%d,%d,\"%s\",%d\n",
                p->passagem.idSensor,
                p->passagem.idVeiculo,
                p->passagem.dataHora,
                p->passagem.tipoRegisto);
    }
    fclose(fp);
    printf("Ficheiro %s exportado com sucesso.\n", filepath);
}


/**
 * @brief Requisito 17: Exporta todos os dados carregados para ficheiros CSV.
 * Cria uma pasta 'Export-CSV' e guarda um ficheiro para cada tipo de entidade.
 */
void exportarDadosCSV(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, 
                      NodeDistancia* listaDistancias, NodePassagem* listaPassagens) {
    
    const char* dir = "Export-CSV";
#ifdef _WIN32
    _mkdir(dir);
#else
    mkdir(dir, 0777);
#endif

    printf("\n--- A exportar dados para formato CSV ---\n");

    exportarDonosCSV(listaDonos, "Export-CSV/donos.csv");
    exportarCarrosCSV(listaCarros, "Export-CSV/carros.csv");
    exportarSensoresCSV(listaSensores, "Export-CSV/sensores.csv");
    exportarDistanciasCSV(listaDistancias, "Export-CSV/distancias.csv");
    exportarPassagensCSV(listaPassagens, "Export-CSV/passagens.csv");
    
    printf("--- Exportação concluída. ---\n");
}

/**
 * @brief Função auxiliar para escrever uma string num ficheiro XML,
 * tratando os caracteres especiais (&, <, >, ", ').
 */
static void escreverStringXML(FILE* fp, const char* str) {
    while (*str) {
        switch (*str) {
            case '&':  fprintf(fp, "&amp;"); break;
            case '<':  fprintf(fp, "&lt;"); break;
            case '>':  fprintf(fp, "&gt;"); break;
            case '\"': fprintf(fp, "&quot;"); break;
            case '\'': fprintf(fp, "&apos;"); break;
            default:   fputc(*str, fp); break;
        }
        str++;
    }
}

/**
 * @brief Requisito 18: Exporta todos os dados carregados para um único ficheiro XML.
 */
void exportarDadosXML(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, 
                      NodeDistancia* listaDistancias, NodePassagem* listaPassagens) {

    const char* filepath = "export_completo.xml";
    FILE* fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "Erro ao criar o ficheiro %s\n", filepath);
        return;
    }

    printf("\n--- A exportar dados para formato XML ---\n");

    // Declaração XML e elemento-raiz
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<baseDeDados>\n");

    // --- Exportar Donos ---
    fprintf(fp, "\t<listaDonos>\n");
    for (NodeDono* p = listaDonos; p; p = p->next) {
        fprintf(fp, "\t\t<dono>\n");
        fprintf(fp, "\t\t\t<numeroContribuinte>%d</numeroContribuinte>\n", p->dono.numeroContribuinte);
        fprintf(fp, "\t\t\t<nome>");
        escreverStringXML(fp, p->dono.nome);
        fprintf(fp, "</nome>\n");
        fprintf(fp, "\t\t\t<codigoPostal>");
        escreverStringXML(fp, p->dono.codigoPostal);
        fprintf(fp, "</codigoPostal>\n");
        fprintf(fp, "\t\t</dono>\n");
    }
    fprintf(fp, "\t</listaDonos>\n\n");

    // --- Exportar Carros ---
    fprintf(fp, "\t<listaCarros>\n");
    for (NodeCarro* p = listaCarros; p; p = p->next) {
        fprintf(fp, "\t\t<carro>\n");
        fprintf(fp, "\t\t\t<matricula>");
        escreverStringXML(fp, p->carro.matricula);
        fprintf(fp, "</matricula>\n");
        fprintf(fp, "\t\t\t<marca>");
        escreverStringXML(fp, p->carro.marca);
        fprintf(fp, "</marca>\n");
        fprintf(fp, "\t\t\t<modelo>");
        escreverStringXML(fp, p->carro.modelo);
        fprintf(fp, "</modelo>\n");
        fprintf(fp, "\t\t\t<ano>%d</ano>\n", p->carro.ano);
        fprintf(fp, "\t\t\t<donoContribuinte>%d</donoContribuinte>\n", p->carro.donoContribuinte);
        fprintf(fp, "\t\t\t<idVeiculo>%d</idVeiculo>\n", p->carro.idVeiculo);
        fprintf(fp, "\t\t</carro>\n");
    }
    fprintf(fp, "\t</listaCarros>\n\n");

    // --- Exportar Sensores ---
    fprintf(fp, "\t<listaSensores>\n");
    for (NodeSensor* p = listaSensores; p; p = p->next) {
        fprintf(fp, "\t\t<sensor>\n");
        fprintf(fp, "\t\t\t<idSensor>%d</idSensor>\n", p->sensor.idSensor);
        fprintf(fp, "\t\t\t<designacao>");
        escreverStringXML(fp, p->sensor.designacao);
        fprintf(fp, "</designacao>\n");
        fprintf(fp, "\t\t\t<latitude>");
        escreverStringXML(fp, p->sensor.latitude);
        fprintf(fp, "</latitude>\n");
        fprintf(fp, "\t\t\t<longitude>");
        escreverStringXML(fp, p->sensor.longitude);
        fprintf(fp, "</longitude>\n");
        fprintf(fp, "\t\t</sensor>\n");
    }
    fprintf(fp, "\t</listaSensores>\n\n");

    // --- Exportar Distâncias ---
    fprintf(fp, "\t<listaDistancias>\n");
    for (NodeDistancia* p = listaDistancias; p; p = p->next) {
        fprintf(fp, "\t\t<distancia>\n");
        fprintf(fp, "\t\t\t<idSensor1>%d</idSensor1>\n", p->distancia.idSensor1);
        fprintf(fp, "\t\t\t<idSensor2>%d</idSensor2>\n", p->distancia.idSensor2);
        fprintf(fp, "\t\t\t<distancia>%.2f</distancia>\n", p->distancia.distancia);
        fprintf(fp, "\t\t</distancia>\n");
    }
    fprintf(fp, "\t</listaDistancias>\n\n");

    // --- Exportar Passagens ---
    fprintf(fp, "\t<listaPassagens>\n");
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        fprintf(fp, "\t\t<passagem>\n");
        fprintf(fp, "\t\t\t<idSensor>%d</idSensor>\n", p->passagem.idSensor);
        fprintf(fp, "\t\t\t<idVeiculo>%d</idVeiculo>\n", p->passagem.idVeiculo);
        fprintf(fp, "\t\t\t<dataHora>");
        escreverStringXML(fp, p->passagem.dataHora);
        fprintf(fp, "</dataHora>\n");
        fprintf(fp, "\t\t\t<tipoRegisto>%d</tipoRegisto>\n", p->passagem.tipoRegisto);
        fprintf(fp, "\t\t</passagem>\n");
    }
    fprintf(fp, "\t</listaPassagens>\n");

    // Fechar o elemento-raiz
    fprintf(fp, "</baseDeDados>\n");
    fclose(fp);

    printf("Ficheiro XML exportado com sucesso em: %s\n", filepath);
}

void debugVeiculo(int idVeiculoDebug, NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias) {
    printf("\n==============================================\n");
    printf("--- INICIANDO DEBUG PARA O VEICULO ID: %d ---\n", idVeiculoDebug);
    printf("==============================================\n");

    // Passo 1: Isolar as passagens apenas para este veículo
    NodePassagem* passagensVeiculo = NULL;
    NodePassagem* cauda = NULL;
    for (NodePassagem* p = listaPassagens; p; p = p->next) {
        if (p->passagem.idVeiculo == idVeiculoDebug) {
            NodePassagem* nova = malloc(sizeof(NodePassagem));
            if (!nova) {
                printf("ERRO: Falha ao alocar memoria para debug.\n");
                return;
            }
            nova->passagem = p->passagem;
            nova->next = NULL;
            if (passagensVeiculo == NULL) {
                passagensVeiculo = cauda = nova;
            } else {
                cauda->next = nova;
                cauda = nova;
            }
        }
    }

    if (passagensVeiculo == NULL) {
        printf("Nenhuma passagem encontrada para o veiculo ID %d.\n", idVeiculoDebug);
        return;
    }

    // Passo 2: Ordenar as passagens do veículo por data/hora
    passagensVeiculo = mergeSortPassagens(passagensVeiculo);
    printf("\n[INFO] Encontradas e ordenadas as seguintes passagens:\n");
    for (NodePassagem* p = passagensVeiculo; p; p = p->next) {
        printf(" -> Sensor: %d | Data: %s\n", p->passagem.idSensor, p->passagem.dataHora);
    }

    // Passo 3: Informação do Veículo
    NodeCarro* carro = pesquisarCarroPorId(listaCarros, idVeiculoDebug);
    if (carro) {
        printf("\n[INFO] Detalhes do Veiculo: Matricula %s, Marca %s, Modelo %s\n",
               carro->carro.matricula, carro->carro.marca, carro->carro.modelo);
    } else {
        printf("\n[AVISO] Nao foram encontrados detalhes para o veiculo ID %d.\n", idVeiculoDebug);
    }

    // Passo 4: Calcular e imprimir detalhes de cada troço da viagem
    printf("\n--- Analise dos Trocos da Viagem ---\n");
    double somaVelocidadesPonderadas = 0.0;
    double tempoTotalViagem = 0.0;
    int trocosValidos = 0;

    for (NodePassagem* p = passagensVeiculo; p && p->next; p = p->next) {
        printf("\n-> A analisar troco: Sensor %d para Sensor %d\n", p->passagem.idSensor, p->next->passagem.idSensor);

        // Obter Timestamps
        time_t ts1 = p->passagem.ts;
        time_t ts2 = p->next->passagem.ts;
        printf("   - DataHora 1: %s (Timestamp Lido: %ld)\n", p->passagem.dataHora, ts1);
        printf("   - DataHora 2: %s (Timestamp Lido: %ld)\n", p->next->passagem.dataHora, ts2);
        
        // Obter Distância
        double distancia = obterDistancia(listaDistancias, p->passagem.idSensor, p->next->passagem.idSensor);
        printf("   - Distancia entre sensores: %.2f km\n", distancia);

        // Calcular Tempo
        double tempo_s = difftime(ts2, ts1);
        printf("   - Tempo de viagem no troco: %.2f segundos\n", tempo_s);

        // Validações
        if (distancia <= 0 || tempo_s <= 0) {
            printf("   [ERRO NO CALCULO] Distancia ou tempo invalidos. A saltar este troco.\n");
            continue;
        }

        // Calcular Velocidade
        double velocidade_kmh = (distancia / tempo_s) * 3600.0;
        printf("   => VELOCIDADE MEDIA NO TROCO: %.2f km/h\n", velocidade_kmh);

        somaVelocidadesPonderadas += velocidade_kmh * tempo_s;
        tempoTotalViagem += tempo_s;
        trocosValidos++;
    }

    // Passo 5: Calcular e imprimir a velocidade média final
    printf("\n--- Resultado Final para o Veiculo ID %d ---\n", idVeiculoDebug);
    if (trocosValidos > 0 && tempoTotalViagem > 0) {
        double velocidadeMediaFinal = somaVelocidadesPonderadas / tempoTotalViagem;
        printf("Velocidade Media Ponderada Final: %.2f km/h\n", velocidadeMediaFinal);
        printf("Calculada com base em %d trocos validos.\n", trocosValidos);
    } else {
        printf("Nao foi possivel calcular uma velocidade media final (nenhum troco valido encontrado).\n");
    }
    printf("==============================================\n");

    // Limpar a memória alocada para a lista temporária
    libertarListaPassagens(&passagensVeiculo);
}