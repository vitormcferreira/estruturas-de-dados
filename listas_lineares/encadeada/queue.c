/**
 * Nome: linked_list.c
 * Lista encadeada
 * @author Vítor M. C. Ferreira
 * @since 17/02/2021
*/
#include <stdio.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

typedef struct linked_list_node {
    void* value;
    struct linked_list_node* next;
} Tlinked_list_node;

typedef struct linked_list {
    int count;
    Tlinked_list_node* first;
    Tlinked_list_node* last;
} Tlinked_list;

Tlinked_list* create_linked_list();
void linked_list_push(Tlinked_list* linked_list, void* value);
void* linked_list_shift(Tlinked_list* linked_list);
void linked_list_walk(Tlinked_list* linked_list,
    void (*f)(void* value, int level));

Tlinked_list* create_linked_list() {
    Tlinked_list* linked_list = malloc(sizeof (Tlinked_list));
    linked_list->count = 0;
    linked_list->first = NULL;
    linked_list->last = NULL;
    return linked_list;
}

void linked_list_push(Tlinked_list* linked_list, void* value) {
    Tlinked_list_node* node = malloc(sizeof (Tlinked_list_node));
    node->value = value;
    node->next = NULL;

    if (linked_list->first == NULL) {
        linked_list->first = node;
        linked_list->last = linked_list->first;
    }

    linked_list->last->next = node;
    linked_list->last = node;
    linked_list->count++;
}

void* linked_list_shift(Tlinked_list* linked_list) {
    if (linked_list->first == NULL)
        return NULL;

    linked_list->count--;

    Tlinked_list_node* first = linked_list->first;
    void* value = first->value;

    linked_list->first = linked_list->first->next;
    free(first);
    if (linked_list->first == NULL) {
        linked_list->last = NULL;
    }
    return value;
}

void linked_list_walk(Tlinked_list* linked_list,
    void (*f)(void* value, int level)) {
    Tlinked_list_node* aux = linked_list->first;
    while (aux != NULL) {
        f(aux->value, 0);
        aux = aux->next;
    }
}

#endif
