#include "../includes/escalonador.h"

void inicializar_escalonador(escalonador_t* escalonador, short quantum, char politica) {
    escalonador->quantum = quantum;
    escalonador->politica = politica;
    escalonador->tempo_atual = 0;
    escalonador->tempo_total = 0;
    escalonador->ultimo_tempo_chegada = 0;
    escalonador->fila = (fila_processos_t*) malloc(sizeof(fila_processos_t));
    if (escalonador->fila == NULL) {
        puts("Erro na alocação");
        exit(0);
    }

    inicializar_fila(escalonador->fila);
}

void aguardar_processo(escalonador_t* escalonador) {
    long tamanho;
    int prioridade;
    char buffer[32] = {};
    FILE* arquivo = fopen("./data/input.csv", "r");

    if (arquivo == NULL) {
        puts("Erro ao abrir o arquivo");
        exit(0);
    }

    fgets(buffer, 31, arquivo); // Ignorar cabeçalho

    while ( fscanf(arquivo, "%i;%li[^\n]\n", &prioridade, &tamanho) == 2 ) {
        processo_t processo = novo_processo(escalonador, tamanho, prioridade);
        recebe_processo(escalonador, processo);
    }
    fclose(arquivo);
}

void recebe_processo(escalonador_t* escalonador, processo_t processo) {
    escalonador->tempo_total += processo.tamanho;
    escalonador->ultimo_tempo_chegada = escalonador->tempo_atual;
    enfileirar(processo, escalonador->fila);
}

void calcula_processo(escalonador_t* escalonador) {
    if (escalonador->politica == 'R') { // RR
        if ( !fila_vazia(escalonador->fila) ) {
            processo_t processo = desenfileirar(escalonador->fila);
            if (processo.tamanho == 0) {
                enfileirar(processo, escalonador->fila);
                return;
            }
            int resto_tempo = ( (processo.tamanho - processo.tempo_processador) < escalonador->quantum ) ?
                            (processo.tamanho - processo.tempo_processador) :
                            escalonador->quantum;
            processo.tempo_processador += resto_tempo;
            escalonador->tempo_atual += resto_tempo;
            if (processo.tempo_processador < processo.tamanho) {
                enfileirar(processo, escalonador->fila);
            }
        }
    } else if (escalonador->politica == 'F') { // FIFO
        processo_t processo = desenfileirar(escalonador->fila);
        if (processo.tamanho == 0) {
            return;
        }
        escalonador->tempo_atual += processo.tamanho;
    }
}

void envia_prox_para_CPU(escalonador_t* escalonador) {
    if (escalonador->tempo_total >= escalonador->tempo_atual) calcula_processo(escalonador);
}

int existe_processo(escalonador_t* escalonador) {
    if (escalonador->politica == 'R') {
        return (escalonador->tempo_total != escalonador->tempo_atual);
    } else if (escalonador->politica == 'F') {
        return 0;
    }
}

processo_t novo_processo(escalonador_t* escalonador, long tamanho, short prioridade) {
    processo_t processo;
    processo.PID = rand() % 1000;
    processo.tamanho = tamanho;
    processo.tempo_processador = 0;
    processo.prioridade = prioridade;
    processo.tempo_chegada = escalonador->ultimo_tempo_chegada;

    return processo;
}