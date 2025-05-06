#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "read_files.h"
#include "operations.h"

#ifdef _WIN32
  #include <windows.h>   // SetConsoleCP, SetConsoleOutputCP
#endif


int main(int argc, char *argv[]) {
  NodePassagem* lista = NULL;
  const char *ficheiro;

  if (argc == 2) {
      // ./portagens pass_test.txt
      ficheiro = argv[1];
  }
  else if (argc == 3 && strcmp(argv[1], "--test-passagens")==0) {
      // ./portagens --test-passagens test/passagens_test.txt
      ficheiro = argv[2];
  }
  else {
      // modo normal: usa o ficheiro da pasta de dados
      ficheiro = "passagem.txt";
  }

  clock_t inicio = clock();
  lerPassagens(ficheiro, &lista);
  clock_t fim = clock();
  double tempo_cpu = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de CPU gasto pela lerPassagens(): %.3f s\n", tempo_cpu);

  libertarListaPassagens(&lista);
  return 0;
}
