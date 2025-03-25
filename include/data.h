#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/*
 * Representa um Dono (conforme o enunciado: numContribuinte, nome, codPostal).
 * Aqui usamos:
 *  - numeroContribuinte (int)
 *  - nome (string)
 *  - codigoPostal (string)
 */
typedef struct {
    int  numeroContribuinte;
    char nome[50];
    char codigoPostal[10];
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
    char matricula[15];
    char marca[30];
    char modelo[30];
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
    char designacao[50];
    char latitude[20];
    char longitude[20];
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
    char dataHora[30];  // ex.: "12-09-2010_21:35:45.135"
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
