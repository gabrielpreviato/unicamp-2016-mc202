/*
*   Nome: Gabriel Previato de Andrade
*   RA: 172388
*   Turma: A
*
*   Esse programa tem como função, criar uma lista ligada com N (0 < N <= 100)
*   nós e implementar 3 métodos de organização dessa lista. Serão feitas R
*   requisições (0 < R <= 100). Então, o programa exibe a quantidade de acessos
*   a memória feita por cada um dos métodos de organização.
*/

// TODO: Incluir as livrarias stdio e stdlib e os headers criados para o programa
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "functions.h"

// TODO: Definir valores de TRUE e FALSE
#define TRUE 1
#define FALSE 0

int main () {
    // NOTE: Variáveis escopo main
    int i, N, R, custo;
    int *array_R = NULL;
    sentinela *L = NULL;

    // TODO: Obtem as entradas
    scanf("%d %d", &N, &R);

    // IDEA: Array dinâmica para armazenar os acesso
    array_R = (int*)malloc(sizeof(int)*R);

    for(i = 0; i < R; i++) {
        scanf("%d", &array_R[i]);
    }

    // IDEA: Para testarmos a eficiência dos 3 métodos de organização de array_R
    // criaremos 3 listas, criando a lista e realizando sua ordenação

    // TODO: Criar Lista Ligada (primeira) para armazenar os registro
    criaListaLigada(&L, N);
    // TODO: Organizar a lista pelo MTF (Move-to-front)
    custo = listaMTF(&L, R, array_R, N);
    printf("%d ", custo);
    // TODO: Liberar a memória alocada para a lista (primeira)
    destroiLista(&L, N);


    // TODO: Criar Lista Ligada (segunda) para armazenar os registro
    criaListaLigada(&L, N);
    // TODO: Organizar a lista pelo MTF (Move-to-front)
    custo = listaTR(&L, R, array_R, N);
    printf("%d ", custo);
    // TODO: Liberar a memória alocada para a lista (segunda)
    destroiLista(&L, N);


    // TODO: Criar Lista Ligada (terceira) para armazenar os registro
    criaListaLigada(&L, N);
    // TODO: Organizar a lista pelo MTF (Move-to-front)
    custo = listaC(&L, R, array_R, N);
    printf("%d\n", custo);
    // TODO: Liberar a memória alocada para a lista (terceira)
    destroiLista(&L, N);


    // TODO: Liberar a memória alocada dinamicamente para a array
    free(array_R);

    return 0;
}

int criaListaLigada(sentinela** L, int N) {
    int i;
    no *apontador = NULL;
    no* novo = NULL;

    // TODO: Criar a cabeça de nó da lista
    *L = (sentinela*)malloc(sizeof(sentinela));

    // TODO: Criar todos os outros nós
    for (i = 0; i < N; i++) {

        // IDEA: Caso seja o primeiro nó, alocar o apontado sentinela no cabeça de nó
        if (i == 0) {
            novo = (no*)malloc(sizeof(no));
            (*L)->cabeca_no = novo;
            apontador = (*L)->cabeca_no;
        }

        // IDEA: Caso seja o último nó, o próximo nó sera NULL
        else if (i == N-1) {
            novo = (no*)malloc(sizeof(no));
            apontador->proximo = novo;
            apontador = apontador->proximo;
            apontador->proximo = NULL;
        }

        // IDEA: Caso contrário, alocar o apontador do próximo nó
        else {
            novo = (no*)malloc(sizeof(no));
            apontador->proximo = novo;
            apontador = apontador->proximo;
        }
    }

    // TODO: Preencher cada nó com o seu respectivo valor (ordem crescente)
    apontador = (*L)->cabeca_no;

    for (i = 1; i <= N; i++) {
        apontador->valor = i;
        apontador->count = 0;
        apontador = apontador->proximo;
    }

    return 0;
}


int destroiLista(sentinela **L, int N) {
    int i;
    no* apontador = (*L)->cabeca_no;

    // TODO: Desalocar os N nós
    for(i = 0; i < N; i++) {
        (*L)->cabeca_no = (*L)->cabeca_no->proximo;
        free(apontador);
        apontador = (*L)->cabeca_no;
    }

    // TODO: Desalocar a sentinela
    free(*L);

    return 0;
}

int listaMTF(sentinela **L, int R, int *array_R, int N) {
    int i, j, contador = 0;
    no *apontador, *aux;

    // TODO: Iterar a array de requisições
    for (i = 0; i < R; i++) {
        apontador = (*L)->cabeca_no;
        aux = (*L)->cabeca_no;

        // TODO: Passar pela lista buscando o nó com a requisição
        for (j = 0; j < N; j++) {

            // IDEA: Aumenta o contador para cada acesso
            contador++;

            // IDEA: Primeiro caso, primeiro nó da lista
            if (apontador == (*L)->cabeca_no) {

                // IDEA: Caso o valor do primeiro nó seja o requisitado, fazer nada
                if (apontador->valor == array_R[i]) {
                    apontador = apontador->proximo;
                    break;
                }

                // IDEA: Caso contrário, passaremos para o próximo nó (continue no for)
                apontador = apontador->proximo;
                continue;
            }

            // IDEA: Para os outros casos
            else{

                // IDEA: Caso o nó tenha o valor requisitado, jogá-lo para o inicio da lista
                if (apontador->valor == array_R[i]) {
                    aux->proximo = apontador->proximo;
                    apontador->proximo = (*L)->cabeca_no;
                    (*L)->cabeca_no = apontador;
                    break;
                }

                // IDEA: Caso o nó NÃO tenha o valor requisitado, avançar de nó
                aux = apontador;
                apontador = apontador->proximo;
            }
        }
    }

  return contador;
}

