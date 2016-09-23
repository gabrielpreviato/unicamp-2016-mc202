/*
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int obtemOrdem(int* ordem_matriz);
int obtemMatriz(double **jagged_array, int *ordem_matriz);
double obtemMedia(double **jagged_array, int *ordem_matriz);
double square (double x);
double obtemDesvioPadrao(double **jagged_array, int *ordem_matriz, double *media);

int main(int argc, char const *argv[]) {
  int ordem_matriz, i, j;
  double media = 0, desvio_padrao = 0;
  double **jagged_array;

  // TODO: Obter o número da ordem da matriz
  obtemOrdem(&ordem_matriz);

  // TODO: Criar a jagged array
  jagged_array = malloc(sizeof(double *)*ordem_matriz);
  for (i = 0; i < ordem_matriz; i++) {
    jagged_array[i] = malloc(sizeof(double)*(i+1));
  }

  // TODO: Obter os valores da jagged array
  obtemMatriz(jagged_array, &ordem_matriz);

  // TODO: Obtem a média e desvio padrão dos valores da matriz
  media = obtemMedia(jagged_array, &ordem_matriz);
  desvio_padrao = obtemDesvioPadrao(jagged_array, &ordem_matriz, &media);

  // TODO: Imprime os elementos (x) da matriz, z = (x - m) / d
  // m = media, d = desvio padrao
  for (i = 0; i < ordem_matriz; i++) {
    for (j = 0; j <= i; j++) {
      printf("%.12lf ", (jagged_array[i][j] - media)/desvio_padrao);
    }
    printf("\n");
  }
  printf("\n%.12lf %.12lf \n", media, desvio_padrao);

  // TODO: Liberar todas as memórias
  for (i = 0; i < ordem_matriz; i++) {
    free(jagged_array[i]);
  }
  free(jagged_array);

  // FIM
  return 0;
}

int obtemOrdem(int* ordem_matriz) {
  // TODO: Obter a ordem da matriz
  return scanf("%d", ordem_matriz);
}

int obtemMatriz(double **jagged_array, int *ordem_matriz) {
  int i, j;
  // TODO: Obter os (n^2 + n)/2 elementos, dispostos em n linhas
  for (i = 0; i < *ordem_matriz; i++) {
    for (j = 0; j <= i; j++) {
      scanf("%lf", &jagged_array[i][j]);
    }
  }
  return 0;
}

double obtemMedia(double **jagged_array, int *ordem_matriz) {
  int i, j;
  double media = 0;
  // TODO: Itera a jagged array e obtem a média dos valores
  for (i = 0; i < *ordem_matriz; i++) {
    for (j = 0; j <= i; j++) {
      media += jagged_array[i][j];
    }
  }
  // IDEA: Número de elementos é (n^2 + n)/2
  double numero_elementos = (square(*ordem_matriz) + (*ordem_matriz)) / 2;

  return media / numero_elementos;
}

double square (double x) {
  // TODO: Retorna o quadrado de x
  return x*x;
}

double obtemDesvioPadrao(double **jagged_array, int *ordem_matriz, double *media) {
  int i, j;
  double desvio_padrao = 0;
  // TODO: Itera a jagged array e obtem o desvio padrao dos valores
  for (i = 0; i < *ordem_matriz; i++) {
    for (j = 0; j <= i; j++) {
      desvio_padrao += square(jagged_array[i][j] - *media);
    }
  }
  // IDEA: Número de elementos é (n^2 + n)/2
  double numero_elementos = (square(*ordem_matriz) + (*ordem_matriz)) / 2;

  return sqrt(desvio_padrao/numero_elementos);
}
