#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5

bool is_empty(int length) {
    return length == 0;
}

bool is_full(int length) {
    return MAX_SIZE == length;
}

bool push(int stack[], int* length, int item) {
    if (is_full(*length)) {
        return false;
    }
    
    stack[*length] = item;
    (*length)++;
}

bool pop(int* length) {
    if (is_empty(*length)) {
        return false;
    }

    (*length)--;
}


void main(void) {
    int stack[MAX_SIZE] = {};
    int length = 0;

    push(stack, &length, 1);
    push(stack, &length, 2);
    pop(&length);

    if (!is_empty(length)) {
        printf("%d\n", stack[length - 1]);
    }
    printf("length=%d\n", length);
}