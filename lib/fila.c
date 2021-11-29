#include "../includes/fila.h"

fila_processos_t* inicializar_fila(fila_processos_t* fila) {
    fila->inicio = (elemento_t*) malloc(sizeof(elemento_t));
    if (fila->inicio == NULL) {
        puts("Erro na alocação");
        exit(0);
    }

    fila->inicio->proximo = NULL;
    fila->fim = fila->inicio;
    fila->tamanho = 0;
}

int fila_vazia(fila_processos_t* fila) {
    return (fila->inicio == fila->fim);
}

void enfileirar(processo_t processo, fila_processos_t* fila) {
    fila->fim->proximo = (elemento_t*) malloc(sizeof(elemento_t));
    if (fila->fim->proximo == NULL) {
        puts("Erro na alocação");
        exit(0);
    }

    fila->fim = fila->fim->proximo;
    fila->fim->processo = processo;
    fila->fim->proximo = NULL;

    fila->tamanho++;
}

processo_t desenfileirar(fila_processos_t* fila) {
    if (fila_vazia(fila)) {
        return fila->inicio->processo;
    }

    elemento_t* temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    processo_t processo = temp->processo;
    free(temp);
    fila->tamanho--;

    return processo;
}

void exibir_fila(fila_processos_t* fila) {
    for(elemento_t* e = fila->inicio; e != NULL; e = e->proximo) {
        processo_t processo = e->processo;
        printf("PID: %li\nTamanho: %li\nQuantum: %li\nPrioridade: %i\nTempo chegada: %li\nTempo de processador: %li\n",
            processo.PID, processo.tamanho, processo.quantum, processo.prioridade,
            processo.tempo_chegada, processo.tempo_processador);
    }
}

void ordenar_fila(fila_processos_t* fila) {
    int i = 0;
    int tamanho = fila->tamanho;
    processo_t* processos = (processo_t*) calloc(fila->tamanho, sizeof(processo_t));

    while (!fila_vazia(fila)) {
        processos[i] = desenfileirar(fila);
        i++;
    }

    for (int j = 0; j < i; j++) {
        for (int k = 0; k < i; k++) {
            if (processos[k].prioridade < processos[j].prioridade) {
                processo_t aux = processos[j];
                processos[j] = processos[k];
                processos[k] = aux;
            }
        }
    }

    int prioridade = 0;
    while (prioridade < 4) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                if (prioridade == processos[j].prioridade && processos[j].prioridade == processos[k].prioridade) {
                    if (processos[k].tamanho < processos[j].tamanho) {
                        processo_t aux = processos[j];
                        processos[j] = processos[k];
                        processos[k] = aux;
                    }
                }
            }
        }   
        prioridade++;
    }

    i = 0;
    while (i < tamanho) {
        enfileirar(processos[i], fila);
        i++;
    }
}

void deletar_fila(fila_processos_t* fila) {
    elemento_t* temp = fila->inicio;
    while(!fila_vazia(fila)) {
        desenfileirar(fila);
    }
    free(fila);
}
