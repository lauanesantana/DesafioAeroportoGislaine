#include <stdio.h> 
#include "Aeroporto.h"
#include <stdlib.h> 
#include <windows.h>


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
    /*Lauane: add essa conferencia para torar mais ''real'' e tornar nossas emergencias mais no sentido medico/mecanico e carga perigosa, mas da para tirar tb ok? */
    if (aviao.combustivel == 0) {
        printf("\n[ALERTA INTERCEPTADO] Voo %d tentou entrar na fila com 0%% de combustivel!\n", aviao.numVoo);
        printf("Direcionando imediatamente para reabastecimento... um momento...\n");
        Sleep(2000); 
        
        aviao.combustivel = 100; 
        printf("Aviao abastecido com sucesso antes de entrar na fila de espera\n");
    }

    noFila* novoAviao = (noFila*) malloc(sizeof(noFila));
    if(novoAviao == NULL){
        return 0;
    }

    novoAviao->aviao = aviao;
    novoAviao->prox = NULL; /*Lauane: add aqui o rabinho dele, mas nao sei se precisa */

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

        pista->qtd++;/*Lauane: alguem da uma olhadinha aqui se makes sense esse qtd*/ 
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
    /*printf("1. falha mecânica - 2. emergência médica - 3. militar - 4.outras: ");*/ 
    printf("\n[01 - Emergência médica]\n"); 
    printf("\n[02 - Emergência militar]\n"); 
    printf("\n[03 - Emergência mecânica no avião]\n"); 

    scanf("%d", &nivelP);


    noFila *atual = auxiliar;
    atual->aviao.emergencia = nivelP;

    free(auxiliar);
    insereAviao(pista, atual->aviao);
    
    return 1;
}

//evento dinamico pistaLIberada

//Lauane: Acionada quando uma pista esta liberada, logo, ja passou pela funcao apagaFila/removeElemento 
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

int aviaoSemCombustivel (Fila* pista) { 

    if (pista == NULL) 
        return;
     
    if (pista->inicio == NULL) { 
        return; 
    }
    noFila *aux = pista->inicio; 

    if (aux->aviao.combustivel == 0) { 
        /* Lauane: aqui pesquisei e descobri que tem como fazer o pc emitir sons de bip, como se fossem aqueles barulhinhos de radio, mas nao consegui testar para ver se funciona*/
        Beep(1500, 150); // Frequência aguda, duração curta
        Sleep(100);
        Beep(1500, 150);
        Sleep(100);
        Beep(1500, 300); // Bip mais longo

        printf ("\n[ALERTA] O Voo %d ficou sem combustivel em pleno voo!\n", aux->aviao.numVoo); 
        printf ("Estamos realizando um pouso forçado e reabastecendo... um momento...\n"); 
        
        Sleep (2000); 
        struct Aviao aviaoAbastecido = aux->aviao; 
        aviaoAbastecido.combustivel = 100; 

        removeAviao(pista); 

        //Lauane: função insereAviao vai jogá-lo lá para o fim da fila de prioridade
        insereAviao(pista, aviaoAbastecido); 

        printf ("Aviao abastecido com sucesso! O nivel de combustivel esta em 100%%\n"); 
        return 1;
    }
    
    return 0; 
}

void exibePista (Fila* pista, int quant){

    noFila* numPista = pista->inicio; 
    
    if (pista == NULL) { 
        printf ("\nOps... Essa pista está inativa no momento...\n");
        return; 
    }

    if (pista->inicio == NULL) { 
        printf ("\nFila da Pista %d vazia. Nenhuma aeronave se aproximando...\n", quant);
        return;  
    }

    while (numPista != NULL) { 
        printf (" = = = = PISTA %d DE POUSO = = = = \n", quant); 
        printf ("[ Nome da Companhia: %s ]", numPista->aviao.nomeCompanhia); 
        printf (" | [ Numero do Voo: %d ]", numPista->aviao.numVoo); 
        printf (" | [ Nivel de Combustivel: %d%%]\n", numPista->aviao.combustivel); 
        printf (" | [ Classificacao de Emergencia: %d ]", numPista->aviao.emergencia); 
        printf (" | [ Possui carga perigosa?");  
            if (numPista->aviao.cargaPerigosa == 1) { 
                printf (" Sim]\n"); 
            } else if (numPista->aviao.cargaPerigosa == 2)
                printf (" Nao]\n");  
        printf (" = = = = = = = = = = = = = \n"); 

        numPista = numPista->prox;  
    }
}

void apagaFila (Fila* pista){

    if (pista == NULL) { 
        return;
    }

    noFila* aux; 

    while (pista->inicio != NULL) { 
        aux = pista->inicio; 
        pista->inicio = pista->inicio->prox; 
        free(aux); 
    }
    free(pista); 
}

int PistaParaDecolagem(Fila* pista, Fila* pistaDecolagem) {
    if (pista == NULL || pista->inicio == NULL || pistaDecolagem == NULL) {
        printf("\n[TORRE] Nao ha aeronaves na fila de decolagem no momento...\n");
        return 0;
    }

    noFila* noAtual = pista->inicio;
    struct Aviao aviaoAvaliado = noAtual->aviao;

    printf("\n==========================================\n");
    printf("     TORRE DE CONTROLE - LAUDO AUTOMATICO\n");
    printf("==========================================\n");
    printf(" Escaneando Voo: %d | Companhia: %s\n", aviaoAvaliado.numVoo, aviaoAvaliado.nomeCompanhia);
    printf(" -> Combustivel atual: %d%%\n", aviaoAvaliado.combustivel);
    printf(" -> Alerta de Emergencia: %d\n", aviaoAvaliado.emergencia);
    printf(" -> Carga Perigosa: %s\n", (aviaoAvaliado.cargaPerigosa == 1) ? "SIM" : "NAO");
    printf("------------------------------------------\n");
    printf(" VEREDITO DOS SISTEMAS: ");

    // aqui sim eh a checagem automatica dos critérios de segurança
    if (aviaoAvaliado.combustivel != 100 || aviaoAvaliado.emergencia != 4 || aviaoAvaliado.cargaPerigosa != 2) {
        printf("REPROVADO PARA DECOLAGEM]\n"); 
        printf("[-> RÁDIO DO AEROPORTO: 'Plano de voo rejeitado por quebra de protocolo de seguranca...");
        printf(" A aeronave deve estar com 100%% de tanque, sem alertas e sem carga perigosa!'\n");
        printf("==========================================\n");
        return 0; 
    }

    printf("[LIBERADO PARA DECOLAGEM]\n");
    printf("[-> RÁDIO DO AEROPORTO: 'ATENÇÃO, HÁ AVIÃO PRONTO PARA SAÍDA NA PISTA DE DECOLAGEM'] \n");
    printf("\nSenhores passageiros, se dirijam ao portao de embarque e boa viagem!!!! a IFSPLines agradece a preferencia!!! ->->->\n"); 
    printf("==========================================\n");

    removeAviao(pista);

    /*Lauane: mesmo processo de todos, alocar memoria em uma nova pista e add no final... */
    noFila* novoNo = (noFila*) malloc(sizeof(noFila));
    if (novoNo == NULL) {
        return 0;
    }
    novoNo->aviao = aviaoAvaliado;
    novoNo->prox = NULL;

    if (pistaDecolagem->inicio == NULL) {
        pistaDecolagem->inicio = novoNo;
        pistaDecolagem->fim = novoNo;
    } else {
        pistaDecolagem->fim->prox = novoNo;
        pistaDecolagem->fim = novoNo;
    }

    pistaDecolagem->qtd++;
    return 1;
}