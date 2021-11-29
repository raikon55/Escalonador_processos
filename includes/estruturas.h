#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

typedef struct elemento elemento_t;
typedef struct processo processo_t;
typedef struct escalonador escalonador_t;
typedef struct fila_processos fila_processos_t;

struct processo {
    unsigned int PID;
    unsigned long tamanho;
    unsigned short quantum;
    unsigned short prioridade;
    unsigned long tempo_chegada;
    unsigned long tempo_processador;
    unsigned long tempo_total_processador;
};

struct escalonador {
    char politica; // R: Round-Robin, F: FIFO, P: Prioridade
    unsigned short quantum;

    short existe_processo;
    fila_processos_t* fila;
    
    unsigned long tempo_atual;
    unsigned long tempo_total;
    unsigned long ultimo_tempo_chegada;
};

struct elemento {
    processo_t processo;
    elemento_t* proximo;
};

struct fila_processos {
    elemento_t* inicio;
    elemento_t* fim;
    unsigned int tamanho;
};

#endif