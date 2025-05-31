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

  lerDistancias("Dados-Portagens-Trab-Pratico/distancias.txt", &distancias);
  lerPassagens(ficheiro, &passagens);
  lerCarros("Dados-Portagens-Trab-Pratico/carros.txt", &carros);
  lerDonos("Dados-Portagens-Trab-Pratico/donos.txt", &donos);
  lerSensores("Dados-Portagens-Trab-Pratico/sensores.txt", &sensores);

  // Definir intervalo de tempo para filtrar as infrações (exemplo)
  char inicioStr[] = "31-01-2003 23:00:00";
  char fimStr[]    = "31-12-2020 23:59:59";
  time_t inicio = parseTimestamp(inicioStr);
  time_t fim    = parseTimestamp(fimStr);

  // Testar a nova função do Requisito 18
  exportarDadosXML(donos, carros, sensores, distancias, passagens);

  // Libertar memória
  libertarListaPassagens(&passagens);
  libertarListaDistancias(&distancias);
  libertarListaCarros(&carros);
  libertarListaSensores(&sensores);
  libertarListaDonos(&donos);


  
  return 0;

}
