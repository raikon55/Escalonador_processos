#include <stdio.h>
#include <pthread.h>

#include "../includes/fila.h"
#include "../includes/escalonador.h"

void main(void) {
    escalonador_t* escalonador = (escalonador_t*) malloc(sizeof(escalonador_t));
    if (escalonador == NULL) {
        puts("Erro na alocação");
        exit(0);
    }
    inicializar_escalonador(escalonador, 5, 'R');

    processo_t controle;
    controle.tamanho = 0;

    aguarda_processo(escalonador);
    do {
        if (fila_vazia(escalonador->fila)) {
            carrega_estado_escalonador(escalonador);
        }
        recebe_processo(escalonador, controle);
        // calcula_quantum(escalonador);
        // exibir_fila(escalonador->fila);
        // puts("----------------------------------------------");
        envia_prox_para_CPU(escalonador);
        organiza_fila(escalonador);
        salva_estado_escalonador(escalonador);
    } while (existe_processo(escalonador));
}