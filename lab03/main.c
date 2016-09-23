#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "functions.h"

#define TRUE 1

int main() {

    char opcao;
    sentinela *cabeca, *rabo;

    criarLista(&cabeca, &rabo);

    while (TRUE) {
        scanf(" %c", &opcao);

        switch (opcao) {
            case 'i':
                if (inserir(&cabeca, &rabo)) {
                    printf("Insertion ERROR\n");
                    return 1;
                }
                break;
            case 'p':
                imprimir(&cabeca, &rabo);
                break;
            case 'v':
                inverter(&cabeca, &rabo);
                break;
            case 't':
                liberar(&cabeca, &rabo);
                return 0;
            default:
                printf("ERROR!\n");
                return 1;
        }
    }
}

int criarLista(sentinela **cabeca, sentinela **rabo) {
    *cabeca = malloc(sizeof(sentinela));
    *rabo = malloc(sizeof(sentinela));

    if (!*cabeca || !*rabo){
        printf("Memory allocation error in criarLista()\n");
        return 1;
    }

    (*cabeca)->posicao = 0;
    (*rabo)->posicao = -1;

    return 0;
}

int inserir(sentinela **cabeca, sentinela **rabo) {
    int posicao, i;
    double valor;
    no *apontador, *auxiliar = (*cabeca)->apont;

    no* lista = malloc(sizeof(no));

    if (!lista) {
        printf("Memory allocation error in inserir()\n");
        return 1;
    }

    scanf("%d %lf", &posicao, &valor);

    if ((*rabo)->posicao == -1) {
        (*cabeca)->apont = lista;
        (*rabo)->apont = lista;
        lista->A = NULL;
        lista->B = NULL;
        lista->valor = valor;
        (*rabo)->posicao = 0;
        return 0;
    }

    else if (posicao == 0) {
        if ((*cabeca)->apont->A == NULL) {
            (*cabeca)->apont->A = lista;
            lista->B = (*cabeca)->apont;
            lista->A = NULL;
            (*cabeca)->apont = lista;
        }
        else {
            (*cabeca)->apont->B = lista;
            lista->B = (*cabeca)->apont;
            lista->A = NULL;
            (*cabeca)->apont = lista;
        }

        lista->valor = valor;
        ++((*rabo)->posicao);
        return 0;
    }

    else if (posicao > (*rabo)->posicao) {
        if ((*rabo)->apont->A == NULL) {
            (*rabo)->apont->A = lista;
            lista->A = (*rabo)->apont;
            lista->B = NULL;
            (*rabo)->apont = lista;
        }
        else {
            (*rabo)->apont->B = lista;
            lista->A = (*rabo)->apont;
            lista->B = NULL;
            (*rabo)->apont = lista;
        }

        lista->valor = valor;
        ++((*rabo)->posicao);
        return 0;
    }

    else {
        if ((*cabeca)->apont->A == NULL) {
            apontador = (*cabeca)->apont->B;
        }
        else {
            apontador = (*cabeca)->apont->A;
        }

        for (i = 0; i < posicao - 1; i++) {
            if (apontador->A == auxiliar) {
                auxiliar = apontador;
                apontador = apontador->B;
            }
            else {
                auxiliar = apontador;
                apontador = apontador->A;
            }
        }

        if (auxiliar->A == apontador) {
            auxiliar->A = lista;
            lista->A = apontador;
            lista->B = auxiliar;
            if (apontador->A == auxiliar) {
                apontador->A = lista;
            }
            else {
                apontador->B = lista;
            }
        }

        else {
            auxiliar->B = lista;
            lista->A = apontador;
            lista->B = auxiliar;
            if (apontador->A == auxiliar) {
                apontador->A = lista;
            }
            else {
                apontador->B = lista;
            }
        }

        lista->valor = valor;
        ++((*rabo)->posicao);
        return 0;
    }
}

int imprimir(sentinela **cabeca, sentinela **rabo) {
    int i;
    no *apontador = (*cabeca)->apont, *auxiliar = (*cabeca)->apont;

    if ((*rabo)->posicao == -1){
    }

    else {

        printf("%.4lf ", apontador->valor);

        if (apontador->A == NULL) {
            apontador = apontador->B;
        } else {
            apontador = apontador->A;
        }

        for (i = 0; apontador != NULL; i++) {

            printf("%.4lf ", apontador->valor);

            if (apontador->A == auxiliar) {
                auxiliar = apontador;
                apontador = apontador->B;
            } else {
                auxiliar = apontador;
                apontador = apontador->A;
            }
        }
    }

    printf("\n");

    return 0;
}

