#include "bst.h"
#include <stdlib.h>

void destroy(t_btree *root) {
    if (root->left != NULL) {
        destroy(root->left);
    }

    if (root->right != NULL) {
        destroy(root->right);
    }

    free(root);
}

t_btree *bstree_create_node(int item) {
    t_btree *res = (t_btree *) calloc(1, sizeof(t_btree));

    if (res != NULL) {
        res->item = item;
        res->right = NULL;
        res->left = NULL;
    }

    return res;
}

void bstree_insert(t_btree *root, int item, int(*cmpf) (int, int)) {
    while ((root->left != NULL && cmpf(root->item, item) == 1) ||
           (root->right != NULL && cmpf(root->item, item) == 0)) {
        if (root->left != NULL && cmpf(root->item, item) == 1) {
            root = root->left;
        } else if (root->right != NULL && cmpf(root->item, item) == 0) {
            root = root->right;
        }
    }

    if (cmpf(root->item, item) == 1) {
        root->left = bstree_create_node(item);
    } else if (cmpf(root->item, item) == 0) {
        root->right = bstree_create_node(item);
    }
}

void bstree_apply_infix(t_btree *root, void(*applyf) (int)) {
    if (root->left != NULL) {
        bstree_apply_infix(root->left, applyf);
    }

    applyf(root->item);

    if (root->right != NULL) {
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree *root, void(*applyf) (int)) {
    applyf(root->item);

    if (root->left != NULL) {
        bstree_apply_prefix(root->left, applyf);
    }

    if (root->right != NULL) {
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree *root, void(*applyf) (int)) {
    if (root->right != NULL) {
        bstree_apply_postfix(root->right, applyf);
    }

    applyf(root->item);

    if (root->left != NULL) {
        bstree_apply_postfix(root->left, applyf);
    }
}
