#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int readToBuffer(char *buffer) {
    // Initialize variables
    int i = 0, j = 0;
    char c = 0, test = 1;

    // Cleans last '\n' on input buffer
    getchar();

    // Iterate buffer putting on it character from scanf
    for (i = 0; i < BUFFER_SIZE; i++) {
        scanf("%c", &c);

        // In case we have spaces (' ') before the sentence itself
        if (test) {
            if (c == ' ') {
                // Decrease i so continue dont affect later string
                i--;
                continue;
            }
            else {
                test = 0;
            }
        }

        // 2 cases (c is a end of line, c is another charecter)
        if (c == '\n') {
            // End of the string
            buffer[i] = '\0';
            break;
        }
        else {
            buffer[i] = c;
        }
    }

    // Clean blank spaces after the sentence
    for (j = i - 2; buffer[j] == ' '; j--) {
        buffer[j] = '\0';
    }

    // Return the size of the string (including \0)
    return i + 1;
}

int freeVector(char ***vector, int *queue_beg, size_t *actual_size) {
    // Initialize variables
    int pointer = *queue_beg, i = 0;

    for (i = 0; i < *actual_size; i++) {
        // Free the memory allocated in position pointer on vector
        free((*vector)[pointer]);

        // In case pointer points to the last element of the vector, pointer updates to the first element
        if (pointer == (*actual_size) - 1) {
            pointer = 0;
        }
        else {
            pointer++;
        }
    }

    // Free the vector itself
    free(*vector);

    return 0;
}

int expandVector(char ***vector, int *queue_beg, int *queue_end, size_t *size) {
    // Initialize variables
    unsigned int i = 0;
    int pointer = *queue_beg;
    // Dinamically allocate new_vector with the double size of vector
    char **new_vector = malloc(sizeof(char *) * 2 * (*size));

    if (!new_vector) {
        printf("AFFE\n");
    }

    // Copy all elements of vector to new_vector, starting at the queue_beg
    for (i = 0; i < *size; i++) {
        // Add to the new vector the element pointed by pointer
        new_vector[i] = malloc(sizeof(char) * strlen((*vector)[pointer]));
        strcpy(new_vector[i], (*vector)[pointer]);
        //new_vector[i] =((*vector)[pointer]);

        // In case pointer points to the last element of vector, pointer update to
        // first element of vector, otherwise, pointer goes to next element
        if (pointer == (*size) - 1) {
            pointer = 0;
        }
        else {
            pointer++;
        }
    }

    freeVector(vector, queue_beg, size);

    // Update queue_beg and queue_end
    *queue_beg = 0;
    *queue_end = i - 1;

    // Update size value;
    *size = (*size) * 2;

    // Free the old vector and assing to vector the addres to the new one
    *vector = new_vector;

    return 0;
}

int push(char ***vector, int *queue_beg, int *queue_end, size_t *size,
         size_t *actual_size, char buffer[BUFFER_SIZE]) {
    // Declare variables
    int string_size = 0, pointer = 0;


    // In case the vector is full (size == actual_size), we need to expand it
    if (*size == *actual_size) {
        expandVector(vector, queue_beg, queue_end, size);
    }

    // In case queue_end point to the last element of the vector, pointer need to point
    // to the first element of the vector
    if (*queue_end == (*size) - 1) {
        pointer = 0;
    }
    else {
        pointer = (*queue_end) + 1;
    }

    // Read the string to be added and take the string size
    string_size = readToBuffer(buffer);

    // Dynamicaly allocate the string and copy the string in the buffer
    (*vector)[pointer] = malloc(sizeof(char) * string_size);
    if (!((*vector)[pointer])) {   // Test if string was successfully allocated
        return 1;
    }
    strcpy((*vector)[pointer], buffer);

    // Update queue_end and vector actual size
    *queue_end = pointer;
    (*actual_size)++;
    if (*actual_size == 1) {
        *queue_beg = pointer;
    }

    return 0;
}

