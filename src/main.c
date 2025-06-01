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
    printf(" 3. Registar Sensor\n");                         // ADICIONADO
    printf(" 4. Registar Distancia entre Sensores\n");       // ADICIONADO
    printf(" 5. Registar Passagem\n");                       // ADICIONADO
    printf("\n--- Listagens e Consultas ---\n");
    printf(" 6. Listar Donos (Ordem de Registo/NIF)\n");     // Ajustado ou Requisito 5
    printf(" 7. Listar Donos (Ordem Alfabética)\n");         // Requisito 3
    printf(" 8. Listar Carros\n");
    printf(" 9. Listar Sensores\n");
    printf(" 10. Listar Veiculos que circularam num periodo (Ord. Matricula)\n"); // Req 7
    printf(" 11. Ranking de veiculos por total de Kms\n");                       // Req 8
    printf(" 12. Ranking de marcas por total de Kms\n");                         // Req 9
    printf(" 13. Determinar Marca Mais Comum\n");                                // ADICIONADO (Req 16)
    printf("\n--- Analise de Infracoes e Velocidades ---\n");
    printf(" 14. Listar Infracoes de velocidade (>120 km/h)\n");                 // Req 10
    printf(" 15. Ranking de veiculos por n. de infracoes\n");                    // Req 11
    printf(" 16. Listar velocidades medias por veiculo\n");                      // Req 12
    printf(" 17. Ranking de marcas por velocidade media\n");                     // Req 13
    printf(" 18. Ranking de donos por velocidade media\n");                      // Req 14
    printf(" 19. Velocidade Media por Codigo Postal\n");                         // Req 15
    printf("\n--- Sistema ---\n");
    printf(" 20. Calcular memoria total ocupada\n");                              // Req 4
    printf(" 21. Exportar dados para CSV\n");                                    // Req 17
    printf(" 22. Exportar dados para XML\n");                                    // Req 18
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
            case 3: registarSensor(&sensores); break;
            case 4: registarDistancia(&distancias, sensores); break;
            case 5: registarPassagem(&passagens, sensores, carros); break;
            case 6: 
                // Se quiser implementar listagem por NIF, seria aqui
                // Por agora, pode chamar a imprimirListaDonos que tem (ordem de registo)
                // ou criar imprimirListaDonosOrdemNIF e chamá-la.
                imprimirListaDonos(donos); // Temporariamente, ou a sua função de ordenação por NIF
                break;
            case 7: imprimirListaDonosOrdemAlfabetica(donos); break;
            case 8: imprimirListaCarros(carros); break;
            case 9: imprimirListaSensores(sensores); break;
            case 10: 
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    listarVeiculosPorPeriodo(passagens, carros, inicio, fim);
                }
                break;
            case 11: 
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    rankingVeiculos(passagens, distancias, inicio, fim);
                }
                break;
            case 12:
                obterPeriodoTempo(&inicio, &fim);
                rankingPorMarca(passagens, distancias, carros, inicio, fim);
                break;
            case 13: // Marca mais comum
                determinarMarcaMaisComum(carros);
                break;
            // ... continuar a ajustar a numeração para os restantes cases ...
            // case 14 para listar infrações (antigo 10)
            case 14: 
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    listarInfracoes(carros, passagens, distancias, inicio, fim);
                }
                break;
            // case 15 para ranking infrações (antigo 11)
            case 15: 
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    rankingInfraVeiculos(passagens, distancias, carros, inicio, fim);
                }
                break;
            // ... e assim por diante
            case 16: // Velocidades médias por veículo (antigo 12)
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    velocidadesMedias(passagens, distancias, carros, inicio, fim);
                }
                break;
            case 17: // Ranking de marcas por velocidade média (antigo 13)
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    rankingMarcasVelocidade(carros, passagens, distancias, inicio, fim);
                }
                break;
            case 18: // Ranking de donos por velocidade média (antigo 14)
                obterPeriodoTempo(&inicio, &fim);
                if (inicio != -1 && fim != -1) {
                    rankingDonosVelocidade(donos, carros, passagens, distancias, inicio, fim);
                }
                break;
            case 19: // Determinar marca mais comum (antigo 15)
                determinarMarcaMaisComum(carros);
                break;

            case 20: // Calcular memória (antigo 16)
                printf("Memoria total ocupada: %zu bytes\n", calcularMemoriaTotal(donos, carros, sensores, distancias, passagens));
                break;
            case 21: // Exportar CSV (antigo 17)
                exportarDadosCSV(donos, carros, sensores, distancias, passagens);
                break;
            case 22: // Exportar XML (antigo 18)
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