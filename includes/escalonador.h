#ifndef ESCALONADOR_H_
#define ESCALONADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "fila.h"
#include "estruturas.h"

void recebe_processo(escalonador_t*, processo_t);
void aguardar_processo(escalonador_t* escalonador);
void calcula_processo(escalonador_t*);
void preempcao(int);
void envia_prox_para_CPU(escalonador_t*);
int existe_processo(escalonador_t*);
void organiza_filas(void);

void inicializar_escalonador(escalonador_t*, short, char);
processo_t novo_processo(escalonador_t*, long, short);

#endif