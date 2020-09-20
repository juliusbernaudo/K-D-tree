#ifndef TREE2H
#define TREE2H
#define MAX_BUFFER 513
#define FIELD_LEN 129
#define MAX_TITLES 11
#define DEPTH 2
#define INPUT 3

typedef struct data {
    char* year;
    char* block;
    char* property;
    char* base;
    char* city;
    char* name;
    char* code;
    char* desc;
    double xCoord;
    char* xCordStr;
    double yCoord;
    char* yCordStr;
    char* location;
    
} data_t;

typedef struct node {
    data_t data;
    struct node* right;
    struct node* left;
    struct node* duplicate;
} node_t;

typedef struct list {
    node_t* head;
    node_t* foot;
} list_t;

list_t *insert_in_tree(list_t *list, data_t *data);
void search_data(list_t *list, char *key, FILE *output, char titles[MAX_TITLES][FIELD_LEN]);
void insert_node(node_t *curr, node_t *new, int level);
void radius_search(double keys[INPUT], char* keycpy, node_t *node, int level, int *comparisons, int *matchFound, FILE *output, char titles[MAX_TITLES][FIELD_LEN]);

#endif
