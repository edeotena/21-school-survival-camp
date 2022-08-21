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

void test_insert(t_btree* head, int item, int(*cmpf) (int, int)) {
    printf("Tree before:\n");
    bstree_apply_infix(head, print);
    printf("Add elem: %d\n", item);
    bstree_insert(head, item, cmpf);
    printf("Tree after:\n");
    bstree_apply_infix(head, print);
    printf("\n");
}

int main() {
    t_btree *test = bstree_create_node(30);

    test_insert(test, 111, cmp);
    test_insert(test, 20, cmp);
    test_insert(test, 55, cmp);
    test_insert(test, 18, cmp);
    test_insert(test, 1, cmp);
    test_insert(test, 2, cmp);

    destroy(test);

    return 0;
}
