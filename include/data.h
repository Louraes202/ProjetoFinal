#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define DONO_MAX_NOME 200
#define DONO_MAX_CODIGOPOSTAL 10
#define CARRO_MAX_MATRICULA 15
#define CARRO_MAX_MARCA 30
#define CARRO_MAX_MODELO 30
#define SENSOR_MAX_DESIGNACAO 50
#define SENSOR_MAX_LATITUDE 20
#define SENSOR_MAX_LONGITUDE 20
#define PASSAGEM_MAX_DATAHORA 30
#define MAX_DONOS 1000 // s.a.a.
#define MAX_CARROS 1000 // s.a.a.

/*
 * Representa um Dono (conforme o enunciado: numContribuinte, nome, codPostal).
 * Aqui usamos:
 *  - numeroContribuinte (int)
 *  - nome (string)
 *  - codigoPostal (string)
 */
typedef struct {
    int  numeroContribuinte;
    char nome[DONO_MAX_NOME];
    char codigoPostal[DONO_MAX_CODIGOPOSTAL];
} Dono;

/*
 * Cada node de lista ligada para armazenar Donos.
 */
typedef struct nodeDono {
    Dono               dono;
    struct nodeDono*   next;
} NodeDono;

/*
 * Representa um Carro (equivalente à entidade "Carro" do enunciado).
 *  - matrícula => matricula
 *  - marca => marca
 *  - modelo => modelo
 *  - ano => ano
 *  - numContribuinte do Dono => donoContribuinte
 *  - codVeiculo => idVeiculo
 */
typedef struct {
    char matricula[CARRO_MAX_MATRICULA];
    char marca[CARRO_MAX_MARCA];
    char modelo[CARRO_MAX_MODELO];
    int  ano;
    int  donoContribuinte; // faz a ligação a Dono.numeroContribuinte
    int  idVeiculo;
} Carro;

/*
 * Lista ligada de Carros.
 */
typedef struct nodeCarro {
    Carro             carro;
    struct nodeCarro* next;
} NodeCarro;

/*
 * Representa um Sensor (equivalente a "codSensor", "designacao", "latitude", "longitude").
 */
typedef struct {
    int  idSensor;
    char designacao[SENSOR_MAX_DESIGNACAO];
    char latitude[SENSOR_MAX_LATITUDE];
    char longitude[SENSOR_MAX_LONGITUDE];
} Sensor;

/*
 * Lista ligada de Sensores.
 */
typedef struct nodeSensor {
    Sensor            sensor;
    struct nodeSensor* next;
} NodeSensor;

/*
 * Representa uma Distancia entre dois Sensores:
 *  - idSensor1
 *  - idSensor2
 *  - distancia (float)
 */
typedef struct {
    int   idSensor1;
    int   idSensor2;
    float distancia;
} Distancia;

/*
 * Lista ligada de Distancias.
 */
typedef struct nodeDistancia {
    Distancia             distancia;
    struct nodeDistancia* next;
} NodeDistancia;

/*
 * Representa uma Passagem (equivalente a "Passagem" do enunciado):
 *  - idSensor
 *  - idVeiculo
 *  - dataHora (string)
 *  - tipoRegisto (0=entrada, 1=saída)
 */
typedef struct {
    int  idSensor;
    int  idVeiculo;
    char dataHora[PASSAGEM_MAX_DATAHORA];  // ex.: "12-09-2010_21:35:45.135"
    int  tipoRegisto;   // 0=entrada, 1=saída
} Passagem;

/*
 * Lista ligada de Passagens.
 */
typedef struct nodePassagem {
    Passagem            passagem;
    struct nodePassagem* next;
} NodePassagem;

#endif /* DATA_STRUCTURES_H */
