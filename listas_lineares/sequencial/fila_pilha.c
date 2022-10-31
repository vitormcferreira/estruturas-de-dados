/**
 * filapilha.c
 * Gerenciador de fila/pilha.
 * O inicio da fila fica na posicao 0 do vetor e
 * o inicio da pilha fica na posicao length - 1
 * do vetor.
 *
 *
 * Autor: Vítor M. C. Ferreira
 * Data: 08/03/2020
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* pos;
    int length;
    int fEnd;
    int pEnd;
    int count;
}TfP; // fP significa Fila/Pilha

TfP* constructorTfP(int length);
void displayF(TfP* fP);
int insertF(TfP* fP, int e);
int removeF(TfP* fP);
void displayP(TfP* fP);
int insertP(TfP* fP, int e);
int removeP(TfP* fP);
void freeTfP(TfP* fP);

TfP* constructorTfP(int length) {
    TfP* fP = (TfP*)malloc(sizeof(TfP));
    if (fP == NULL) {
        return NULL;
    }
    fP->pos = (TfP*)malloc(sizeof(int) * length);
    if (fP->pos == NULL) {
        return NULL;
    }
    fP->length = length;
    fP->fEnd = 0;
    fP->pEnd = length;
    fP->count = 0;
    return fP;
}

void displayF(TfP* fP) {
    int i;
    for (i = 0; i < fP->fEnd; i++) {
        printf("array[%d] = %d\n", i, fP->pos[i]);
    }
}

int insertF(TfP* fP, int e) {
    if (fP->count == fP->length) {
        return 1;
    }
    fP->pos[fP->fEnd] = e;
    fP->fEnd++;
    fP->count++;
    return 0;
}

int removeF(TfP* fP) {
    if (fP->fEnd == 0) {
        return 1;
    }
    int i;
    for (i = 1; i < fP->fEnd; i++) {
        fP->pos[i - 1] = fP->pos[i];
    }
    fP->fEnd--;
    fP->count--;
}

void displayP(TfP* fP) {
    int i;
    for (i = fP->pEnd; i < fP->length; i++) {
        printf("array[%d] = %d\n", i, fP->pos[i]);
    }
}

int insertP(TfP* fP, int e) {
    if (fP->count == fP->length) {
        return 1;
    }
    fP->pEnd--;
    fP->pos[fP->pEnd] = e;
    fP->count++;
    return 0;
}

int removeP(TfP* fP) {
    if (fP->pEnd == fP->length) {
        return 1;
    }
    fP->pEnd++;
    fP->count--;
    return 0;
}

void freeTfP(TfP* fP) {
    free(fP->pos);
    free(fP);
}