#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left, *right;
    double left_p, right_p;
} node_t;

node_t *createTree(node_t *node, int c);
node_t *freeTree(node_t *node);
double countWeight(node_t *node);

int main(int argc, char const *argv[]) {
    node_t *root = NULL;

    char c = 0;

    while (scanf("%c", &c) != EOF) {
        root = createTree(root, c);

        printf("%.3lf\n", countWeight(root));
        
        freeTree(root);

        scanf("%c", &c);
    }

    return 0;
}

node_t *createTree(node_t *node, int c) {
    char symbol = 0;
    scanf("%c", &symbol);

    if (c == '(' && symbol == ')') {
        return NULL;
    }

    else {
        node = malloc(sizeof(node_t));

        node->left = createTree(node->left, symbol);
        if (node->left) {
            scanf("%lf:", &node->left_p);
        }
        // Value of the node
        scanf("%d", & node->value);

        // Next input after node's value
        scanf("%c", &symbol);
        if (symbol == ':') {
            scanf("%lf", &node->right_p);
            scanf("%c", &symbol);
        }

        node->right = createTree(node->right, symbol);
        scanf("%c", &symbol);
    }

    return node;
}

node_t *freeTree(node_t *node) {
    if (!node) {
    }
    else {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }

    return NULL;
}

double countWeight(node_t *node) {
    if (node->left == node->right) {
        return 0;
    }
    else if (!node->left) {
        return node->right_p + countWeight(node->right);
    }
    else if (!node->right) {
        return node->left_p + countWeight(node->left);;
    }
    else {
        double l_weight = countWeight(node->left) + node->left_p;
        double r_weight = countWeight(node->right) + node->right_p;

        if (l_weight >= r_weight) {
            return l_weight;
        }
        else {
            return r_weight;
        }
    }
}
