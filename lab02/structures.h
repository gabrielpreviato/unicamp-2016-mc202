#ifndef STRUCTURES
#define STRUCTURES 1

// NOTE: Estrutura nó
typedef struct no {
  struct no *proximo;
  char valor;
  char count;
} no;

// NOTE: Estrutura cabeça de nó (sentinela)
typedef struct {
  no *cabeca_no;
} sentinela;

#endif
