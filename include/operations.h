#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "data.h"
#include <stdbool.h>

// imprime listas (já existentes)
void imprimirListaDonos(NodeDono* lista);
void imprimirListaCarros(NodeCarro* lista);
void imprimirListaSensores(NodeSensor* lista);
void imprimirListaDistancias(NodeDistancia* lista);
void imprimirListaPassagens(NodePassagem* lista);

// liberta listas
void libertarListaDonos(NodeDono** lista);
void libertarListaCarros(NodeCarro** lista);
void libertarListaSensores(NodeSensor** lista);
void libertarListaDistancias(NodeDistancia** lista);
void libertarListaPassagens(NodePassagem** lista);

// funções de registo
void registarDono(NodeDono** listaDonos);
void registarCarro(NodeCarro** listaCarros);
void registarSensor(NodeSensor** listaSensores);
void registarDistancia(NodeDistancia** listaDistancias);
void registarPassagem(NodePassagem** listaPassagens);

bool validarNIF(int nif);
bool validarMatricula(const char *m);
bool validarCodigoPostal(const char *cp);

int parseTimestampCustom(const char *dataHora, struct tm *tm);
time_t parseTimestamp(const char *dataHora);
double obterDistancia(NodeDistancia* lista, int id1, int id2);
int cmpVeiculoRanking(const void *a, const void *b);
void rankingVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);

#endif // OPERATIONS_H