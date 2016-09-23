#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_vector.h"


#define TRUE 1
#define BUFFER_SIZE 1001

int main() {

    // Declare variables
    int queue_beg = 0, queue_end = 0;
    char **vector = NULL, opcao[12], buffer[BUFFER_SIZE];
    size_t size = sizeof(char) * 2, actual_size = 0;

    // Dinamically allocate the vector
    vector = (char **) malloc(sizeof(char *) * size);

    // Stay in a loop unless the input says to exit the program
    while (TRUE) {
        // Gets operation
        scanf(" %s", opcao);

        if (strcmp(opcao, "unshift") == 0) {
            if (unshift(&vector, &queue_beg, &queue_end, &size, &actual_size, buffer)) {
                printf("Error in unshift!\n");
            }
        }
        else if (strcmp(opcao, "shift") == 0) {
            shift(&vector, &queue_beg, &queue_end, &size, &actual_size);
        }
        else if (strcmp(opcao, "print-first") == 0) {
            printFirst(&vector, &queue_beg, &actual_size);
        }
        else if (strcmp(opcao, "push") == 0) {
            if (push(&vector, &queue_beg, &queue_end, &size, &actual_size, buffer)) {
                printf("Error in push!\n");
            }
        }
        else if (strcmp(opcao, "pop") == 0) {
            pop(&vector, &queue_beg, &queue_end, &size, &actual_size);
        }
        else if (strcmp(opcao, "print-last") == 0) {
            printLast(&vector, &queue_end, &actual_size);
        }
        else if (strcmp(opcao, "is-empty") == 0) {
            isEmpty(&actual_size);
        }
        else if (strcmp(opcao, "exit") == 0) {
            freeVector(&vector, &queue_beg, &actual_size);
            return 0;
        }
    }
}
