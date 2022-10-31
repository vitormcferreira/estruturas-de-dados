#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5

bool is_empty(int length) {
    return length == 0;
}

bool is_full(int length) {
    return MAX_SIZE == length;
}

void _move_forward(int queue[], int length) {
    for (int i = length; i > 0; i--) {
        queue[i] = queue[i - 1];
    }
}

bool enqueue(int queue[], int* length, int item) {
    if (is_full(*length)) {
        return false;
    }

    _move_forward(queue, *length);
    queue[0] = item;
    (*length)++;
    return true;
}

bool dequeue(int* length) {
    if (is_empty(*length)) {
        return false;
    }

    (*length)--;
}

void main(void) {
    int queue[MAX_SIZE] = {};
    int length = 0;

    enqueue(queue, &length, 1);
    enqueue(queue, &length, 2);
    dequeue(&length);

    if (!is_empty(length)) {
        printf("%d\n", queue[length - 1]);
    }
    printf("length=%d\n", length);
}