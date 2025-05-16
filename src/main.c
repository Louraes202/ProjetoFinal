#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <locale.h>
#include "data.h"
#include "read_files.h"
#include "operations.h"

#ifdef _WIN32
  #include <windows.h>   // SetConsoleCP, SetConsoleOutputCP
#endif


int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "pt_PT.UTF-8");

  #ifdef _WIN32
      SetConsoleOutputCP(CP_UTF8);
  #endif

  // Variáveis do main
  NodePassagem* lista = NULL;
  const char *ficheiro;


  // Testes manuais
  if (argc == 2) {
      // ./portagens pass_test.txt
      ficheiro = argv[1];
  }
  // Testes Automáticos (Gh Actions)
  else if (argc == 3 && strcmp(argv[1], "--test-donos") == 0) {
      NodeDono* listaDonos = NULL;  // ← necessário!
      lerDonos(argv[2], &listaDonos);
      imprimirListaDonos(listaDonos);
      libertarListaDonos(&listaDonos);
      return 0;
  }
  // Funcionamento normal, sem inputs de teste
  else {
      // modo normal: usa o ficheiro da pasta de dados
      ficheiro = "passagem.txt";
  }

  // Core
  NodeDono*      donos      = NULL;
  NodeCarro*     carros     = NULL;
  NodeSensor*    sensores   = NULL;
  NodeDistancia* distancias = NULL;
  NodePassagem*  passagens  = NULL;

  printf("=== Teste de registos ===\n\n");

  // 1) Donos
  printf("-- Registar 2 donos --\n");
  registarDono(&donos);
  registarDono(&donos);
  printf("\nLista de Donos:\n");
  imprimirListaDonos(donos);

  // 2) Carros
  printf("\n-- Registar 2 carros --\n");
  registarCarro(&carros);
  registarCarro(&carros);
  printf("\nLista de Carros:\n");
  imprimirListaCarros(carros);

  // 3) Sensores
  printf("\n-- Registar 2 sensores --\n");
  registarSensor(&sensores);
  registarSensor(&sensores);
  printf("\nLista de Sensores:\n");
  imprimirListaSensores(sensores);

  // 4) Distâncias
  printf("\n-- Registar 2 distâncias --\n");
  registarDistancia(&distancias);
  registarDistancia(&distancias);
  printf("\nLista de Distâncias:\n");
  imprimirListaDistancias(distancias);

  // 5) Passagens
  printf("\n-- Registar 2 passagens --\n");
  registarPassagem(&passagens);
  registarPassagem(&passagens);
  printf("\nLista de Passagens:\n");
  imprimirListaPassagens(passagens);

  // libertar tudo
  printf("\n=== Libertar memória ===\n");
  libertarListaDonos(&donos);
  libertarListaCarros(&carros);
  libertarListaSensores(&sensores);
  libertarListaDistancias(&distancias);
  libertarListaPassagens(&passagens);

  return 0;

}
