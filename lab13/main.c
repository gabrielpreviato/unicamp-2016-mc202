#include "includes.h"

int main(int argc, char const *argv[]) {
    clock_t t1;
    int count = 0, i, j, sizes[4] = {1000, 10000, 100000, 1000000}, k = 0;
    double logSum = 0;
    double logResults[4] = {ceil(log2(1000)), ceil(log2(10000)),
        ceil(log2(100000)), ceil(log2(1000000))};

    for (i = 0; i < 4; i++) {
        logSum += logResults[i];
    }

    // Dynamic arrays allocation
    double *timeResultsMerge = malloc(sizeof(double)*(logSum));
    double *timeResultsQuick = malloc(sizeof(double)*(logSum));
    double *timeResultsHeap = malloc(sizeof(double)*(logSum));
    double *timeResultsShell = malloc(sizeof(double)*(logSum));
    double *timeResultsShellLog = malloc(sizeof(double)*(logSum));

    // File opening
    FILE *file = fopen("results.out", "a");

    // For all vector sizes (4)
    for (j = 0; j < 4; j++) {
        int *elements = malloc(sizeof(int)*sizes[j]);
        int *working = malloc(sizeof(int)*sizes[j]);

        // Sort log10(size of the vector) vectors
        for (count = 0; count < logResults[j]; count++) {
            // Generate a random key based on the time (for "pseudo-ramdonness")
            srand(time(NULL));

            // Inizialize the vector
            for (i = 0; i < sizes[j]; ++i)
                elements[i] = i;

            // Shuffle the vector
            for (i = sizes[j] - 1; i > 0; --i) {
                // Generate random index
                int w = rand()%i;
                // Swap items
                int t = elements[i];
                elements[i] = elements[w];
                elements[w] = t;
            }

            // Before every sort we must copy the element vector to a working vector

            // MergeSort
            copyArray(working, elements, sizes[j]);
            // Start measuring time
            t1 = clock();
            // Do the sort
            mergesort(working, 0, sizes[j] - 1, sizes[j]);
            // Finish measuring and store the result
            t1 = clock() - t1;
            timeResultsMerge[k] = t1/(double)CLOCKS_PER_SEC;

            // QuickSort
            copyArray(working, elements, sizes[j]);
            // Start measuring time
            t1 = clock();
            // Do the sort
            qsort(working, sizes[j], sizeof(int), cmpfunc);

            // Finish measuring and store the result
            t1 = clock() - t1;
            timeResultsQuick[k] = t1/(double)CLOCKS_PER_SEC;

            // HeapSort
            copyArray(working, elements, sizes[j]);
            // Start measuring time
            t1 = clock();
            // Do the sort
            heapsort(working, sizes[j]);

            // Finish measuring and store the result
            t1 = clock() - t1;
            timeResultsHeap[k] = t1/(double)CLOCKS_PER_SEC;

            // ShellSort w/ gap = 1
            copyArray(working, elements, sizes[j]);
            // Start measuring time
            t1 = clock();
            // Do the sort
            shellSort1(working, sizes[j]);

            // Finish measuring and store the result
            t1 = clock() - t1;
            timeResultsShell[k] = t1/(double)CLOCKS_PER_SEC;

            // ShellSort w/ gap = log2(size)
            copyArray(working, elements, sizes[j]);
            // Start measuring time
            t1 = clock();
            // Do the sort
            shellSortLog(working, sizes[j]);

            // Finish measuring and store the result
            t1 = clock() - t1;
            timeResultsShellLog[k] = t1/(double)CLOCKS_PER_SEC;


            // Increment k
            k++;
        }

        free(elements);
        free(working);
    }

    for (i = 0; i < logSum; i++) {
        printf("%.6lf ", timeResultsMerge[i]);
    }
    printf("\n");
    printf("\n");
    for (i = 0; i < logSum; i++) {
        printf("%.6lf ", timeResultsQuick[i]);
    }
    printf("\n");
    printf("\n");
    for (i = 0; i < logSum; i++) {
        printf("%.6lf ", timeResultsHeap[i]);
    }
    printf("\n");
    printf("\n");
    for (i = 0; i < logSum; i++) {
        printf("%.6lf ", timeResultsShell[i]);
    }
    printf("\n");
    printf("\n");
    for (i = 0; i < logSum; i++) {
        printf("%.6lf ", timeResultsShellLog[i]);
    }
    printf("\n");

    // Put the results on the file
    saveResults(file, timeResultsMerge, timeResultsQuick, timeResultsHeap,
        timeResultsShell, timeResultsShellLog, logResults);

    // Dynamic arrays de-allocation
    free(timeResultsMerge);
    free(timeResultsQuick);
    free(timeResultsHeap);
    free(timeResultsShell);
    free(timeResultsShellLog);

    return 0;
}

