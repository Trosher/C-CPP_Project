#ifndef C_FILE_MAIN_C_H_
#define C_FILE_MAIN_C_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct data {
  unsigned long int count_of_vertexes;
  unsigned long int count_of_facets;
  unsigned long int *facets;
  double **matrix;
  double **matrix_print;
  double max_x;
  double min_x;
  double max_y;
  double min_y;
  double max_z;
  double min_z;
  int rebro;
} data_t;

data_t init_struct();
void malloc_struct(data_t *obj, int *error_target);
void free_struct(data_t *obj);

#endif  // C_FILE_MAIN_C_H_