int inverter(sentinela **cabeca, sentinela **rabo) {
    int inicio, termino, i;
    no *apontador = (*cabeca)->apont, *apontador2 = (*cabeca)->apont, *aux1 = (*cabeca)->apont, *aux2 = (*cabeca)->apont;

    scanf("%d %d", &inicio, &termino);

    if (inicio == termino) {
        return 0;
    }

    else if (inicio == 0 && termino == (*rabo)->posicao) {
        apontador = (*rabo)->apont;
        (*rabo)->apont = (*cabeca)->apont;
        (*cabeca)->apont = apontador;
        return 0;
    }

    else if (inicio == 0) {

        for (i = 0; i < termino; i++) {
            if (apontador->A == aux1) {
                aux1 = apontador;
                apontador = apontador->B;
            }
            else {
                aux1 = apontador;
                apontador = apontador->A;
            }
        }

        if (apontador->A == aux1) {
            aux2 = apontador->B;

            if (aux2->A == apontador) {
                aux2->A = (*cabeca)->apont;
            }
            else {
                aux2->B = (*cabeca)->apont;
            }
            apontador->B = NULL;

            if ((*cabeca)->apont->A == NULL) {
                (*cabeca)->apont->A = aux2;
            }
            else {
                (*cabeca)->apont->B = aux2;
            }

            (*cabeca)->apont = apontador;
        }

        else {
            aux2 = apontador->A;

            if (aux2->A == apontador) {
                aux2->A = (*cabeca)->apont;
            }
            else {
                aux2->B = (*cabeca)->apont;
            }
            apontador->A = NULL;

            if ((*cabeca)->apont->A == NULL) {
                (*cabeca)->apont->A = aux2;
            }
            else {
                (*cabeca)->apont->B = aux2;
            }

            (*cabeca)->apont = apontador;
        }

        return 0;
    }

    else if (termino == (*rabo)->posicao) {
        for (i = 0; i < inicio; i++) {
            if (apontador->A == aux1) {
                aux1 = apontador;
                apontador = apontador->B;
            }
            else {
                aux1 = apontador;
                apontador = apontador->A;
            }
        }

        if (apontador->A == aux1) {

            if (aux1->A == apontador) {
                aux1->A = (*rabo)->apont;
            }
            else {
                aux1->B = (*rabo)->apont;
            }
            apontador->A = NULL;

            if ((*rabo)->apont->A == NULL) {
                (*rabo)->apont->A = aux1;
            }
            else {
                (*rabo)->apont->B = aux1;
            }

            (*rabo)->apont = apontador;
        }

        else {

            if (aux1->A == apontador) {
                aux1->A = (*rabo)->apont;
            }
            else {
                aux1->B = (*rabo)->apont;
            }
            apontador->B = NULL;

            if ((*rabo)->apont->A == NULL) {
                (*rabo)->apont->A = aux1;
            }
            else {
                (*rabo)->apont->B = aux1;
            }

            (*rabo)->apont = apontador;
        }

        return 0;
    }

    else {

        for (i = 0; i < inicio; i++) {
            if (apontador->A == aux1) {
                aux1 = apontador;
                apontador = apontador->B;
            }
            else {
                aux1 = apontador;
                apontador = apontador->A;
            }
        }

        for (i = 0; i < termino + 1; i++) {
            if (apontador2->A == aux2) {
                aux2 = apontador2;
                apontador2 = apontador2->B;
            }
            else {
                aux2 = apontador2;
                apontador2 = apontador2->A;
            }
        }

        if(aux1->A == apontador) {
            aux1->A = aux2;
        }
        else {
            aux1->B = aux2;
        }

        if (apontador2->A == aux2) {
            apontador2->A = apontador;
        }
        else {
            apontador2->B = apontador;
        }

        if (aux2->A == apontador2) {
            aux2->A = aux1;
        }
        else {
            aux2->B = aux1;
        }

        if (apontador->A == aux1) {
            apontador->A = apontador2;
        }
        else {
            apontador->B = apontador2;
        }

        return 0;
    }
}

int liberar(sentinela **cabeca, sentinela **rabo) {
    int i;
    no *apontador = (*cabeca)->apont, *auxiliar = (*cabeca)->apont;

    if ((*rabo)->posicao == -1){
    }

    else {

        if (apontador->A == NULL) {
            apontador = apontador->B;
        } else {
            apontador = apontador->A;
        }

        for (i = 0; apontador != NULL; i++) {

            free(auxiliar);

            if (apontador->A == auxiliar) {
                auxiliar = apontador;
                apontador = apontador->B;
            } else {
                auxiliar = apontador;
                apontador = apontador->A;
            }
        }
    }

    free(*cabeca);
    free(*rabo);

    return 0;
}