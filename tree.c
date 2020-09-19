#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "tree.h"
#define MAX_BUFFER 513
#define MAX_OUTPUT 613
#define FIELD_LEN 129
#define MAX_TITLES 11
#define DEPTH 2
#define COUNT 10

void
free_data(data_t *data) {
    free(data->year);
    free(data->block);
    free(data->property);
    free(data->base);
    free(data->city);
    free(data->name);
    free(data->code);
    free(data->desc);
    free(data->xCordStr);
    free(data->yCordStr);
    free(data->location);
}

/* Stuff from listops.c */
/* =====================================================================
   Program (free_list) was written by Alistair Moffat, as an
   example for the book and modified by me, Julius Miguel Bernaudo
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
/*void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
        free_data(&(prev -> data));
		free(prev);
	}
	free(list);
} */

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

/* Simple function created to store the data into the data struct so 
that my code is not as messy */
void
insert_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]) {
    char* xptr;
    char* yptr;
    strcpy(data -> year, dataArray[0]);
    strcpy(data -> block ,dataArray[1]);
    strcpy(data -> property ,dataArray[2]);
    strcpy(data -> base ,dataArray[3]);
    strcpy(data -> city ,dataArray[4]);
    strcpy(data -> name ,dataArray[5]);
    strcpy(data -> code ,dataArray[6]);
    strcpy(data -> desc ,dataArray[7]);
    strcpy(data -> xCordStr ,dataArray[8]);
    data -> xCoord = strtod(dataArray[8], &xptr);
    data -> yCoord = strtod(dataArray[9], &yptr);
    strcpy(data -> yCordStr ,dataArray[9]);
    strcpy(data -> location ,dataArray[10]);
}

/* Same purpose as insert_data, however this is to intialise the data struct
and keep the code clean and simple to read */
void 
initialise_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]) {
    data -> year = (char *)malloc(strlen(dataArray[0])+2*sizeof(char));
    data -> block = (char *)malloc(strlen(dataArray[1])+2*sizeof(char));
    data -> property = (char *)malloc(strlen(dataArray[2])+2*sizeof(char));
    data -> base = (char *)malloc(strlen(dataArray[3])+2*sizeof(char));
    data -> city = (char *)malloc(strlen(dataArray[4])+2*sizeof(char));
    data -> name = (char *)malloc(strlen(dataArray[5])+2*sizeof(char));
    data -> code = (char *)malloc(strlen(dataArray[6])+2*sizeof(char));
    data -> desc = (char *)malloc(strlen(dataArray[7])+2*sizeof(char));
    data -> xCordStr = (char *)malloc(strlen(dataArray[8])+2*sizeof(char));
    data -> yCordStr = (char *)malloc(strlen(dataArray[9])+2*sizeof(char));
    data -> location = (char *)malloc(strlen(dataArray[10])+2*sizeof(char));
}

/* Scans through the list searching for any string matches with the key */
void
search_data(list_t *list, char *key, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    int cmpResult, matchFound = 1, count = 0;
    char* xptr;
    char* yptr;
    char* str;
    double keys[DEPTH];
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
    
   
}

/* Removing any double quotations from the data while maintaining
any quotations that are part of the string itself */
void
filter_quotations(char *array) {
    int i = 0, len = strlen(array), j;
    while(i<len) {
        if (array[i] == 34 && array[i+1] != 34) {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        }
        if (array[i] == 34 && array[i+1]) {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        }
        i++;
        len = strlen(array);
    }
}

/* Remove any newlines trailing at the end of the data */
void
filter_newline(char *array) {
    int i = 0, len = strlen(array), j;
    while(i<len) {
        if (array[i] == '\n' || array[i] == '\r') {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        } else {
            i++;
        }
        len = strlen(array);
    }
}

/* Generate an output string that is to be outputted to the text file
while keeping the code within other functions easier to understand */
void
output_string(data_t *data, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    char outputStr[MAX_OUTPUT];
    strcpy(outputStr, data -> name);
    strcat(outputStr, " --> ");
    strcat(outputStr, titles[0]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> year);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[1]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> block);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[2]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> property);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[3]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> base);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[4]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> city);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[6]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> code);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[7]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> desc);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[8]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> xCordStr);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[9]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> yCordStr);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[10]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> location);
    strcat(outputStr, " || ");
    strcat(outputStr, "\n");
    fputs(outputStr, output);
}

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

void
calculate_distance(node_t *key, node_t *node, node_t *closestPoint int level, double *closestDistance, int *comparisons) {
    if (node == NULL) {
        return;
    }
    *comparisons =+ 1
    double distance = sqrt(pow(node->data.xCoord - key->data.xCoord) + pow(node->data.yCoord - key->data.yCoord));
    double xDistance = fabs(node->data.xCoord - key->data.xCoord);
    double yDistance = fabs(node->data.yCoord - key->data.yCoord);
    
    if (distance < closestDistance) {
        *closestDistance = distance;
        *closestPoint = node;
    }
    if (level % DEPTH == 0) {
        if (node->data.xCoord > xDistance) {
            if (node->data.xCoord < key->data.xCoord) {
                calculate_distance(key, node->right, &closestPoint, level+1, &closestDistance); 
            } else {
                calculate_distance(key, node->left, &closestPoint, level+1, &closestDistance); 
            }
        } else {
            calculate_distance(key, node->right, &closestPoint, level+1, &closestDistance);
            calculate_distance(key, node->left, &closestPoint, level+1, &closestDistance);
        }
    } else {
        if (node->data.yCoord > yDistance) {
            if (node->data.yCoord < key->data.yCoord) {
                calculate_distance(key, node->right, &closestPoint, level+1, &closestDistance);
            } else {
                calculate_distance(key, node->left, &closestPoint, level+1, &closestDistance);
            }
        } else {
            calculate_distance(key, node->right, &closestPoint, level+1, &closestDistance);
            calculate_distance(key, node->left, &closestPoint, level+1, &closestDistance);
        }
    }
}

void 
print2DUtil(node_t *root, int space, FILE *output) {

    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space, output); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    
    printf("%s\n", root->data.location);
    fputs(root->data.location, output);
    fputs("\n", output);
  
    // Process left child 
    print2DUtil(root->left, space, output); 
} 
  
// Wrapper over print2DUtil() 
void 
print2D(node_t *root, FILE *output) { 
   // Pass initial space count as 0 
   print2DUtil(root, 0, output); 
} 