int unshift(char ***vector, int *queue_beg, int *queue_end, size_t *size,
            size_t *actual_size, char buffer[BUFFER_SIZE]) {
    // Declare variables
    int string_size = 0, pointer = 0;


    // In case the vector is full (size == actual_size), we need to expand it
    if (*size == *actual_size) {
        expandVector(vector, queue_beg, queue_end, size);
    }

    // In case queue_beg point to the firts element of the vector, pointer need to point
    // to the last (after queue_end) element of the vector
    if (*queue_beg == 0) {
        pointer = (*size) - 1;
    }
    else {
        pointer = (*queue_beg) - 1;
    }

    // Read the string to be added and take the string size
    string_size = readToBuffer(buffer);

    // Dynamicaly allocate the string and copy the string in the buffer
    (*vector)[pointer] = malloc(sizeof(char) * string_size);
    if (!((*vector)[pointer])) {   // Test if string was successfully allocated
        return 1;
    }
    strcpy((*vector)[pointer], buffer);

    // Update queue_beg and vector actual size
    *queue_beg = pointer;
    (*actual_size)++;
    if (*actual_size == 1) {
        *queue_end = pointer;
    }

    return 0;
}

int printFirst(char ***vector, int *queue_beg, size_t *actual_size) {
    // In case the vector is empty
    if (*actual_size == 0) {
    }
        // Otherwise, print the first element
    else {
        printf("%s\n", (*vector)[*queue_beg]);
    }

    return 0;
}

int printLast(char ***vector, int *queue_end, size_t *actual_size) {
    // In case the vector is empty
    if (*actual_size == 0) {
    }
        // Otherwise, print the last element
    else {
        printf("%s\n", (*vector)[*queue_end]);
    }

    return 0;
}

int isEmpty(size_t *actual_size) {
    // In case vector is empty, print yep, otherwise print nope
    if (*actual_size) {
        printf("nope\n");
    }
    else {
        printf("yep\n");
    }

    return 0;
}

int decreaseVector(char ***vector, int *queue_beg, int *queue_end, size_t *size) {
    // Initialize variables
    unsigned int i = 0;
    int pointer = *queue_beg;
    char **new_vector = NULL;

    // Dinamically allocate new_vector with the double size of vector
    new_vector = malloc(sizeof(char *) * (*size) / 2);


    // Copy all elements of vector to new_vector, starting at the queue_beg
    for (i = 0; i < (*size) / 4; i++) {
        // Add to the new vector the element pointed by pointer
        new_vector[i] = (*vector)[pointer];

        // In case pointer points to the last element of vector, pointer update to first element of vector
        if (pointer == (*size) - 1) {
            pointer = 0;
        }
        else {
            pointer++;
        }
    }

    // Update queue_beg and queue_end
    *queue_beg = 0;
    *queue_end = i - 1;

    // Update size value;
    *size = (*size) / 2;

    // Free the old vector and assing to vector the addres to the new one
    free(*vector);
    *vector = new_vector;

    return 0;
}

int shift(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size) {

    // In case the vector is empty
    if (*actual_size == 0) {
        return 0;
    }

    // Free the first element in the queue and update actual size
    free((*vector)[*queue_beg]);
    (*vector)[*queue_beg] = NULL;
    (*actual_size)--;

    // In case the queue_beg was the last element in the vector and actual size is greater than 0
    if (*queue_beg == (*size) - 1 && *actual_size > 0) {
        *queue_beg = 0;
    }
        // In case the actua size becomes 0 or 1/4 of the total, decrease the vector
    else if (*actual_size == 0 || *actual_size == (*size) / 4) {
        decreaseVector(vector, queue_beg, queue_end, size);
    }
    else {
        (*queue_beg)++;
    }

    return 0;
}

int pop(char ***vector, int *queue_beg, int *queue_end, size_t *size, size_t *actual_size) {

    // In case the vector is empty
    if (*actual_size == 0) {
        return 0;
    }

    // Free the first element in the queue and update actual size
    free((*vector)[*queue_end]);
    (*actual_size)--;

    // In case the queue_end was the first element in the vector and actual size is greater than 0
    if (*queue_end == 0 && *actual_size > 0) {
        *queue_end = (int) (*size);
    }
        // In case the actua size becomes 0 or 1/4 of the total, decrease the vector
    else if (*actual_size == 0 || *actual_size == (*size) / 4) {
        decreaseVector(vector, queue_beg, queue_end, size);
    }
    else {
        (*queue_end)--;
    }

    return 0;
}

