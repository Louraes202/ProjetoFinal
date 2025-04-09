#ifndef READ_FILES_H
#define READ_FILES_H

#include "data.h"

static void libertarListaDonosParcial(NodeDono** lista);
static void libertarListaCarrosParcial(NodeCarro** lista);

void lerDonos(const char* nomeFicheiro, NodeDono** listaDonos);
void lerCarros(const char* nomeFicheiro, NodeCarro** listaCarros);

#endif