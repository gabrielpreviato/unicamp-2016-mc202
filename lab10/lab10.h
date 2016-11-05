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