int listaTR(sentinela **L, int R, int *array_R, int N) {
    int i, j, contador = 0;
    no *apontador, *aux;
    char primeiro_caso, segundo_caso;

    // TODO: Iterar a array de requisições
    for (i = 0; i < R; i++) {
        apontador = (*L)->cabeca_no;
        aux = (*L)->cabeca_no;
        primeiro_caso = TRUE;
        segundo_caso = TRUE;

        // TODO: Passar pela lista buscando o nó com a requisição
        for (j = 0; j < N; j++) {

            // IDEA: Aumenta o contador para cada acesso
            contador++;

            // IDEA: Primeiro caso, primeiro nó da lista
            if (primeiro_caso) {

                // IDEA: Caso o valor do primeiro nó seja o requisitado, fazer nada
                if (apontador->valor == array_R[i]) {
                    apontador = apontador->proximo;
                    primeiro_caso = FALSE;
                    break;
                }

                // IDEA: Caso contrário, passaremos para o próximo nó (continue no for)
                apontador = apontador->proximo;
                primeiro_caso = FALSE;
                continue;
            }

            // IDEA: Segundo caso, segundo nó da lista
            if (segundo_caso) {

                // IDEA: Caso o valor do segundo nó seja o requisitado, alternar com o primeiro, alterando
                // a cabeça do nó
                if (apontador->valor == array_R[i]) {
                    aux->proximo = apontador->proximo;
                    apontador->proximo = aux;
                    (*L)->cabeca_no = apontador;
                    segundo_caso = FALSE;
                    break;
                }

                // IDEA: Caso contrário, passaremos para o próximo nó (continue no for)
                segundo_caso = FALSE;
                continue;
            }

            // IDEA: Para os outros casos
            else{

                // IDEA: Caso o nó tenha o valor requisitado, trocar de posição
                if (apontador->proximo->valor == array_R[i]) {
                    aux->proximo = apontador->proximo;
                    apontador->proximo = apontador->proximo->proximo;
                    aux->proximo->proximo = apontador;
                    break;
                }

                // IDEA: Caso o nó NÃO tenha o valor requisitado, avançar de nó
                aux = apontador;
                apontador = apontador->proximo;
            }
        }
    }




    return contador;
}

int listaC(sentinela **L, int R, int *array_R, int N) {
    int i, j, contador = 0, max_count = 0;
    no *apontador, *aux1, *aux2;

    // TODO: Iterar a array de requisições
    for (i = 0; i < R; i++) {
        apontador = (*L)->cabeca_no;
        aux1 = (*L)->cabeca_no;
        aux2 = (*L)->cabeca_no;

        // TODO: Passar pela lista buscando o nó com a requisição
        for (j = 0; j < N; j++) {

            // IDEA: Aumenta o contador para cada acesso
            contador++;

            // IDEA: Primeiro caso, primeiro nó da lista
            if (apontador == (*L)->cabeca_no) {

                // IDEA: Caso o valor do primeiro nó seja o requisitado, fazer nada
                if (apontador->valor == array_R[i]) {
                    apontador->count++;
                    max_count = apontador->count;
                    break;
                }

                // IDEA: Caso contrário, passaremos para o próximo nó (continue no for)
                apontador = apontador->proximo;
                continue;
            }

            // IDEA: Para os outros casos
            else{

                // IDEA: Caso o nó tenha o valor requisitado, jogá-lo para o inicio da lista ou
                // para o inicio dos nós com o mesmo numeros de requisições que ele (auxiliar2) ou
                // para frente do nó que tenha um número mais de requisições que ele
                if (apontador->valor == array_R[i]) {
                    apontador->count++;
                    if ((apontador->count) >= max_count) {
                        max_count = apontador->count;
                        aux1->proximo = apontador->proximo;
                        apontador->proximo = (*L)->cabeca_no;
                        (*L)->cabeca_no = apontador;
                    }
                    else if((apontador->count) <= (aux2->count) - 1 && aux1 != aux2) {
                        aux1->proximo = apontador->proximo;
                        apontador->proximo = aux2->proximo;
                        aux2->proximo = apontador;
                    }

                    break;
                }

                // IDEA: Caso o nó NÃO tenha o valor requisitado, avançar de nó
                aux1 = apontador;
                if(aux1->count >= apontador->proximo->count + 2) {
                    aux2 = apontador;
                }
                else {}
                apontador = apontador->proximo;
            }
        }
    }

  return contador;
}
