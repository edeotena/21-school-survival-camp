#include <stdlib.h>
#include <time.h>
#include "list.h"

#define MAX_ID_SEED 10000

void destroy(struct node* root) {
    while (root != NULL) {
        struct node *next = root->next;
        free(root);
        root = next;
    }
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (elem == root) {
        root = elem->next;
        free(elem);
    } else if (elem != NULL) {
        struct node *temp = root;
        while (temp != NULL && temp->next != elem) {
            temp = temp->next;
        }

        if (temp != NULL && temp->next == elem) {
            temp->next = elem->next;
            free(elem);
        }
    }

    return root;
}

struct node* find_door(int door_id, struct node* root) {
    struct node *res = NULL;
    int code = 0;

    while (root != NULL && code == 0) {
        if (root->door.id == door_id) {
            res = root;
            code = 1;
        }
        root = root->next;
    }

    return res;
}

struct node* add_door(struct node* elem, const struct door* door) {
    struct node* new = NULL;
    if (elem != NULL) {
        struct node *next = elem->next;
        new = (struct node *) calloc(1, sizeof(struct node));

        if (new != NULL) {
            new->door = *door;
            elem->next = new;
            new->next = next;
        }
    }

    return new;
}

struct node* init(const struct door* door) {
    struct node *res = NULL;

    if (door != NULL) {
        res = (struct node *) calloc(1, sizeof(struct node));
        res->door = door[0];
    }

    return res;
}

void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}
