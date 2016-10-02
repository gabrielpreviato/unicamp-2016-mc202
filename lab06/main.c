#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value;
    struct node *left, *right;
} node_t;

node_t* constructTree(node_t *node, int size, int *size_pre, char **pre_order, char *in_order,
    int j, int j_b, int root);
int printTree(node_t *node);
int destructTree(node_t *node);

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
                tree_root = constructTree(tree_root, in_order_size, &pre_order_size, &pre_order_tree, in_order_tree,
                j, in_order_size + 1, 1);

                printTree(tree_root);
                printf("\n");

                destructTree(tree_root);
                if(pre_order_tree) {
                    free(pre_order_tree);
                    pre_order_tree = NULL;
                }
                if(in_order_tree) {
                    free(in_order_tree);
                    in_order_tree = NULL;
                }
                pre_order_size = 0;
                in_order_size = 0;

                tree = 0;
                continue;
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
        printf("%c\n", node->value);

        char *new_pre = malloc(--(*size_pre));
        for (k = 0; k < *size_pre; k++) {
            new_pre[k] = (*pre_order)[k+1];
        }

        free(*pre_order);
        *pre_order = new_pre;

        if (*size_pre == 0) {
            node->left = NULL;
            node->right = NULL;
        }
        else {
            node->left = constructTree(node->left, size, size_pre, pre_order, in_order, j, j_b, 0);
            if (*size_pre == 0) {
                node->right = NULL;
            }
            else {
                node->right = constructTree(node->left, size, size_pre, pre_order, in_order, j, j_b, 0);
            }
        }
        return node;
    }

    for(l = 0; l < j; l++) {
        // In case
        if (in_order[l] == *pre_order[0] && *size_pre != 0) {
            node = malloc(sizeof(node_t));
            node->value = *pre_order[0];
            printf("%c\n", node->value);

            char *new_pre = malloc(--(*size_pre));
            for (k = 0; k < *size_pre; k++) {
                new_pre[k] = (*pre_order)[k+1];
            }

            free(*pre_order);
            *pre_order = new_pre;

            if (*size_pre == 0) {
                node->left = NULL;
                node->right = NULL;
            }
            else {
                node->left = constructTree(node->left, size, size_pre, pre_order, in_order, l, j, 0);
                if (*size_pre == 0) {
                    node->right = NULL;
                }
                else {
                    node->right = constructTree(node->right, size, size_pre, pre_order, in_order, l, j, 0);
                }
            }
            return node;
        }
    }

    for (l = j + 1; l < j_b; l++) {
        if (in_order[l] == (*pre_order)[0] && *size_pre != 0) {
            node = malloc(sizeof(node_t));
            node->value = *pre_order[0];
            printf("%c\n", node->value);

            char *new_pre = malloc(--(*size_pre));
            for (k = 0; k < *size_pre; k++) {
                new_pre[k] = (*pre_order)[k+1];
            }

            free(*pre_order);
            *pre_order = new_pre;

            if (*size_pre == 0) {
                node->left = NULL;
                node->right = NULL;
            }
            else {
                node->left = constructTree(node->left, size, size_pre, pre_order, in_order, l, j, 0);
                if (*size_pre == 0) {
                    node->right = NULL;
                }
                else {
                    node->right = constructTree(node->right, size, size_pre, pre_order, in_order, l, j_b, 0);
                }
            }
            return node;
        }
    }

    return NULL;
}

int printTree(node_t *node) {
    if (node == NULL) {
    }
    else {
        printTree(node->left);
        printTree(node->right);
        printf("%c", node->value);
    }

    return 0;
}

int destructTree(node_t *node) {
    if (node == NULL) {
    }
    else {
        destructTree(node->left);
        destructTree(node->right);
        free(node);
        node = NULL;
    }

    return 0;
}
