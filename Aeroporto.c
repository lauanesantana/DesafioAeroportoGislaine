#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Aeroporto.h"

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

Fila* criaPista() {

    Fila* pista = (Fila*) malloc(sizeof(Fila));

    if(pista == NULL)
        return NULL;

    pista->inicio = NULL;
    pista->fim = NULL;
    pista->qtd = 0;

    return pista;
}

int insereAviao(Fila* pista, struct Aviao aviao) {

    if(pista == NULL)
        return 0;

    noFila* novoAviao = (noFila*) malloc(sizeof(noFila));

    if(novoAviao == NULL)
        return 0;
    
      /*Lauane: add essa conferencia para tornar mais ''real'' e tornar nossas emergencias mais no sentido medico/mecanico e carga perigosa */
    if (aviao.combustivel == 0) {
        printf("\n[ALERTA INTERCEPTADO] Voo %d tentou entrar na fila com 0%% de combustivel!\n", aviao.numVoo);
        printf("Direcionando imediatamente para reabastecimento... um momento...\n");
        Sleep(2000); 
        
        aviao.combustivel = 100; 
        printf("Aviao abastecido com sucesso antes de entrar na fila de espera\n");
    }

    novoAviao->aviao = aviao;
    novoAviao->prox = NULL;

    if(pista->inicio == NULL) {

        pista->inicio = novoAviao;
        pista->fim = novoAviao;
        pista->qtd++;

        return 1;
    }

    noFila *ant = NULL;
    noFila *atual = pista->inicio;

    while(atual != NULL &&
          atual->aviao.emergencia < aviao.emergencia) {

        ant = atual;
        atual = atual->prox;
    }

    if(ant == NULL) {

        novoAviao->prox = pista->inicio;
        pista->inicio = novoAviao;

    } else {

        novoAviao->prox = atual;
        ant->prox = novoAviao;
    }

    if(atual == NULL)
        pista->fim = novoAviao;

    pista->qtd++;

    return 1;
}

int removeAviao(Fila* pista) {

    if(pista == NULL || pista->inicio == NULL)
        return 0;

    noFila *auxiliar = pista->inicio;

    pista->inicio = pista->inicio->prox;

    if(pista->inicio == NULL)
        pista->fim = NULL;

    free(auxiliar);

    pista->qtd--;

    return 1;
}

int consultaPista(Fila* pista, struct Aviao *aviao) {

    if(pista == NULL || pista->inicio == NULL)
        return 0;

    *aviao = pista->inicio->aviao;

    return 1;
}

int buscarAviao(Fila* pista, int numVoo, struct Aviao *aviao) {

    if(pista == NULL || pista->inicio == NULL)
        return 0;

    noFila *auxiliar = pista->inicio;

    while(auxiliar != NULL &&
          auxiliar->aviao.numVoo != numVoo) {

        auxiliar = auxiliar->prox;
    }

    if(auxiliar == NULL)
        return 0;

    *aviao = auxiliar->aviao;

    return 1;
}

int atualizarPrioridade(Fila* pista, int numVoo) {

    if(pista == NULL || pista->inicio == NULL)
        return 0;

    noFila *aux = pista->inicio;

    while(aux != NULL &&
          aux->aviao.numVoo != numVoo) {

        aux = aux->prox;
    }

    if(aux == NULL)
        return 0;

    printf("\nNovo nivel de prioridade:\n");
    printf("[0] Sem Emergencia\n");
    printf("[1] Emergencia Medica\n");
    printf("[2] Emergencia Militar\n");
    printf("[3] Emergencia Mecanica\n");

    scanf("%d", &aux->aviao.emergencia);

    return 1;
}

int pistaLiberada(Fila* pista) {

    if(pista == NULL || pista->inicio != NULL) {

        printf("\nNao ha pistas liberadas no momento.\n");

    } else {

        printf("\nPista disponivel para pouso.\n");
    }

    return 1;
}

int aviaoSemCombustivel(Fila* pista) {

    if(pista == NULL || pista->inicio == NULL)
        return 0;

    noFila *aux = pista->inicio;

    if(aux->aviao.combustivel == 0) {

        /* Lauane: aqui pesquisei e descobri que tem como fazer o pc emitir sons de bip, como se fossem aqueles barulhinhos de radio, mas nao consegui testar para ver se funciona*/
        Beep(1500, 150); // Frequência aguda, duração curta
        Sleep(100);
        Beep(1500, 150);
        Sleep(100);
        Beep(1500, 300); // Bip mais longo

        printf ("\n[ALERTA] O Voo %d ficou sem combustivel em pleno voo!\n", aux->aviao.numVoo); 
        printf ("Estamos realizando um pouso forçado e reabastecendo... um momento...\n"); 

        Beep(1500, 300);

        aux->aviao.combustivel = 100;

        printf("Aviao reabastecido com sucesso!\n");

        return 1;
    }

    return 0;
}

void exibePista(Fila* pista, int quant) {

    if(pista == NULL || pista->inicio == NULL) {

        printf("\nPista %d vazia.\n", quant);
        return;
    }

    noFila *aux = pista->inicio;

    printf("\n======= PISTA %d =======\n", quant);

    while(aux != NULL) {

        printf("\nCompanhia: %s\n", aux->aviao.nomeCompanhia);
        printf("Voo: %d\n", aux->aviao.numVoo);
        printf("Combustivel: %d%%\n", aux->aviao.combustivel);
        printf("Emergencia: %d\n", aux->aviao.emergencia);
        printf("Carga perigosa: %s\n",
               aux->aviao.cargaPerigosa == 1 ? "SIM" : "NAO");

        aux = aux->prox;
    }
}

void apagaFila(Fila* pista) {

    if(pista == NULL)
        return;

    noFila *aux;

    while(pista->inicio != NULL) {
||
        aux = pista->inicio;
        pista->inicio = pista->inicio->prox;

        free(aux);
    }

    free(pista);
}

int PistaParaDecolagem(Fila* pista, Fila* pistaDecolagem) {

    if(pista == NULL ||
       pista->inicio == NULL ||
       pistaDecolagem == NULL) {

        return 0;
    }

    struct Aviao aviao = pista->inicio->aviao;

    if(aviao.combustivel != 100 ||
       aviao.emergencia != 0 ||
       aviao.cargaPerigosa != 2) {

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

    insereAviao(pistaDecolagem, aviao);

    printf("\nAviao liberado para decolagem!\n");

    return 1;
}