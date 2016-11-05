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
            insertHeap(heap, kVector, & lastHeap);
        }
        else if (option == 'm') {
            removeMin(heap, kVector, size);
        }
        else if (option == 'd') {

        }

    } while (option != 't');

    free(heap);
    free(kVector);

    return 0;
}

int createHeap(heap_t **heap, int size) {
    *heap = malloc(sizeof(heap_t)*size);

    if (!*heap) {
        printf("Allocation error in createHeap()\n");
        return 1;
    }

    int i;
    for (i = 0; i < size; i++) {
        (*heap)[i].key = K_EMPTY;
    }
    return 0;
}

int createKeyVector(int **kVector, int size) {
    *kVector = malloc(sizeof(heap_t)*size);

    if (!*kVector) {
        printf("Allocation error in createKeyVector()\n");
        return 1;
    }

    int i;
    for (i = 0; i < size; i++) {
        (*kVector)[i] = K_EMPTY;
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

int insertHeap(heap_t *heap, int *kVector, int* lastHeap) {
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
    if (*lastHeap == 0) {
        (*lastHeap)++;
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

int findChild1(int position) {
    return 2 * position + 1;
}

int findChild2(int position) {
    return 2 * position + 2;
}

int removeMin(heap_t *heap, int *kVector, int size) {
    if (heap[0].key == K_EMPTY) {
        printf("vazio\n");
        return 1;
    }
    int child1Position = 1, child2Position = 2, positionHeap = 0,
        key = heap[0].key, value = heap[0].value;

    // Loop for putting the root (min value) to a leaf, making the correct changes
    //while (heap[child1Position].value != K_EMPTY || heap[child2Position].value != K_EMPTY)
    while (1) {
        // In case the min has 2 childs
        if (heap[child1Position].key != K_EMPTY && heap[child2Position].key != K_EMPTY) {
            // In case left child value smaller than right child value
            if (heap[child1Position].value < heap[child2Position].value) {
                // Updates new min value
                heap[positionHeap] = heap[child1Position];
                kVector[heap[positionHeap].key] = positionHeap;

                // Updates old new value
                positionHeap = child1Position;
                // In case the left child is out of vector, we reached a leaf
                if (findChild1(positionHeap) >= size) {
                    break;
                }
                child1Position = findChild1(positionHeap);
                child2Position = findChild2(positionHeap);
            }
            // In case right child value smaller than left child value
            else {
                // Updates new min value
                heap[positionHeap] = heap[child2Position];
                kVector[heap[positionHeap].key] = positionHeap;

                // Updates old new value
                positionHeap = child2Position;
                // In case the left child is out of vector, we reached a leaf
                if (findChild1(positionHeap) >= size) {
                    break;
                }
                child1Position = findChild1(positionHeap);
                child2Position = findChild2(positionHeap);
            }
        }
        // In case the min has only left child
        else if (heap[child1Position].key != K_EMPTY) {
            // Updates new min value
            heap[positionHeap] = heap[child1Position];
            kVector[heap[positionHeap].key] = positionHeap;

            // Updates old new value
            positionHeap = child1Position;
            // In case the left child is out of vector, we reached a leaf
            if (findChild1(positionHeap) >= size) {
                break;
            }
            child1Position = findChild1(positionHeap);
            child2Position = findChild2(positionHeap);
        }
        // TODO: Test if above else is really necessary
        // In case the min has only right child
        else {
            // Updates new min value
            heap[positionHeap] = heap[child2Position];
            kVector[heap[positionHeap].key] = positionHeap;

            // Updates old new value
            positionHeap = child2Position;
            // In case the left child is out of vector, we reached a leaf
            if (findChild1(positionHeap) >= size) {
                break;
            }
            child1Position = findChild1(positionHeap);
            child2Position = findChild2(positionHeap);
        }
    }

    printf("minimo {%d,%d}\n", key, value);

    // Erase kValue of min
    kVector[key] = K_EMPTY;

    // Shift to the left all heap elements after the removed elements
    int i;
    for (i = positionHeap; heap[i].key != -1; i++) {
        heap[positionHeap] = heap[positionHeap + 1];
    }

    return 0;
}

int decreaseHeap(heap_t *heap, int *kVector) {
    
}
