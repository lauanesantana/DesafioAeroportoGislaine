#include <stdio.h>
#include <stdlib.h>
#include "Aeroporto.h"

int main() {

    Fila *fila = criaPista();
    Fila *pistaDecolagem = criaPista();

    if(fila == NULL) {

        printf("Erro ao criar fila!\n");
        return 1;
    }

    int opcao;
    int numeroBusca;

    struct Aviao aviao;

    do {

        printf("\n=======================================\n");
        printf(" Torre de Controle - Aeroporto IFSP\n");
        printf("=======================================\n");

        printf("[1] Inserir Aviao\n");
        printf("[2] Remover Aviao\n");
        printf("[3] Consultar Primeiro Aviao\n");
        printf("[4] Buscar Aviao\n");
        printf("[5] Atualizar Prioridade\n");
        printf("[6] Exibir Pista\n");
        printf("[7] Apagar Fila\n");
        printf("[8] Liberar Decolagem\n");
        printf("[0] Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                printf("\nNome da companhia: ");
                scanf("%s", aviao.nomeCompanhia);

                printf("Numero do voo: ");
                scanf("%d", &aviao.numVoo);

                printf("Combustivel (0-100): ");
                scanf("%d", &aviao.combustivel);

                printf("\n[0] Sem Emergencia\n");
                printf("[1] Emergencia Medica\n");
                printf("[2] Emergencia Militar\n");
                printf("[3] Emergencia Mecanica\n");

                printf("Nivel de emergencia: ");
                scanf("%d", &aviao.emergencia);

                printf("\n[1] Sim\n");
                printf("[2] Nao\n");

                printf("Carga perigosa: ");
                scanf("%d", &aviao.cargaPerigosa);

                if(insereAviao(fila, aviao)) {

                    printf("\nAviao inserido com sucesso!\n");

                } else {

                    printf("\nErro ao inserir aviao!\n");
                }

            break;

            case 2:

                if(removeAviao(fila)) {

                    printf("\nAviao removido com sucesso!\n");

                } else {

                    printf("\nFila vazia!\n");
                }

            break;

            case 3:

                if(consultaPista(fila, &aviao)) {

                    printf("\nPrimeiro aviao da fila:\n");
                    printf("Companhia: %s\n", aviao.nomeCompanhia);
                    printf("Voo: %d\n", aviao.numVoo);

                } else {

                    printf("\nFila vazia!\n");
                }

            break;

            case 4:

                printf("\nDigite o numero do voo: ");
                scanf("%d", &numeroBusca);

                if(buscarAviao(fila, numeroBusca, &aviao)) {

                    printf("\nAviao encontrado!\n");
                    printf("Companhia: %s\n", aviao.nomeCompanhia);

                } else {

                    printf("\nAviao nao encontrado!\n");
                }

            break;

            case 5:

                printf("\nDigite o numero do voo: ");
                scanf("%d", &numeroBusca);

                if(atualizarPrioridade(fila, numeroBusca)) {

                    printf("\nPrioridade atualizada!\n");

                } else {

                    printf("\nAviao nao encontrado!\n");
                }

            break;

            case 6:

                exibePista(fila, 1);
                exibePista(fila, 2);
                exibePista(fila, 3);
                exibePista(fila, 4);
                exibePista(fila, 5);

            break;

            case 7:

                apagaFila(fila);

                fila = criaPista();

                printf("\nFila apagada com sucesso!\n");

            break;

            case 8:

                PistaParaDecolagem(fila, pistaDecolagem);

            break;

            case 0:

                printf("\nEncerrando sistema...\n");

            break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    apagaFila(fila);
    apagaFila(pistaDecolagem);

    return 0;
}