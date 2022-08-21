#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#define DOORS_COUNT 3

struct door {
    int id;
    int status;
};

struct node {
    struct door door;
    struct node *next;
};

void initialize_doors(struct door* doors);
struct node* init(const struct door* door);
struct node* add_door(struct node* elem, const struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);

#endif  // SRC_LIST_H_
