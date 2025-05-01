#ifndef READ_FILES_H
#define READ_FILES_H

#include "data.h"

static void libertarListaDonosParcial(NodeDono** lista);
static void libertarListaCarrosParcial(NodeCarro** lista);
static void libertarListaSensoresParcial(NodeSensor** lista);

void lerDonos(const char* nomeFicheiro, NodeDono** listaDonos);
void lerCarros(const char* nomeFicheiro, NodeCarro** listaCarros);
void lerSensores(const char* nomeFicheiro, NodeSensor** listaSensores);
void lerDistancias(const char* nomeFicheiro, NodeDistancia** listaDistancias);
void lerPassagens(const char* nomeFicheiro, NodePassagem** listaPassagens);


void ordenar_donos(const char *ficheiro);
void ordenar_por_nome(Dono *donos, int total);


#endif