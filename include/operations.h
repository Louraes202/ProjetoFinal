#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "data.h"
#include <time.h>
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

// funçoes de memoria
size_t calcularMemoriaTotal(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, NodeDistancia* listaDistancias, NodePassagem* listaPassagens);

// funções de registo
void registarDono(NodeDono** listaDonos);
void registarCarro(NodeCarro** listaCarros);
void registarSensor(NodeSensor** listaSensores);
void registarDistancia(NodeDistancia** listaDistancias);
void registarPassagem(NodePassagem** listaPassagens);

bool validarNIF(int nif);
bool validarMatricula(const char *m);
bool validarCodigoPostal(const char *cp);

void ordenar_donos_NIF(Dono *dono, int total);
void ordenar_carros(Carro *carros, int total, int (*comparar)(const Carro *, const Carro *));
int comparar_matricula(const Carro *a, const Carro *b);
int comparar_marca(const Carro *a, const Carro *b);
int comparar_modelo(const Carro *a, const Carro *b);
int verificacao_periodo(const char *dataHora, const char *inicio, const char *fim);
int veiculo_ja_adicionado(const int lista[], int total, int id);
void mostrar_veiculos_periodo(Passagem passagens[], int total_passagens, Carro carros[], int total_carros);

time_t parseTimestamp(const char *dataHora);
double obterDistancia(NodeDistancia* lista, int id1, int id2);
void rankingVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);

int cmpMarcaRanking(const void *a, const void *b);
void rankingPorMarca(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);
int cmpVeiculoRanking(const void *a, const void *b);

time_t parseTimestamp(const char *dataHora);
double obterDistancia(NodeDistancia* lista, int id1, int id2);
double calcularVelocidadeInfracao(NodePassagem* passagens, NodeDistancia* listaDistancias);
double calcularVelocidadeMediaPonderada(NodePassagem* passagens, NodeDistancia* listaDistancias);
NodePassagem* filtrarPassagens(NodePassagem* lista, time_t inicio, time_t fim);
HashTablePassagens* criarHashTablePassagens(size_t numBuckets);
void inserirPassagemHash(HashTablePassagens* ht, const Passagem* passagem);
NodePassagem* pesquisarPassagensParaVeiculo(HashTablePassagens* ht, int idVeiculo);
void libertarHashTablePassagens(HashTablePassagens* ht);
void inserirInfracao(TreeNodeInfracao** root, const char* matricula, double velocidadeMedia);

TreeNodeInfracao** armazenarInfracoes(TreeNodeInfracao* arvInfra, int* total);
void libertarArvoreInfracoes(TreeNodeInfracao* arvInfra);


void listarInfracoes(NodeCarro* listaCarros, NodePassagem* listaPassagens,
                     NodeDistancia* listaDistancias, time_t inicio, time_t fim);


void rankingInfraVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);

void velocidadesMedias(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);

void rankingMarcasVelocidade(NodeCarro* listaCarros, NodePassagem* listaPassagens, 
                             NodeDistancia* listaDistancias, time_t inicio, time_t fim);

void rankingDonosVelocidade(NodeDono* listaDonos, NodeCarro* listaCarros, NodePassagem* listaPassagens, 
                          NodeDistancia* listaDistancias, time_t inicio, time_t fim);

void exportarDadosCSV(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, 
                      NodeDistancia* listaDistancias, NodePassagem* listaPassagens);

void exportarDadosXML(NodeDono* listaDonos, NodeCarro* listaCarros, NodeSensor* listaSensores, 
                      NodeDistancia* listaDistancias, NodePassagem* listaPassagens);

void debugVeiculo(int idVeiculoDebug, NodeCarro* listaCarros, NodePassagem* listaPassagens, NodeDistancia* listaDistancias);


#endif // OPERATIONS_H