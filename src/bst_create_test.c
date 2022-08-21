#include <stdio.h>
#include "bst.h"

void test_tree(int item) {
    t_btree *new = bstree_create_node(item);
    if (new != NULL) {
        printf("INPUT:\n%d\n", item);
        printf("OUTPUT:\n");
        printf("%d %p %p\n", new->item, new->left, new->right);
        if (new->item == item && new->left == NULL && new->right == NULL) {
            printf("SUCCESS\n");
        } else {
            printf("FAIL\n");
        }
        destroy(new);
    } else {
        printf("Alloc error!\n");
    }
}

int main() {
    test_tree(3);
    test_tree(10);
    test_tree(0);
    return 0;
}
