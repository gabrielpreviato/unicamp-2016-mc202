#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void getEntries(int* entries, int k, int *row, int *col);
void getOrderedEntries(int *entries, int *ordered, int k, int *row, int *col);
void getA(int *A, int* ordered, int k);
void getIA(int *IA, int* ordered, int row, int k);
void getJA(int *JA, int* ordered, int k);
int searchCSR(int *A, int *IA, int *JA, int row, int col, int i, int j);

int main(int argc, char const *argv[]) {
    // Number of entries
    int i, k;
    scanf("%d", &k);

    // Dynamic vector of entries with 3*k elements [i1, j1, d1, i2, j2, d2, ...]
    int maxRow = 0, maxCollum = 0;
    int* entries = malloc(sizeof(int)*k*3);
    getEntries(entries, k, &maxRow, &maxCollum);

    // Order the vector of entries
    int* ordered_entries = malloc(sizeof(int)*k*3);
    for (i = 0; i < 3*k; i++) {
        ordered_entries[i] = -1;
    }

    /*for (i = 0; i < k; i++) {
        printf("%d %d %d\n", entries[3*i], entries[3*i + 1], entries[3*i + 2]);
    }*/

    getOrderedEntries(entries, ordered_entries, k, &maxRow, &maxCollum);

    /*printf("\n");
    for (i = 0; i < k; i++) {
        printf("%d %d %d\n", ordered_entries[3*i], ordered_entries[3*i + 1], ordered_entries[3*i + 2]);
    }*/

    // Start CSR algorithm
    int *A = malloc(sizeof(int)*k);
    int *IA = malloc(sizeof(int)*(maxRow+2));
    int *JA = malloc(sizeof(int)*k);

    getA(A, ordered_entries, k);
    /*for (i = 0; i < k; i++) {
        printf("%d ", A[i]);
    }*/
    getIA(IA, ordered_entries, maxRow, k);
    /*for (i = 0; i < maxRow + 2; i++) {
        printf("%d ", IA[i]);
    }*/
    getJA(JA, ordered_entries, k);
    /*for (i = 0; i < k; i++) {
        printf("%d ", JA[i]);
    }*/

    // Start searching numbers
    int row, col;
    scanf("%d %d", &row, &col);
    while (row != -1 && col != -1) {
        printf("(%d,%d) = %d\n", row, col, searchCSR(A, IA, JA, maxRow, maxCollum, row, col));
        scanf("%d %d", &row, &col);
    }

    free(A);
    free(IA);
    free(JA);
    free(entries);
    free(ordered_entries);
    return 0;
}

void getEntries(int* entries, int k, int *row, int *col) {
    int i;
    for (i = 0; i < k; i++) {
        scanf("%d %d %d", &entries[3*i], &entries[3*i + 1], &entries[3*i + 2]);
        // Update max values
        if (entries[3*i] > *row)
            *row = entries[3*i];
        if (entries[3*i + 1] > *col)
            *col = entries[3*i + 1];
    }
}

void getOrderedEntries(int *entries, int *ordered, int k, int *row, int *col) {
    int i, j = 0, n = 0;

    while (1) {
        for (i = 1; i < k; i++) {
            if (entries[3*i] < entries[3*j]) {
                j = i;
            }
            else if (entries[3*i] == entries[3*j] && entries[3*i + 1] < entries[3*j + 1]) {
                j = i;
            }
        }

        ordered[3*n] = entries[3*j];
        ordered[3*n + 1] = entries[3*j + 1];
        ordered[3*n + 2] = entries[3*j + 2];
        n++;

        // Make entries[j] bigger than all, so won't be added twice
        entries[3*j] = *row + 1;
        entries[3*j + 1] = *col + 1;

        // Condition to end the loop
        if (n == k) {
            break;
        }
    }
}

void getA(int *A, int* ordered, int k) {
    int i;
    for (i = 0; i < k; i++) {
        A[i] = ordered[3*i + 2];
    }
}

void getIA(int *IA, int* ordered, int row, int k) {
    int i, n, count = 0;
    IA[0] = 0;
    for (i = 1; i < row + 2; i++) {
        for (n = 0; n < k; n++) {
            if (ordered[3*n] == i - 1) {
                count++;
            }
        }
        IA[i] = IA[i -1] + count;
        count = 0;
    }
}

void getJA(int *JA, int* ordered, int k) {
    int i;
    for (i = 0; i < k; i++) {
        JA[i] = ordered[3*i + 1];
    }
}

int searchCSR(int *A, int *IA, int *JA, int row, int col, int i, int j) {
    // Out of the "matrix"
    if (i > row || j > col) {
        return 0;
    }

    // No numbers in row i
    if (IA[i + 1] - IA[i] == 0) {
        return 0;
    }

    // Search j in JA
    int n;
    for (n = IA[i]; n < IA[i + 1]; n++) {
        if (JA[n] == j) {
            return A[n];
        }
    }

    // Didn't find the collum
    return 0;
}
