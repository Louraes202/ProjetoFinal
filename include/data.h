#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define DONO_MAX_NOME 200
#define DONO_MAX_CODIGOPOSTAL 10
#define CARRO_MAX_MATRICULA 15
#define CARRO_MAX_MARCA 30
#define CARRO_MAX_MODELO 30
#define SENSOR_MAX_DESIGNACAO 50
#define SENSOR_MAX_LATITUDE 90
#define SENSOR_MAX_LONGITUDE 180
#define PASSAGEM_MAX_DATAHORA 30
#define MAX_DONOS 100000 // s.a.a.
#define MAX_CARROS 100000 // s.a.a.
#define MAX_SENSORES 10000

#define _GNU_SOURCE
#include <time.h>

/**
 * @brief  * Representa um Dono (conforme o enunciado: numContribuinte, nome, codPostal).
 * Aqui usamos:
 *  - numeroContribuinte (int)
 *  - nome (string)
 *  - codigoPostal (string)
 * 
 */
typedef struct {
    int  numeroContribuinte;
    char nome[DONO_MAX_NOME];
    char codigoPostal[DONO_MAX_CODIGOPOSTAL];
} Dono;

/**
 * @brief Cada node de lista ligada para armazenar Donos.
 * 
 */
typedef struct nodeDono {
    Dono               dono;
    struct nodeDono*   next;
} NodeDono;

/**
 * @brief Representa um Carro (equivalente à entidade "Carro" do enunciado).
 *  - matrícula => matricula
 *  - marca => marca
 *  - modelo => modelo
 *  - ano => ano
 *  - numContribuinte do Dono => donoContribuinte
 *  - codVeiculo => idVeiculo
 *
 * 
 */
typedef struct {
    char matricula[CARRO_MAX_MATRICULA];
    char marca[CARRO_MAX_MARCA];
    char modelo[CARRO_MAX_MODELO];
    int  ano;
    int  donoContribuinte; // faz a ligação a Dono.numeroContribuinte
    int  idVeiculo;
} Carro;

/**
 * @brief Lista ligada de Carros.
 * 
 */
typedef struct nodeCarro {
    Carro             carro;
    struct nodeCarro* next;
} NodeCarro;

/**
 * @brief Representa um Sensor (equivalente a "codSensor", "designacao", "latitude", "longitude").
 * 
 */
typedef struct {
    int  idSensor;
    char designacao[SENSOR_MAX_DESIGNACAO];
    char latitude[SENSOR_MAX_LATITUDE];
    char longitude[SENSOR_MAX_LONGITUDE];
} Sensor;

/**
 * @brief Lista ligada de Sensores.
 * 
 */
typedef struct nodeSensor {
    Sensor            sensor;
    struct nodeSensor* next;
} NodeSensor;

/**
 * @brief  Representa uma Distancia entre dois Sensores:
 *  - idSensor1
 *  - idSensor2
 *  - distancia (float)
 * 
 */
typedef struct {
    int   idSensor1;
    int   idSensor2;
    float distancia;
} Distancia;

/**
 * @brief Lista ligada de Distancias.
 * 
 */
typedef struct nodeDistancia {
    Distancia             distancia;
    struct nodeDistancia* next;
} NodeDistancia;

/**
 * @brief  Representa uma Passagem (equivalente a "Passagem" do enunciado):
 *  - idSensor
 *  - idVeiculo
 *  - dataHora (string)
 *  - tipoRegisto (0=entrada, 1=saída)
 * 
 */
typedef struct {
    int  idSensor;
    int  idVeiculo;
    char dataHora[PASSAGEM_MAX_DATAHORA];  // ex.: "12-09-2010_21:35:45.135"
    int  tipoRegisto;   // 0=entrada, 1=saída
    time_t ts;
} Passagem;

/**
 * @brief Lista ligada de Passagens.
 * 
 */
typedef struct nodePassagem {
    Passagem            passagem;
    struct nodePassagem* next;
} NodePassagem;

typedef struct kmVeiculo {
    int  idVeiculo;
    float km;
} KmVeiculo;

/**
 * @brief Estrutura para armazenar o total de quilómetros por marca
 * 
 */
typedef struct kmMarca {
    char marca[CARRO_MAX_MARCA];
    double km;
} KmMarca;


/**
 * @brief Estrutura para armazenar infrações numa árvore binária
 * 
 */
typedef struct TreeNodeInfracao {
    char matricula[CARRO_MAX_MATRICULA];  // Matrícula do veículo infrator
    double velocidadeMedia;               // Velocidade média calculada para determinar a infração
    struct TreeNodeInfracao *left;          // Ponteiro para subárvore esquerda
    struct TreeNodeInfracao *right;         // Ponteiro para subárvore direita
} TreeNodeInfracao;

/**
 * @brief Estrutura para agrupar passagens por veículo numa tabela hash
 * 
 */
typedef struct PassagemGroup {
    int idVeiculo;                  // Identificador do veículo
    NodePassagem* passagens;        // Lista ligada de passagens deste veículo
    struct PassagemGroup* next;     // Próximo grupo em caso de colisão no hash
} PassagemGroup;


/**
 * @brief -- Estruturas para a funçao listarInfracoes
 * 
 */
typedef struct hashTablePassagens {
    size_t numBuckets;              // Número de buckets na tabela hash
    PassagemGroup** buckets;        // Array com os buckets (cada bucket é uma lista de PassagemGroup)
} HashTablePassagens;

typedef struct rankingInfra {
    int idVeiculo;
    char matricula[CARRO_MAX_MATRICULA];
    int infraCount;
} RankingInfra;
    
typedef struct {
    int idVeiculo;
    double velocidadeMedia;
} VelocidadeMedia;

typedef struct {
    char   marca[CARRO_MAX_MARCA];
    double somaVelocidades; // Soma das velocidades médias dos veículos desta marca
    int    numVeiculos;     // Nº de veículos da marca que circularam
} MarcaVelocidade;

typedef struct {
    int    nifDono;
    char   nomeDono[DONO_MAX_NOME];
    double somaVelocidades; // Soma das velocidades médias dos veículos deste dono
    int    numVeiculos;     // Nº de veículos do dono que circularam
} DonoVelocidade;

/**
 * @brief Estrutura auxiliar local para guardar a contagem de cada marca
 * 
 */
typedef struct {
    char marca[CARRO_MAX_MARCA];
    int contagem;
} MarcaContagem;

#endif /* DATA_STRUCTURES_H */

