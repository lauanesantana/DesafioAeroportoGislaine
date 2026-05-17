struct Aviao { 
    char nomeCompanhia [40]; 
    int numVoo; 
    int combustivel; 
    int emergencia;
    int cargaPerigosa; 
};

typedef struct tipoFila Fila; 

Fila* criaPista (); 

int insereAviao (Fila* pista, struct Aviao aviao);

int removeAviao (Fila* pista); 

int consultaPista (Fila* pista, struct Aviao *aviao); 

int buscarAviao (Fila* pista, int numVoo, struct Aviao *aviao); 

int atualizarPrioridade (Fila* pista, int numVoo); 

int pistaLiberada (Fila* pista);

int aviaoSemCombustivel (Fila* pista);

void exibePista (Fila* pista, int quant); 

void apagaFila (Fila* pista); 

int PistaParaDecolagem(Fila* pista, Fila* pistaDecolagem); 