/**
 * fila_circular.h
 * Biblioteca com operações sobre uma fila circular dinâmica.
 *
 * Autor: Vítor M. C. Ferreira
 *
 * Data: 18/03/2021
 * Modificações da última versão:
 *
 * A fila cresce quando fica cheia.
 *
 * Adicionado queue como parametro da função foreach.
 *
 * Versão: 3.0
 */
#ifndef _FILACIRC2_H
#define _FILACIRC2_H

#include <stdio.h> // printf em to_str_control_cqueue
#include <stdlib.h> // malloc, free
#include <stdbool.h> // em enqueue_cqueue
#include <math.h> // ceil em _expand_cqueue

 /* Estrutura para a fila circular.
 DEVE SER INICIADA PELA FUNÇÃO create_cqueue */
typedef struct cqueue {
    // tamanho da fila
    int length;
    // inicio da fila
    int start;
    // fim da fila
    int end;
    // quantidade de elementos na fila
    int count;
    // fator de crescimento
    float mult;
    // fila
    void** pos;
}Tcqueue;

/* Retorna a fila com o tamanho especificado ou
NULL caso não tenha conseguido alocar memória. */
Tcqueue* create_cqueue(int length, float mult);

/* EXTRA: Envia iterativamente as posicoes e seus
respectivos valores até o fim da fila a partir
de repetidas chamadas à funcao. */
void foreach_cqueue(Tcqueue* queue,
    void (*func)(Tcqueue* queue, void* e, int pos));

/* EXTRA: Retorna o elemento na posição especificada.
Caso a posição não seja válida, retorna NULL. */
void* get_element_cqueue(Tcqueue* queue, int pos);

/* Insere o elemento na fila. Retorna 1 caso a
fila esteja cheia ou 0 caso não. */
int enqueue_cqueue(Tcqueue* queue, void* e);

/* Remove um elemento da fila. Retorna NULL caso
a fila esteja vazia ou o elemento caso não. */
void* dequeue_cqueue(Tcqueue* queue);

/* Expande a fila usando como novo length
queue->length * queue->mult. */
void _expand_cqueue(Tcqueue* queue);

/* Busca um elemento na fila usando a função passada
 como criterio. */
void* search_cqueue(Tcqueue* queue,
    bool (*search)(Tcqueue* queue, void* e, int pos));

/* Libera a memória alocada pelo construtor. */
void free_cqueue(Tcqueue* queue,
    void libera(Tcqueue* queue, void* e, int pos));

/* Recebe a fila e exibe as variáveis da struct.
Serve para observar como as coisas estão. */
void to_str_control_cqueue(Tcqueue* queue);


Tcqueue* create_cqueue(int length, float mult) {
    Tcqueue* queue = (Tcqueue*)malloc(sizeof (Tcqueue));

    if (queue == NULL) {
        return NULL; // se nao conseguir alocar retorna NULL
    }
    queue->pos = malloc(sizeof (void*) * length);
    if (queue->pos == NULL) {
        free(queue);
        // se nao conseguir alocar libera a fila alocada e retorna NULL
        return NULL;
    }
    queue->length = length;
    queue->start = 0;
    queue->end = 0;
    queue->count = 0;
    queue->mult = mult;

    return queue;
}


void foreach_cqueue(Tcqueue* queue,
    void (*func)(Tcqueue* queue, void* e, int pos)) {
    /* Fiz assim para que a iteração seja mais facil. Deste jeito
    quem for iterar nao precisa saber de detalhes de implementacao. */
    int i;
    for (i = 0; i < queue->count; i++) {
        func(queue, get_element_cqueue(queue, i), i);
    }
}


void* get_element_cqueue(Tcqueue* queue, int pos) {
    if (pos < 0 || pos >= queue->count) {
        return NULL;
    }
    return queue->pos[(pos + queue->start) % queue->length];
}


int enqueue_cqueue(Tcqueue* queue, void* e) {
    // verifica se é preciso (fila cheia) e se é possível (mult > 0) expandir
    if (queue->count == queue->length && queue->mult > 0) {
        _expand_cqueue(queue);
    }
    else {
        // verifica se existe espaço
        if (queue->count == queue->length) {
            return false;
        }
    }
    queue->pos[queue->end] = e;

    queue->count++;
    queue->end++;
    queue->end = queue->end % queue->length;
    return true;
}


void* dequeue_cqueue(Tcqueue* queue) {
    if (queue->count == 0) {
        return NULL;
    }
    void* elemento = queue->pos[queue->start];

    // diminui um elemento do contador de elementos
    queue->count--;

    // aumenta o início
    queue->start++;
    // faz com que o início sempre seja menor que length (tamanho do vetor)
    queue->start = queue->start % queue->length;
    return elemento;
}


void _expand_cqueue(Tcqueue* queue) {
    int new_lengh = ceil(queue->length * queue->mult);
    void** new_pos = malloc(sizeof(void*) * new_lengh);

    int i;
    for (i = 0; i < queue->count; i++) {
        new_pos[i] = get_element_cqueue(queue, i);
    }
    free(queue->pos);
    queue->pos = new_pos;
    queue->length = new_lengh;
    queue->start = 0;
    queue->end = queue->count;
}


void* search_cqueue(Tcqueue* queue,
    bool (*search)(Tcqueue* queue, void* e, int pos)) {
    int i;
    for (i = 0; i < queue->count; i++) {
        void* el = get_element_cqueue(queue, i);
        if (search(queue, el, i)) {
            return el;
        }
    }
    return NULL;
}


void free_cqueue(Tcqueue* queue,
    void (*libera)(Tcqueue* queue, void* e, int pos)) {
    foreach_cqueue(queue, libera);
    free(queue);
}


void to_str_control_cqueue(Tcqueue* queue) {
    printf("length=%d, start=%d, end=%d, count=%d, mult=%f\n",
        queue->length, queue->start, queue->end, queue->count, queue->mult);
}

#endif
