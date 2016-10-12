#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int value;
    struct node *left, *right;
} node_t;

node_t* inserir(node_t *node, int value);
node_t* buscar(node_t *node, int value);
node_t* excluir(node_t *node, int value);
int minimo(node_t *node);
int maximo(node_t *node);
int terminar(node_t *node);
int preOrdem(node_t *node);
int emOrdem(node_t *node);
int posOrdem(node_t *node);
int printBreadth(node_t *root);

int main(int argc, char const *argv[]) {
    int value;
    // Declare tree root
    node_t *root = NULL;
    char option[10];

    while (scanf("%s", option)) {
        if (!strcmp(option, "inserir")) {
            scanf("%d", &value);
            if (!buscar(root, value)) {
                root = inserir(root, value);
            }
        }
        else if (!strcmp(option, "excluir")) {
            scanf("%d", &value);
            if (buscar(root, value)) {
                root = excluir(root, value);
            }
        }
        else if (!strcmp(option, "buscar")) {
            scanf("%d", &value);
            if (buscar(root, value)) {
                printf("pertence\n");
            }
            else {
                printf("nao pertence\n");
            }
        }
        else if (!strcmp(option, "minimo")) {
            if (root) {
                printf("%d\n", minimo(root));
            }
            else {
                printf("vazia\n");
            }
        }
        else if (!strcmp(option, "maximo")) {
            if (root) {
                printf("%d\n", maximo(root));
            }
            else {
                printf("vazia\n");
            }
        }
        else if (!strcmp(option, "pos-ordem")) {
            if (root) {
                posOrdem(root);
            }
            else {
                printf("vazia");
            }

            printf("\n");
        }
        else if (!strcmp(option, "em-ordem")) {
            if (root) {
                emOrdem(root);
            }
            else {
                printf("vazia");
            }

            printf("\n");
        }
        else if (!strcmp(option, "pre-ordem")) {
            if (root) {
                preOrdem(root);
            }
            else {
                printf("vazia");
            }

            printf("\n");
        }
        else if (!strcmp(option, "largura")) {
            if (root) {
                printBreadth(root);
            }
            else {
                printf("vazia");
            }

            printf("\n");
        }
        else if (!strcmp(option, "terminar")) {
            terminar(root);
            return 0;
        }
    }
}

node_t* inserir(node_t *node, int value) {
    if (!node) {
        node = malloc(sizeof(node_t));
        if (!node) {
            printf("memoria insuficiente\n");
            return NULL;
        }
        node->value = value;
        node->left = node->right = NULL;
    }
    else if (value < node->value) {
        node->left = inserir(node->left, value);
    }
    else {
        node->right = inserir(node->right, value);
    }

    return node;
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
    else {
        return buscar(node->right, value);
    }

}

node_t* excluir(node_t *node, int value) {
    if (!node) {
        return NULL;
    }
    else if (value < node->value) {
        node->left = excluir(node->left, value);
    }
    else if (value > node->value) {
        node->right = excluir(node->right, value);
    }
    else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            node = NULL;
        }
        else if (node->left == NULL) {
            node_t *aux = node;
            node = node->right;
            free(aux);
        }
        else if (node->right == NULL) {
            node_t *aux = node;
            node = node->left;
            free(aux);
        }
        else {
            node_t *aux = node->left;
            while (aux->right != NULL) {
                aux = aux->right;
            }
            node->value = aux->value;
            aux->value = value;
            node->left = excluir(node->left, value);
        }
    }

    return node;
}

int minimo(node_t *node) {
    if (!node->left) {
        return node->value;
    }
    else {
        return minimo(node->left);
    }
}

int maximo(node_t *node) {
    if (!node->right) {
        return node->value;
    }
    else {
        return maximo(node->right);
    }
}

int terminar(node_t *node) {
    if (!node) {
        return 0;
    }
    if (node->left) {
        terminar(node->left);
    }
    if (node->right){
        terminar(node->right);
    }

    free(node);
    return 0;
}

int preOrdem(node_t *node) {
    if (node == NULL) {
    }
    else {
        printf("%d ", node->value);
        preOrdem(node->left);
        preOrdem(node->right);
    }

    return 0;
}

int emOrdem(node_t *node) {
    if (node == NULL) {
    }
    else {
        emOrdem(node->left);
        printf("%d ", node->value);
        emOrdem(node->right);
    }

    return 0;
}

int posOrdem(node_t *node) {
    if (node == NULL) {
    }
    else {
        posOrdem(node->left);
        posOrdem(node->right);
        printf("%d ", node->value);
    }

    return 0;
}

int printBreadth(node_t *root) {
    if (root == NULL) {
        return 0;
    }
    int nodesCurrentLevel = 1, nodesNextLevel = 0, k;
    node_t **queue = malloc(sizeof(node_t*));
    queue[0] = root;
    while (queue[0]) {
        node_t *currentNode = queue[0];

        if (currentNode) {
            printf("%d ", currentNode->value);
            if (currentNode->left) {
                queue = realloc(queue, sizeof(node_t*) * (nodesCurrentLevel + (++nodesNextLevel)));
                queue[nodesCurrentLevel + nodesNextLevel - 1] = currentNode->left;
            }
            if (currentNode->right) {
                queue = realloc(queue, sizeof(node_t*) * (nodesCurrentLevel + (++nodesNextLevel)));
                queue[nodesCurrentLevel + nodesNextLevel - 1] = currentNode->right;
            }
        }

        node_t **new_queue = malloc(sizeof(node_t*)*(--(nodesCurrentLevel) + nodesNextLevel));
        for (k = 0; k < nodesCurrentLevel + nodesNextLevel; k++) {
            new_queue[k] = queue[k+1];
        }

        free(queue);
        queue = new_queue;

        if (nodesNextLevel + nodesCurrentLevel == 0) {
            free(queue);
            return 0;
        }
        else if (nodesCurrentLevel == 0) {
            nodesCurrentLevel = nodesNextLevel;
            nodesNextLevel = 0;
        }
    }

    return 0;
}
