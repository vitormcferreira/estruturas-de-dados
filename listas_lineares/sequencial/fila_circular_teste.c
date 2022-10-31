#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fila_circular.c"
#include <math.h>

bool igual_a_20(Tcqueue* queue, void* e, int pos) {
    int num = *((int*)e);
    return num == 20;
}

void fun(Tcqueue* queue, void* e, int pos) {
    int num = *((int*)e);
    printf("%d 👌\n", num);
}

void libera(Tcqueue* queue, void* e, int pos) {
    int* num = (int*)e;
    free(num);
}

void main(void) {
    int* valor1 = malloc(sizeof(int));
    (*valor1) = 10;
    int* valor2 = malloc(sizeof(int));
    (*valor2) = 20;
    int* valor3 = malloc(sizeof(int));
    (*valor3) = 30;

    Tcqueue* q = create_cqueue(1, 2);

    enqueue_cqueue(q, valor1);
    enqueue_cqueue(q, valor2);
    enqueue_cqueue(q, valor3);

    int* aux;

    printf("get_element_cqueue\n");
    aux = (int*)get_element_cqueue(q, 0);
    printf("%d\n", *aux);

    printf("dequeue_cqueue\n");
    aux = (int*)dequeue_cqueue(q);
    printf("%d\n", *aux);

    printf("search_cqueue\n");
    aux = (int*)search_cqueue(q, igual_a_20);
    printf("%d\n", *aux);

    printf("foreach_cqueue\n");
    foreach_cqueue(q, fun);

    printf("to_str_control_cqueue\n");
    to_str_control_cqueue(q);

    free_cqueue(q, libera);
}