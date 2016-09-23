#ifndef DYNAMIC_VECTOR_H

#include <stdlib.h>

#define DYNAMIC_VECTOR_H

int expandVector(char ***vector, int *queue_beg, int *queue_end, size_t *size);

int readToBuffer(char *buffer);

int push(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size, char buffer[]);

int unshift(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size, char buffer[]);

int printFirst(char ***vector, int *queue_beg, size_t *actual_size);

int printLast(char ***vector, int *queue_end, size_t *actual_size);

int isEmpty(size_t *actual_size);

int decreaseVector(char ***vector, int *queue_beg, int *queue_end, size_t *size);

int pop(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size);

int shift(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size);

int freeVector(char ***vector, int *queue_beg, size_t *actual_size);

#endif
