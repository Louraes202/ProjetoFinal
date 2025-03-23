#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/*
 * Representa um Owner (equivalente a "Dono" do enunciado).
 * Campos do enunciado: numContribuinte, nome, codPostal 
 * Passamos a usar: taxId, name, postalCode
 */
typedef struct {
    int  taxId;              // em vez de numContribuinte
    char name[50];           // em vez de nome
    char postalCode[10];     // em vez de codPostal
} Owner;

/*
 * Cada nó de lista para armazenar Owners (Donos).
 * Substituímos 'nodo' por 'node' e 'prox' por 'next'.
 */
typedef struct nodeOwner {
    Owner               owner;
    struct nodeOwner*   next;
} NodeOwner;

/*
 * Representa um Car (equivalente a "Carro" do enunciado).
 * Matrícula => licensePlate
 * marca => brand
 * modelo => model
 * ano => year
 * dono => taxIdOwner (poderia ser ownerId, mas definimos taxIdOwner)
 * codVeiculo => vehicleId
 */
typedef struct {
    char licensePlate[15];
    char brand[30];
    char model[30];
    int  year;
    int  taxIdOwner;   // referência ao Owner (taxId), 
    int  vehicleId;
} Car;

/*
 * Lista ligada de Cars
 */
typedef struct nodeCar {
    Car              car;
    struct nodeCar*  next;
} NodeCar;

/*
 * Representa um Sensor (codSensor => sensorId,
 * designacao => designation, latitude, longitude)
 */
typedef struct {
    int  sensorId;
    char designation[50];
    char latitude[20];
    char longitude[20];
} Sensor;

/*
 * Lista ligada de Sensors
 */
typedef struct nodeSensor {
    Sensor            sensor;
    struct nodeSensor* next;
} NodeSensor;

/*
 * Representa a Distance entre dois sensores:
 * codSensor1 => sensorId1
 * codSensor2 => sensorId2
 * distancia => distance
 */
typedef struct {
    int   sensorId1;
    int   sensorId2;
    float distance;
} Distance;

/*
 * Lista ligada de Distance
 */
typedef struct nodeDistance {
    Distance             distance;
    struct nodeDistance* next;
} NodeDistance;

/*
 * Representa uma Passage (equivalente a "Passagem"):
 * idSensor => sensorId
 * codVeiculo => vehicleId
 * dataHora => dateTime
 * tipoRegisto => recordType (0=entrada, 1=saída)
 */
typedef struct {
    int  sensorId;
    int  vehicleId;
    char dateTime[30];  // "12-09-2010_21:35:45.135"
    int  recordType;    // 0=entrada, 1=saída
} Passage;

/*
 * Lista ligada de Passages
 */
typedef struct nodePassage {
    Passage            passage;
    struct nodePassage* next;
} NodePassage;

#endif /* DATA_STRUCTURES_H */
