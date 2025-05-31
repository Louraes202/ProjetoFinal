#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "data.h"
#include <time.h>
#include <stdbool.h>

// -- Funções de Input e Output Básicas do menu --
void limparBufferInput();
void esperarEnter();
void obterPeriodoTempo(time_t* inicio, time_t* fim);

// --- Funções Auxiliares de Input e Pesquisa ---
void lerString(const char* prompt, char* buffer, int tamanho);
NodeDono* pesquisarDonoPorNIF(NodeDono* listaDonos, int nif);
NodeCarro* pesquisarCarroPorId(NodeCarro* listaCarros, int idVeiculo);
NodeSensor* pesquisarSensorPorId(NodeSensor* listaSensores, int idSensor);


// --- Funções de Impressão e Libertação ---
void imprimirListaDonos(NodeDono* lista);
void imprimirListaCarros(NodeCarro* lista);
void imprimirListaSensores(NodeSensor* lista);
void imprimirListaDistancias(NodeDistancia* lista);
void imprimirListaPassagens(NodePassagem* lista);

void libertarListaDonos(NodeDono** lista);
void libertarListaCarros(NodeCarro** lista);
void libertarListaSensores(NodeSensor** lista);
void libertarListaDistancias(NodeDistancia** lista);
void libertarListaPassagens(NodePassagem** lista);


// --- Funções de Registo ---
// ALTERADO: Assinaturas atualizadas para validação
void registarDono(NodeDono** listaDonos);
void registarCarro(NodeCarro** listaCarros, NodeDono* listaDonos);
void registarSensor(NodeSensor** listaSensores);
void registarDistancia(NodeDistancia** listaDistancias, NodeSensor* listaSensores);
void registarPassagem(NodePassagem** listaPassagens, NodeSensor* listaSensores, NodeCarro* listaCarros);


// --- Funções de Validação ---
bool validarNIF(int nif);
bool validarMatricula(const char *m);
bool validarCodigoPostal(const char *cp);


// --- Funções Principais do Projeto ---
size_t calcularMemoriaTotal(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, NodeDistancia* listaDistancias, NodePassagem* listaPassagens);
time_t parseTimestamp(const char *dataHora);
double obterDistancia(NodeDistancia* lista, int id1, int id2);
void rankingVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);
void rankingPorMarca(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);
void listarInfracoes(NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);
void rankingInfraVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);
void velocidadesMedias(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);
void rankingMarcasVelocidade(NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);
void rankingDonosVelocidade(NodeDono* listaDonos, NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);
void exportarDadosCSV(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, NodeDistancia* listaDistancias, NodePassagem* listaPassagens);
void exportarDadosXML(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, NodeDistancia* listaDistancias, NodePassagem* listaPassagens);


#endif // OPERATIONS_H