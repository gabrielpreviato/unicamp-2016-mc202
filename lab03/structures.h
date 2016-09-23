#ifndef STRUCTURES_H
#define STRUCTURES_H

// NOTE: Estrutura nó
typedef struct no_struct {
    struct no_struct *A;
    struct no_struct *B;
    double valor;
} no;

// NOTE: Estrutura cabeça de nó (sentinela)
typedef struct {
    no *apont;
    int posicao;
} sentinela;

#endif
