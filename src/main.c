#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <locale.h>
#include "data.h"
#include "read_files.h"
#include "operations.h"

#ifdef _WIN32
  #include <windows.h>
#endif


/**
 * @brief Mostra o menu de opções e retorna a escolha do utilizador.
 */
int mostrarMenu() {
    int opcao;
    
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("=============================================\n");
    printf("     Sistema de Gestao de Portagens\n");
    printf("=============================================\n");
    printf("\n--- Registos ---\n");
    printf(" 1. Registar Dono\n");
    printf(" 2. Registar Carro\n");
    printf("\n--- Listagens e Consultas ---\n");
    printf(" 3. Listar Donos\n");
    printf(" 4. Listar Carros\n");
    printf(" 5. Listar Sensores\n");
    printf(" 6. Listar Veiculos que circularam num periodo\n");
    printf(" 7. Ranking de veiculos por total de Kms\n");
    printf(" 8. Ranking de marcas por total de Kms\n");
    printf("\n--- Analise de Infracoes e Velocidades ---\n");
    printf(" 9. Listar Infracoes de velocidade (>120 km/h)\n");
    printf(" 10. Ranking de veiculos por n. de infracoes\n");
    printf(" 11. Listar velocidades medias por veiculo\n");
    printf(" 12. Ranking de marcas por velocidade media\n");
    printf(" 13. Ranking de donos por velocidade media\n");
    printf(" 14. Velocidade Media por Codigo Postal\n"); 
    printf("\n--- Sistema ---\n");
    printf(" 15. Calcular memoria total ocupada\n");    
    printf(" 16. Exportar dados para CSV\n");             
    printf(" 17. Exportar dados para XML\n");             
    printf("\n 0. Sair\n");
    printf("---------------------------------------------\n");
    printf("Escolha uma opcao: ");

    if (scanf("%d", &opcao) != 1) {
        printf("Opcao invalida. Por favor, insira um numero.\n");
        limparBufferInput();
        return -1; // Retorna -1 para indicar uma opção inválida
    }
    limparBufferInput();
    return opcao;
}


int main(void) {
    // --- Configuração Inicial ---
    setlocale(LC_ALL, "pt_PT.UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // --- Carregamento de Dados (Inicializa Programa) ---
    NodeDono* donos      = NULL;
    NodeCarro* carros     = NULL;
    NodeSensor* sensores   = NULL;
    NodeDistancia* distancias = NULL;
    NodePassagem* passagens  = NULL;

    printf("A carregar base de dados...\n");
    lerDonos("Dados-Portagens-Trab-Pratico/donos.txt", &donos);
    lerCarros("Dados-Portagens-Trab-Pratico/carros.txt", &carros);
    lerSensores("Dados-Portagens-Trab-Pratico/sensores.txt", &sensores);
    lerDistancias("Dados-Portagens-Trab-Pratico/distancias.txt", &distancias);
    lerPassagens("passagem.txt", &passagens);
    printf("Dados carregados com sucesso.\n");
    esperarEnter();

    // --- Loop Principal da Aplicação ---
    int opcao;
    do {
        opcao = mostrarMenu();
        time_t inicio, fim; // Variáveis para períodos de tempo

        switch (opcao) {
            case 1: registarDono(&donos); break;
            case 2:
                registarCarro(&carros, donos); // Passar a lista de donos
                break;
            case 3: imprimirListaDonos(donos); break;
            case 4: imprimirListaCarros(carros); break;
            case 5: imprimirListaSensores(sensores); break;
            case 6: // A ser implementado - Requer array de carros e passagens
                printf("Funcionalidade a ser implementada.\n");
                break;
            case 7: 
                obterPeriodoTempo(&inicio, &fim);
                rankingVeiculos(passagens, distancias, inicio, fim);
                break;
            case 8:
                obterPeriodoTempo(&inicio, &fim);
                rankingPorMarca(passagens, distancias, carros, inicio, fim);
                break;
            case 9:
                obterPeriodoTempo(&inicio, &fim);
                listarInfracoes(carros, passagens, distancias, inicio, fim);
                break;
            case 10:
                obterPeriodoTempo(&inicio, &fim);
                rankingInfraVeiculos(passagens, distancias, carros, inicio, fim);
                break;
            case 11:
                obterPeriodoTempo(&inicio, &fim);
                velocidadesMedias(passagens, distancias, carros, inicio, fim);
                break;
            case 12:
                obterPeriodoTempo(&inicio, &fim);
                rankingMarcasVelocidade(carros, passagens, distancias, inicio, fim);
                break;
            case 13:
                obterPeriodoTempo(&inicio, &fim); 
                rankingDonosVelocidade(donos, carros, passagens, distancias, inicio, fim);
                break;

            case 14: 
            {
                char codPostalInput[DONO_MAX_CODIGOPOSTAL];
                printf("\n--- Calcular Velocidade Media por Codigo Postal ---\n");
                do {
                    lerString("Introduza o Codigo Postal (formato XXXX-XXX): ", codPostalInput, sizeof(codPostalInput));
                    if (!validarCodigoPostal(codPostalInput)) {
                        printf("Erro: Formato de codigo postal invalido. Tente novamente.\n");
                    }
                } while (!validarCodigoPostal(codPostalInput));

                double velMedia = velocidadeMediaPorCodigoPostal(codPostalInput, donos, carros, passagens, distancias);
                if (velMedia < 0) {
                    printf("Nao foi possivel calcular a velocidade media para o codigo postal %s (sem dados ou viagens validas).\n", codPostalInput);
                } else {
                    printf("A velocidade media dos condutores com codigo postal %s e: %.2f km/h\n", codPostalInput, velMedia);
                }
                break;
            }
            case 15:
                printf("Memoria total ocupada: %zu bytes\n", calcularMemoriaTotal(donos, carros, sensores, distancias, passagens));
                break;
            case 16: 
                exportarDadosCSV(donos, carros, sensores, distancias, passagens);
                break;
            case 17: 
                exportarDadosXML(donos, carros, sensores, distancias, passagens);
                break;
            case 0:
                printf("A sair do programa...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            esperarEnter();
        }

    } while (opcao != 0);

    // --- Libertação de Memória (Finalizar Programa) ---
    libertarListaDonos(&donos);
    libertarListaCarros(&carros);
    libertarListaSensores(&sensores);
    libertarListaDistancias(&distancias);
    libertarListaPassagens(&passagens);

    printf("Programa terminado.\n");
    return 0;
}