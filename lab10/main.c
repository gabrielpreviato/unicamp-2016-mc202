#include "lab10.h"

int main() {
    int size;
    scanf("%d", &size);

    int *kVector;
    heap_t *heap;



    if (createHeap(&heap, size) == 1) {
        return 1;
    }
    if (createKeyVector(&kVector, size) == 1) {
        return 1;
    }

    char option;
    do {
        scanf(" %c", &option);

        if (option = 'i') {

        }
        else if (option = 'm') {

        }
        else if (option = 'd') {

        }
        
    } while (option != 't');

    return 0;
}

int createHeap(heap_t **heap, int size) {
    *heap = malloc(sizeof(heap_t)*size);

    if (!*heap) {
        printf("Allocation error in createHeap()\n");
        return 1;
    }
    return 0;
}

int createKeyVector(int **kVector, int size) {
    *kVector = malloc(sizeof(heap_t)*size);

    if (!*kVector) {
        printf("Allocation error in createKeyVector()\n");
        return 1;
    }
    return 0;
}
