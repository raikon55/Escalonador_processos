#ifndef ESCALONADOR_H_
#define ESCALONADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "fila.h"
#include "estruturas.h"

void aguarda_processo(escalonador_t* escalonador);
void recebe_processo(escalonador_t*, processo_t);
void processa(escalonador_t*);
void organiza_fila(escalonador_t*);
void carrega_estado_escalonador(escalonador_t* escalonador);
void salva_estado_escalonador(escalonador_t* escalonador);
void envia_prox_para_CPU(escalonador_t*);
int existe_processo(escalonador_t*);
void organiza_filas(void);

void inicializar_escalonador(escalonador_t*, short, char);
processo_t novo_processo(escalonador_t*, long, short);

#endif