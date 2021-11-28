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

    do {
        aguardar_processo(escalonador);
        exibir_fila(escalonador->fila);
        // recebe_processo();
        // calcula_quantum();
        envia_prox_para_CPU(escalonador);
    } while (existe_processo(escalonador));
}