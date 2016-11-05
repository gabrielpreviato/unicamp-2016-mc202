#include "lab10.h"

int main() {
    int size, lastHeap = 0;
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

        if (option == 'i') {

        }
        else if (option == 'm') {

        }
        else if (option == 'd') {

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

int searchHeap(int *kVector, int key) {
    if (kVector[key] == K_EMPTY) {
        return 0;
    }
    return 1;
}

int findParent(int position) {
    return position / 2;
}

int insertHeap(heap_t *heap, int *kVector, int size, int* lastHeap) {
    int key, value, positionHeap = *lastHeap;
    scanf("%d %d", &key, &value);

    // Check if the key already exists
    if (searchHeap(kVector, key)) {
        return 1;
    }

    // Add these data to the heap
    heap[positionHeap].key = key;
    heap[positionHeap].value = value;

    // In case we are adding the first heap element, ends the function
    if (lastHeap == 0) {
        lastHeap++;
        kVector[key] = positionHeap;
        return 0;
    }

    // Do a loop for checking if the value added is lesser than his parent
    int parentPosition = findParent(positionHeap);
    while (value < heap[parentPosition].value && positionHeap != 0) {
        // Updates the parent element
        heap[positionHeap] = heap[parentPosition];
        kVector[heap[parentPosition].key] = positionHeap;

        // Updates the new element
        positionHeap = parentPosition;
        heap[positionHeap].value = value;
        heap[positionHeap].key = key;
        parentPosition = findParent(positionHeap);
    }

    kVector[key] = positionHeap;
    // Update lastHeap and lastKey
    (*lastHeap)++;

    return 0;
}
