#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

typedef struct node {
    char value;
    struct node *left, *right;
} node_t;

node_t* buscar(node_t *node, int value);

int main(int argc, char const *argv[]) {

    // Declare tree root
    //node_t *root = NULL;
    char option[10];

    while (TRUE) {
        if (strcmp(option, "inserir")) {
        }
        else if (strcmp(option, "excluir")) {
        }
        else if (strcmp(option, "buscar")) {
        }
        else if (strcmp(option, "minimo")) {
        }
        else if (strcmp(option, "maximo")) {
        }
        else if (strcmp(option, "pos-ordem")) {
        }
        else if (strcmp(option, "em-ordem")) {
        }
        else if (strcmp(option, "pre-ordem")) {
        }
        else if (strcmp(option, "largura")) {
        }
        else if (strcmp(option, "terminar")) {
            //liberatudo();
            return 0;
        }
    }
}

node_t* inserir(node_t *node, int value) {
    if (!node) {
        node_t *ptr = malloc(sizeof(node_t));
        if (!ptr) {
            printf("memoria insuficiente\n");
            return NULL;
        }
        return ptr;
    }
    else if (value < node->value) {
        return inserir(node->left, value);
    }
    else if (value > node->value) {
        return inserir(node->right, value);
    }

    return NULL;
}

node_t* buscar(node_t *node, int value) {
    if (!node) {
        return NULL;
    }
    else if (value == node->value) {
        return node;
    }
    else if (value < node->value) {
        return buscar(node->left, value);
    }
    else if (value > node->value) {
        return buscar(node->right, value);
    }

    return NULL;
}
