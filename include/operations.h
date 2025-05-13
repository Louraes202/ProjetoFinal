#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "data.h"

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

#endif // OPERATIONS_H