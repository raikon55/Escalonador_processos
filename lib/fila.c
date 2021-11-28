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

void deletar_fila(fila_processos_t* fila) {
    elemento_t* temp = fila->inicio;
    while(!fila_vazia(fila)) {
        desenfileirar(fila);
    }

    free(fila);
}
