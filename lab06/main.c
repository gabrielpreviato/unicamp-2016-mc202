#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char value;
    struct node *left, *right;
} node_t;

node_t* constructTree(node_t *node, int size, int *size_pre, char **pre_order, char *in_order,
    int j, int j_b, int root);

int main() {
    int j = 0;
    char c, tree = 0;
    char *pre_order_tree = NULL, *in_order_tree = NULL;
    int pre_order_size = 0, in_order_size = 0;

    node_t *tree_root;

    // Gets the tree elements and stores it to an array, then do the reconstruction
    // and then gets another tree
    while (scanf("%c", &c) != EOF) {
        // In case c is a space, than change the tree we are adding the values
        if (c == ' '){
            tree = 1;
            continue;
        }
        else if (c == '\n') {
            if (in_order_size == pre_order_size) {
                constructTree(tree_root, in_order_size, &pre_order_size, &pre_order_tree, in_order_tree,
                j, in_order_size + 1, 1);
                //printTree();
                //destructTree();
            }
            else {
                printf("ERROR: Different sizes\n");
            }
        }

        // We have 2 trees, pre_order (tree = 0) and in_oder (tree = 1)
        if (tree == 0) {
            pre_order_tree = realloc(pre_order_tree, pre_order_size + 1);
            pre_order_tree[pre_order_size++] = c;
        }
        else {
            in_order_tree = realloc(in_order_tree, in_order_size + 1);
            in_order_tree[in_order_size++] = c;
        }

    }
}

node_t* constructTree(node_t *node, int size, int *size_pre, char **pre_order, char *in_order,
    int j, int j_b, int root) {
    int l, k;

    if (root == 1) {
        for (l = 0; l < size; l++) {
            if ((*pre_order)[0] == in_order[l]) {
                j = l;
                break;
            }
        }

        node = malloc(sizeof(node_t));
        node->value = *pre_order[0];

        char *new_pre = malloc(--(*size_pre));
        for (k = 0; k < *size_pre; k++) {
            new_pre[k] = (*pre_order)[k+1];
        }

        free(*pre_order);
        *pre_order = new_pre;

        node->left = constructTree(node->left, size, size_pre, pre_order, in_order, j, j_b, 0);
        node->right = constructTree(node->left, size, size_pre, pre_order, in_order, j, j_b, 0);
        return node;
    }

    for(l = 0; l < j; l++) {
        // In case
        if (in_order[l] == *pre_order[0]) {
            node = malloc(sizeof(node_t));
            node->value = *pre_order[0];

            char *new_pre = malloc(--(*size_pre));
            for (k = 0; k < *size_pre; k++) {
                new_pre[k] = (*pre_order)[k+1];
            }

            free(*pre_order);
            *pre_order = new_pre;

            node->left = constructTree(node->left, size, size_pre, pre_order, in_order, l, j, 0);
            node->right = constructTree(node->right, size, size_pre, pre_order, in_order, l, j, 0);
            return node;
        }
    }

    for (l = j + 1; j < j_b; j++) {
        if (in_order[l] == (*pre_order)[0]) {
            node = malloc(sizeof(node_t));
            node->value = *pre_order[0];

            char *new_pre = malloc(--(*size_pre));
            for (k = 0; k < *size_pre; k++) {
                new_pre[k] = (*pre_order)[k+1];
            }

            free(*pre_order);
            *pre_order = new_pre;

            node->left = constructTree(node->left, size, size_pre, pre_order, in_order, l, j, 0);
            node->right = constructTree(node->right, size, size_pre, pre_order, in_order, l, j_b, 0);
            return node;
        }
    }

    return NULL;
}
