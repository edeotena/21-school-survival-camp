#include <stdio.h>
#include "bst.h"

void print(int num) {
    printf("%d\n", num);
}

int digit_sum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int cmp(int a, int b) {
    int res = 0;
    if (digit_sum(a) > digit_sum(b)) {
        res = 1;
    }
    return res;
}

int main() {
    t_btree *test = bstree_create_node(30);

    bstree_insert(test, 111, cmp);
    bstree_insert(test, 20, cmp);
    bstree_insert(test, 55, cmp);
    bstree_insert(test, 2, cmp);
    bstree_insert(test, 18, cmp);
    bstree_insert(test, 1, cmp);

    printf("Infix output:\n");
    bstree_apply_infix(test, print);
    printf("Prefix output:\n");
    bstree_apply_prefix(test, print);
    printf("Postfix output:\n");
    bstree_apply_postfix(test, print);

    destroy(test);

    return 0;
}
