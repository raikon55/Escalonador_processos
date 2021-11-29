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

void aguarda_processo(escalonador_t* escalonador) {
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
    if (processo.tamanho == 0) {
        float probabilidade = 0.1;
        float prob = ( ((float)(rand()%10))+1.0)/10.0;
        if (prob <= probabilidade) {
            processo_t novo_proc = novo_processo(escalonador, rand() % 51, rand() % 4); 
            escalonador->tempo_total += novo_proc.tamanho;
            escalonador->ultimo_tempo_chegada = escalonador->tempo_atual;
            enfileirar(novo_proc, escalonador->fila);
        }
    } else {
        escalonador->tempo_total += processo.tamanho;
        escalonador->ultimo_tempo_chegada = escalonador->tempo_atual;
        enfileirar(processo, escalonador->fila);
    }
}

void processa(escalonador_t* escalonador) {
    int resto_tempo;
    processo_t processo;

    switch (escalonador->politica) { // RR
    case 'R':
        if ( !fila_vazia(escalonador->fila) ) {
            processo = desenfileirar(escalonador->fila);
            if (processo.tamanho == 0) {
                return;
            }
            resto_tempo = ( (processo.tamanho - processo.tempo_processador) < escalonador->quantum ) ?
                            (processo.tamanho - processo.tempo_processador) :
                            escalonador->quantum;
            processo.tempo_processador += resto_tempo;
            escalonador->tempo_atual += resto_tempo;
            if (processo.tempo_processador < processo.tamanho) {
                enfileirar(processo, escalonador->fila);
            }
        }
        break;

    case 'F':
        processo = desenfileirar(escalonador->fila);
        if (processo.tamanho == 0) {
            return;
        }
        escalonador->tempo_atual += processo.tamanho;
        break;

    case 'P':
        processo = desenfileirar(escalonador->fila);
        break;

    default:
        return;
    }
}

void envia_prox_para_CPU(escalonador_t* escalonador) {
    if (escalonador->tempo_total >= escalonador->tempo_atual) {
        processa(escalonador);
    }
}

int existe_processo(escalonador_t* escalonador) {
    return escalonador->existe_processo;
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

void salva_estado_escalonador(escalonador_t* escalonador) {
    FILE* arquivo = fopen("./data/memoria.csv", "w");
    if (arquivo == NULL) {
        puts("Erro ao abrir o arquivo");
        exit(0);
    }

    escalonador->existe_processo = (escalonador->fila->tamanho != 0);
    fprintf(arquivo, "%c;%i;%li;%li;%li\n",
        escalonador->politica, escalonador->quantum, escalonador->tempo_atual, escalonador->tempo_total, escalonador->ultimo_tempo_chegada);

    while (!fila_vazia(escalonador->fila)) {
        processo_t processo = desenfileirar(escalonador->fila);
            fprintf(arquivo, "%i;%li;%i;%i;%li;%li;%li\n",
        processo.PID, processo.tamanho, processo.quantum, processo.prioridade, processo.tempo_chegada, processo.tempo_processador, processo.tempo_total_processador);
    }
    fclose(arquivo);
}

void carrega_estado_escalonador(escalonador_t* escalonador) {
    processo_t processo;
    FILE* arquivo = fopen("./data/memoria.csv", "r");
    if (arquivo == NULL) {
        puts("Erro ao abrir o arquivo");
        return;
    }

    fscanf(arquivo, "%c;%i;%li;%li;%li[^\n]\n",
        &escalonador->politica, &escalonador->quantum, &escalonador->tempo_atual, &escalonador->tempo_total, &escalonador->ultimo_tempo_chegada);

    while (fscanf(arquivo, "%i;%li;%i;%i;%li;%li;%li[^\n]\n",
        &processo.PID, &processo.tamanho, &processo.quantum, &processo.prioridade, &processo.tempo_chegada, &processo.tempo_processador, &processo.tempo_total_processador) == 7) {
        enfileirar(processo, escalonador->fila);
    }
    fclose(arquivo);
}