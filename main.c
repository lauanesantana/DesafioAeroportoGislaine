#include <stdio.h>
#include <stdlib.h>
#include "Aeroporto.h"

int main(){

     Fila *fila = criaFila();

    if(fila == NULL)
    {
        printf("Erro ao criar fila!\n");
        return 1;
    }

    int opcao;
    struct Aviao aviao;


    do{
        printf("\n\n=======================================\n");
        printf("Torre de Controle - Aeroporto IFSP\n");
        printf("=======================================\n\n");
        printf("| [1]- Inserir Avião  |\n");
        printf("| [2]- Remover Avião  |\n");
        printf("| [3]- Consultar Fila |\n");
        printf("| [4]- Buscar Avião   |\n");
        printf("| [5]- Prioridade     |\n");
        printf("| [6]- Exibir Pista   |\n");
        printf("| [7]- Apagar Fila    |\n");
        printf("| [0]- Sair           |\n");

        switch (opcao){
            case 1:

            printf("\nInforme o nome da companhia do voo: ");
            scanf("");

            printf("\nInforme o número do voo: ");


            printf("\nInforme o nível do combustível do avião em porcentagem(0%% - 100%%): ");


            printf("\nInforme : ");//EMERGENCIA
            printf("\nInforme : ");//CARGA PERIGOSA




            if(insereFila(fila, aviao)){
                    printf("Avião inserido com sucesso!\n");
                }else{
                    printf("Erro ao inserir o avião!\n");
                }
            break;

            case 2:
                if(removeAviao(pista)){


                    printf("Avião removido com sucesso\n");
                }else{
                printf("Fila vazia\n");
                }
            break;

            case 3:
                if(consultaPista){
                    printf("Primeiro avião a fila é: ");
                }else{
                    printf("Fila vazia");
                }
            break;

            case 4:
                int buscarAviao (Fila* pista, int numVoo, struct Aviao *aviao); 

            break;

            case 5:
                int atualizarPrioridade (Fila* pista, int numVoo);
            break;

            case 6:
                exibePista(fila, 1);
                exibePista(fila, 2);
                exibePista(fila, 3);
                exibePista(fila, 4);
                exibePista(fila, 5);
            break;

            case 7:
                apagarFila(fila);

                fila = criaFila();

                if(fila != NULL){
                    printf("Fila liberada com sucesso!\n");
                }else{
                    printf("Erro ao recriar fila!\n");
                    return 1;
                }
            break;

            case 0:
                printf("Encerrando programa....");
            break;

            default:
                    printf("Opção inválida escolha outra opção");
            break;
        }
    }while(opcao != 0);
    

    apagarFila(pista);

    return 0;
}

