#ifndef FILA_H_
#define FILA_H_

#include <stdlib.h>

#include "escalonador.h"
#include "estruturas.h"

/*
 * Inicia a fila, alocando memória e apontando o inicio e fim para a mesma
 * região da memória
 */
fila_processos_t* inicializar_fila(fila_processos_t*);

/*
 * Verifica se há processos não executados na fila
 */
int fila_vazia(fila_processos_t* fila);

/*
 * Adiciona processo na fila, verificando a prioridade e tamanho do mesmo
 */
void enfileirar(processo_t, fila_processos_t*);

/*
 * Remove o primeiro processo da fila
 */
processo_t desenfileirar(fila_processos_t* fila);

/*
 * Exibe todos os elementos da fila
 */
void exibir_fila(fila_processos_t* elemento);

/*
 * Deleta todos os processos da fila, e em seguida a propria fila
 */
void deletar_fila(fila_processos_t*);

#endif