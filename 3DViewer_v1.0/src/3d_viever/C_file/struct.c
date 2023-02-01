#include "struct.h"

data_t init_struct() {
  return (data_t){0, 0, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0};
}

void malloc_struct(data_t *obj, int *error_target) {
  if (obj->count_of_facets > 0) {
    if (!(obj->facets =
              malloc(obj->count_of_facets * sizeof(unsigned long int)))) {
      *error_target = 2;
    }
  } else {
    *error_target = 2;
  }
  if (obj->count_of_vertexes > 0) {
    if (!*error_target) {
      if (!(obj->matrix = malloc(obj->count_of_vertexes * sizeof(double *)))) {
        *error_target = 2;
      } else {
        for (unsigned long int i = 0;
             i < obj->count_of_vertexes && !*error_target; i++) {
          if (!(obj->matrix[i] = malloc(3 * sizeof(double)))) {
            *error_target = 2;
          }
        }
      }
    }
    if (!*error_target) {
      if (!(obj->matrix_print =
                malloc(obj->count_of_vertexes * sizeof(double *)))) {
        *error_target = 2;
      } else {
        for (unsigned long i = 0; i < obj->count_of_vertexes && !*error_target;
             i++) {
          if (!(obj->matrix_print[i] = malloc(3 * sizeof(double)))) {
            *error_target = 2;
          }
        }
      }
    }
  } else {
    *error_target = 2;
  }
}

void free_struct(data_t *obj) {
  if (obj->facets && obj->count_of_facets > 0) {
    free(obj->facets);
  }
  if (obj->matrix && obj->count_of_vertexes > 0) {
    for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
      free(obj->matrix[i]);
    }
    free(obj->matrix);
  }
  if (obj->matrix_print && obj->count_of_vertexes > 0) {
    for (unsigned long i = 0; i < obj->count_of_vertexes; i++) {
      free(obj->matrix_print[i]);
    }
    free(obj->matrix_print);
  }
  *obj = init_struct();
}
