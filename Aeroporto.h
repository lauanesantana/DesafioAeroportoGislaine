#ifndef AEROPORTO_H
#define AEROPORTO_H

struct Aviao {
    char nomeCompanhia[40];
    int numVoo;
    int combustivel;
    int emergencia;
    int cargaPerigosa;
};

typedef struct tipoFila Fila;

Fila* criaPista(); //sarah

int insereAviao(Fila* pista, struct Aviao aviao); //sarah

int removeAviao(Fila* pista);//murilo

int consultaPista(Fila* pista, struct Aviao *aviao);//sarah

int buscarAviao(Fila* pista, int numVoo, struct Aviao *aviao);//bruna

int atualizarPrioridade(Fila* pista, int numVoo);//murilo

int pistaLiberada(Fila* pista);//lauane

int aviaoSemCombustivel(Fila* pista);//lauane

void exibePista(Fila* pista, int quant);//bruna

void apagaFila(Fila* pista);//murilo

int PistaParaDecolagem(Fila* pista, Fila* pistaDecolagem);//lauane

#endif