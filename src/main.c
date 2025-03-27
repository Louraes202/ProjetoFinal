// *
// Compilaçáo e Execução manual, respetivamente:
// gcc -Iinclude -o portagens src/main.c src/read_files.c src/operations.c src/data.c
// ./portagens
// *

#include "data.h"
#include "read_files.h"
#include <stdlib.h>
#include <stdio.h>


int main() {

    NodeDono* listaDonos = NULL;

    // Testar a função
    lerDonos("Dados-Portagens-Trab-Pratico/donos.txt", &listaDonos);
}