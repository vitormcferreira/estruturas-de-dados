#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int key;
    struct no* next;
} Tno;

typedef struct list {
    Tno* first;
} Tlist;

Tno* new_node(int key) {
    Tno* new = malloc(sizeof(Tno));
    new->key = key;
    new->next = NULL;
    return new;
}

void pop(Tlist* list) {
    if (list->first == NULL) return;

    if (list->first->next == NULL) {
        free(list->first);
        list->first = NULL;
        return;
    }

    Tno* before_last = list->first;

    while (before_last->next->next != NULL) {
        before_last = before_last->next;
    }

    free(before_last->next);
    before_last->next = NULL;
}

void push(Tlist* list, int key) {
    Tno* new = new_node(key);
    if (list->first == NULL) {
        list->first = new;
        return;
    }

    Tno* last = list->first;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new;
}

void shift(Tlist* list) {
    if (list->first == NULL) return;

    Tno* new_first = list->first->next;

    free(list->first);
    list->first = new_first;
}

void unshift(Tlist* list, int key) {
    Tno* new = new_node(key);

    new->next = list->first;
    list->first = new;
}

void delete(Tlist* list, int key) {
    if (list->first == NULL) return;

    if (list->first->next == NULL) {
        if (list->first->key == key) {
            free(list->first);
            list->first = NULL;
        }
        return;
    }

    Tno* before_target = NULL;
    Tno* target = list->first;

    while (target->key != key || target->next != NULL) {
        before_target = target;
        target = target->next;
    }
    if (target->key == key) {
        Tno* after_target = target->next;
        free(target);
        before_target->next = after_target;
    }
}

void display(Tlist* list) {
    Tno* next = list->first;

    while (next != NULL) {
        printf("%d ", next->key);
        next = next->next;
    }
    printf("\n");
}

void main(void) {
    Tlist* l = malloc(sizeof(Tlist));

    push(l, 10);
    push(l, 20);
    unshift(l, 30);
    pop(l);
    shift(l);
    delete(l, 10);
    display(l);
}
