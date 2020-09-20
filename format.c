#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "tree.h"
#include "format.h"
#define MAX_BUFFER 513
#define MAX_OUTPUT 613
#define FIELD_LEN 129
#define MAX_TITLES 11
#define DEPTH 2
#define COUNT 10

/* Frees the data node */
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

/* Free's each node within the tree */
void
free_list(node_t *node) {
    if (node != NULL) {
        free_list(node->duplicate);
        free_list(node->left);
        free_list(node->right);
        free_data(&(node -> data));
        free(node);
    }
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
output_string(data_t *data, FILE *output, char titles[MAX_TITLES][FIELD_LEN], char *key) {
    char outputStr[MAX_OUTPUT];
    strcpy(outputStr, key);
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