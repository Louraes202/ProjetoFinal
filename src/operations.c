// operations.c

#include <stdio.h>
#include "operations.h"

// --- Donos ---
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
