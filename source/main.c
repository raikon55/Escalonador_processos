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

    pthread_t thread;
    pthread_create(&thread, NULL, (void *)aguardar_processo, (escalonador_t*) escalonador);
    pthread_join(thread, NULL);

    do {
        envia_prox_para_CPU(escalonador);
        printf("%li %i\n", escalonador->tempo_total, escalonador->fila->tamanho);
    } while (existe_processo(escalonador));
}

