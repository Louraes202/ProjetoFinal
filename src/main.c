#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "read_files.h"

#ifdef _WIN32
  #include <windows.h>   // SetConsoleCP, SetConsoleOutputCP
#endif


// --- main apenas para sensores ---
int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif


}