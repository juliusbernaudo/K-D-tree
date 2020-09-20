#ifndef FORMATH
#define FORMATH
#define MAX_BUFFER 513
#define FIELD_LEN 129
#define MAX_TITLES 11
#define DEPTH 2

void free_data(data_t *data);
void free_list(node_t *node);
void insert_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]);
void initialise_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]);
void filter_newline(char *array);
void filter_quotations(char *array);
void output_string(data_t *data, FILE *output, char titles[MAX_TITLES][FIELD_LEN], char *key);

#endif