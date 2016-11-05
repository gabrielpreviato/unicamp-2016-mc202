#include <stdio.h>
#include <stdlib.h>

// Defines
#define K_EMPTY -1

// Structures
typedef struct {
    int key, value;
} heap_t;

// Functions prototypes
int createHeap(heap_t **heap, int size);
int createKeyVector(int **kVector, int size);
int searchHeap(int *kVector, int key);
int findParent(int position);
int insertHeap(heap_t *heap, int *kVector, int* lastHeap);
int findChild1(int position);
int findChild2(int position);
int removeMin(heap_t *heap, int *kVector, int size);
