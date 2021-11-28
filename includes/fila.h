#ifndef FILA_H_
#define FILA_H_

#include <stdlib.h>

#include "escalonador.h"
#include "estruturas.h"

fila_processos_t* inicializar_fila(fila_processos_t*);
int fila_vazia(fila_processos_t* fila);
void enfileirar(processo_t, fila_processos_t*);
processo_t desenfileirar(fila_processos_t* fila);
void deletar_fila(fila_processos_t*);

#endif