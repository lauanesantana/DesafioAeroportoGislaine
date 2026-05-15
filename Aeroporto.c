#include <stdio.h> 
#include "Aeroporto.h"
#include <stdlib.h> 


struct tipoNo { 
    struct Aviao aviao; 
    struct tipoNo *prox; 
}; 

struct tipoFila { 
    struct tipoNo *inicio; 
    struct tipoNo *fim; 
    int qtd; 
};

typedef struct tipoNo noFila; 



Fila* criaPista () { 
    Fila* pista = (Fila*) malloc (sizeof(Fila));
    
    if(pista == NULL) 
        return NULL;

    if (pista != NULL) { 
        pista->fim = NULL; 
        pista->inicio = NULL; 
        pista->qtd = 0; 
    }

    return pista; 
}



int insereAviao (Fila* pista, struct Aviao aviao){
    if(pista == NULL){
        return 0;
    }


    noFila* novoAviao = (noFila*) malloc(sizeof(noFila));
    if(novoAviao == NULL){
        return 0;
    }

    novoAviao->aviao;

    if(pista->inicio == NULL){
        novoAviao->prox = NULL;
        pista->inicio = novoAviao;
        return 1;
    
    } else {
        noFila *ant, *atual = pista->inicio;

        while(atual != NULL && atual->aviao.emergencia < aviao.emergencia){
            ant = atual;
            atual = atual->prox;
        }

        if(atual == pista->inicio){
            novoAviao->prox = pista->inicio;
            pista->inicio = novoAviao;
        
        } else {
            novoAviao->prox = atual;
            ant->prox = novoAviao;
        }

        return 1;
    }
}



int removeAviao (Fila* pista){
    if(pista == NULL){
        return 0;
    }

    noFila *auxiliar = pista->inicio;
    pista->inicio = pista->inicio->prox;

    if(pista->inicio == NULL){
        pista->fim = NULL;
        pista->qtd = 0;
    }

    free(auxiliar);
    return 1;
}



int consultaPista (Fila* pista, struct Aviao *aviao){
    if(pista == NULL){
        return 0;
    }

    if(pista->inicio == NULL){
        return 0;
    }

    *aviao = pista->inicio->aviao;
    return 1;
}



int buscarAviao (Fila* pista, int numVoo, struct Aviao *aviao){
    if(pista == NULL){
        return 0;
    }

    if(pista->inicio == NULL){
        return 0;
    }

    noFila *auxiliar = pista->inicio;
    while(auxiliar != NULL || auxiliar->aviao.numVoo != numVoo){
        auxiliar = auxiliar->prox;
    }

    if(auxiliar == NULL){
        return 0;
    }

    *aviao = auxiliar->aviao;
    return 1;
}



int atualizarPrioridade (Fila* pista, int numVoo){
    if(pista == NULL){
        return 0;
    }


    noFila *auxiliar = pista->inicio;

    while(auxiliar != NULL || auxiliar->aviao.numVoo != numVoo){
        auxiliar = auxiliar->prox;
    }

    if(auxiliar == NULL){
        return 0;
    }


    int nivelP = 0;

    printf("\n Qual é o nível de prioridade para pouso? \n");
    printf("1. falha mecânica - 2. emergência médica - 3. militar - 4.outras: ");

    scanf("%d", &nivelP);


    noFila *atual = auxiliar;
    atual->aviao.emergencia = nivelP;

    free(auxiliar);
    insereAviao(pista, atual->aviao);
    
    return 1;
}




//evento dinamico pistaLIberada



//Acionada quando uma pista esta liberada, logo, ja passou pela funcao apagaFila/removeElemento 
int pistaLiberada (Fila* pista) { 

    if (pista != NULL) { 
        printf ("Nao ha pista liberadas no momento...\n"); 
    }
    else { 
    printf ("Pista disponivel para pouso\n"); 

    /* puxa no main: insereAVviao (Fila* pista, struct Aviao aviao); */  
    } 
    return 1; 
}



int aviaoSemCombustivel (Fila* pista, struct Aviao aviao) { 

    noFila *aux = pista->inicio; 

    if (pista != NULL) { 
        return; 
    }
    if (pista->inicio == NULL) { 
        return; 
    }

    if (aux->aviao.combustivel == 0) { 
        printf ("\nEstamos abastecendo o aviao... um momento...\n"); 
        Sleep (2000); 

        aux->aviao.combustivel = 100; 

        printf ("Aviao abastecido, o nivel de combustivel esta em 100%%\n"); 
    }
    

    //conferir com outras funcoes
    //pista->inicio = pista->prox
}



void exibePista (Fila* pista, int quant){

    noFila* numPista = pista->inicio; 
    
    if (pista == NULL) { 
        printf ("\nOps... Essa pista está inativa no momento...\n");
        return; 
    }

    if (pista->inicio == NULL) { 
        printf ("\nOps... Não há nenhum avião pousado na pista...\n");
        return;  
    }

    while (numPista != NULL) { 
        printf (" = = = = PISTA %d = = = = \n", quant); 
        printf ("[ Nome da Companhia: %s ]", numPista->aviao.nomeCompanhia); 
        printf (" | [ Numero do Voo: %d ]", numPista->aviao.numVoo); 
        printf (" | [ Nivel de Combustivel: %d%%]\n", numPista->aviao.combustivel); 
        printf (" | [ Classificacao de Emergencia: %d ]", numPista->aviao.emergencia); 
        printf (" | [ Possui carga perigosa?");  
            if (numPista->aviao.cargaPerigosa == 1) { 
                printf (" Sim]\n"); 
            } else if (numPista->aviao.cargaPerigosa== 2)
                printf (" Nao]\n");  
        printf (" = = = = = = = = = = = = = \n"); 

        numPista = numPista->prox;  
    }
}



void apagaFila (Fila* pista){

    noFila* aux; 

    while (pista->inicio != NULL) { 
        aux = pista->inicio; 
        pista->inicio = pista->inicio->prox; 
        free(aux); 
    }
    free(pista); 
}