#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "tree2.h"
#include "format.h"
#define MAX_BUFFER 513
#define MAX_OUTPUT 613
#define FIELD_LEN 129
#define MAX_TITLES 11
#define DEPTH 2
#define INPUT 3
#define COUNT 10

/* Inserts the data into the tree and begins the recursion functionality of the insert_node */
list_t
*insert_in_tree(list_t *list, data_t *value) {
    int level = 0;
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = *value;
	new->right = NULL;
    new->left = NULL;
    new->duplicate = NULL;
    
	if (list->head==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
        insert_node(list->head, new, level);
	}
	return list;
}

/* Scans through the tree tracking which is the closest point to the query */
void
search_data(list_t *list, char *key, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    int count = 0, comparisons = 0, level = 0, matchFound = 0;
    char* xptr;
    char* str;
    char* keycpy;
    keycpy = (char *)malloc(strlen(key)+2*sizeof(char));
    strcpy(keycpy, key);
    
    double keys[INPUT];
    str = strtok(key, " ");
    while (str) {
        keys[count] = strtod(str, &xptr);
        str = strtok(NULL, " ");
        count++;
    }
    
    node_t *curr;
    curr = (node_t*)malloc(sizeof(*curr));
    assert(curr!=NULL);
    curr = list -> head;

    radius_search(keys, keycpy, curr, level, &comparisons, &matchFound, output, titles);
    
    if (matchFound == 0) {
        fputs(keycpy, output);
        fputs(" -->", output);
        fputs("NOTFOUND\n", output);
    }
    printf("%s -->%d\n", keycpy, comparisons);
    free(keycpy);
}

/* A recursive function that will traverse the list and insert the data node */
void
insert_node(node_t *curr, node_t *new, int level) {
    if ((new->data.xCoord == curr->data.xCoord) && (new->data.yCoord == curr->data.yCoord)) {
        if (curr->duplicate == NULL) {
            curr->duplicate = new;
            return;
        } else {
            insert_node(curr->duplicate, new, level + 1);
        }
    } else {
    // Checking if its on the x or y plane
        if (level % DEPTH == 0) {
            if (new->data.xCoord < curr->data.xCoord) {
                if (curr->left == NULL) {
                    curr->left = new;
                    return;
                } else {
                    insert_node(curr->left, new, level + 1);
                }
            } else {
                if (curr->right == NULL) {
                    curr->right = new;
                    return;
                } else {
                    insert_node(curr->right, new, level + 1);
                }
            }
        } else {
            if (new->data.yCoord < curr->data.yCoord) {
                if (curr->left == NULL) {
                    curr->left = new;
                    return;
                } else {
                    insert_node(curr->left, new, level + 1);
                }
            } else {
                if (curr->right == NULL) {
                    curr->right = new;
                    return;
                } else {
                    insert_node(curr->right, new, level + 1);
                }
            }
        }
    }
}

/* calculates the distance of each node it visits and traverses the tree to find the closest point */
void
radius_search(double keys[INPUT], char* keycpy, node_t *node, int level, int *comparisons, 
              int *matchFound, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    node_t *curr;
    curr = (node_t*)malloc(sizeof(*curr));
    assert(curr!=NULL);
    
    if (node == NULL) {
        return;
    }
    double distance = sqrt(pow(node->data.xCoord - keys[0], 2) + pow(node->data.yCoord - keys[1], 2));
    //double xDistance = fabs(node->data.xCoord - keys[0]);
    //double yDistance = fabs(node->data.yCoord - keys[1]);
    
    
    if (distance < keys[2]) {
        *curr = *node;
        while (curr) {
            output_string(&(curr -> data), output, titles, keycpy);
            curr = curr -> duplicate;
        }
        *matchFound = 1;
        radius_search(keys, keycpy, node->right, level+1, comparisons, matchFound, output, titles);
        radius_search(keys, keycpy, node->left, level+1, comparisons, matchFound, output, titles);
    } else {
        if (level % DEPTH == 0) {
            if (node->data.xCoord < keys[0]) {
                radius_search(keys, keycpy, node->right, level+1, comparisons, matchFound, output, titles);
            } else {
                radius_search(keys, keycpy, node->left, level+1, comparisons, matchFound, output, titles); 
            }
        } else {
            if (node->data.yCoord < keys[1]) {
                radius_search(keys, keycpy, node->right, level+1, comparisons, matchFound, output, titles);
            } else {
                radius_search(keys, keycpy, node->left, level+1, comparisons, matchFound, output, titles);
            }
        }
    }
    *comparisons = *comparisons + 1;
    if (curr != NULL) {
        free(curr);
    }
}
