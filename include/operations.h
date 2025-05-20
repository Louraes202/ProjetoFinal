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

int parseTimestampCustom(const char *dataHora, struct tm *tm);
time_t parseTimestamp(const char *dataHora);
double obterDistancia(NodeDistancia* lista, int id1, int id2);
int cmpVeiculoRanking(const void *a, const void *b);
void rankingVeiculos(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, time_t inicio, time_t fim);

int cmpMarcaRanking(const void *a, const void *b);
void rankingPorMarca(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);

void listarInfracoes(NodePassagem* listaPassagens, NodeDistancia* listaDistancias, NodeCarro* listaCarros, time_t inicio, time_t fim);

#endif // OPERATIONS_H