void copyArray(int *A, int *B, int k) {
    int i;
    for (i = 0; i < k; i++) {
        A[i] = B[i];
    }
}// Dynamic arrays allocation

void merge(int a[], int low, int mid, int high, int size) {
    int b[size];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= mid)
        b[k++] = a[i++];

    while (j <= high)
        b[k++] = a[j++];

    k--;
    while (k >= 0) {
        a[low + k] = b[k];
        k--;
    }
}

void mergesort(int a[], int low, int high, int size) {
    if (low < high) {
        int m = (high + low)/2;
        mergesort(a, low, m, size);
        mergesort(a, m + 1, high, size);
        merge(a, low, m, high, size);
    }
}

int cmpfunc(const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

void heapsort(int a[], int n) {
   int i = n / 2, pai, filho, t;
   for (;;) {
      if (i > 0) {
          i--;
          t = a[i];
      } else {
          n--;
          if (n == 0) return;
          t = a[n];
          a[n] = a[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < n) {
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t) {
             a[pai] = a[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      a[pai] = t;
   }
}

void shellSort1(int *vet, int size) {
    int i , j , value;
    int gap = 1;
    while(gap < size) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
            }
            vet [j + gap] = value;
        }
    }
}

void shellSortLog(int *vet, int size) {
    int i , j , value;
    int gap = (int)ceil(log2(size));
    while(gap < size) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
            }
            vet [j + gap] = value;
        }
    }
}

double countResultLog(double *logResults, double k) {
    int i, result = 0;
    for (i = 0; i < k; i++) {
        result += logResults[i];
    }
    
    return result;
}

void saveResults(FILE *file, double *merge, double *quick, double *heap,
    double *shell1, double *shellLog, double *logResults) {
    int j;

    fprintf(file, "%.6lf ", mean(merge, 0, logResults[0]));
    fprintf(file, "%.6lf ", mean(quick, 0, logResults[0]));
    fprintf(file, "%.6lf ", mean(heap, 0, logResults[0]));
    fprintf(file, "%.6lf ", mean(shell1, 0, logResults[0]));
    fprintf(file, "%.6lf\n", mean(shellLog, 0, logResults[0]));

    for (j = 1; j < 4; j++) {
        printf("---%lf---|---%lf---\n", countResultLog(logResults, j), logResults[j]);
        fprintf(file, "%.6lf ", mean(merge, countResultLog(logResults, j), logResults[j]));
        fprintf(file, "%.6lf ", mean(quick, countResultLog(logResults, j), logResults[j]));
        fprintf(file, "%.6lf ", mean(heap, countResultLog(logResults, j), logResults[j]));
        fprintf(file, "%.6lf ", mean(shell1, countResultLog(logResults, j), logResults[j]));
        fprintf(file, "%.6lf\n", mean(shellLog, countResultLog(logResults, j), logResults[j]));
    }
}

double mean(double *vec, double init, double end) {
    int i;
    double mean = 0;

    for (i = init; i < init + end; i++) {
        mean += vec[i];
    }

    return mean/(end);
}
