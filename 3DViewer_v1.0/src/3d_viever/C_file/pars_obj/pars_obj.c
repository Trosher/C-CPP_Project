#include "pars_obj.h"

int pars_control(char const *file_name, data_t *obj) {
  int error_target = 0;
  FILE *fp = NULL;
  if ((fp = fopen(file_name, "r")) == NULL) {
    error_target = 1;
  } else {
    error_target = pars_obj(fp, obj);
    fclose(fp);
    obj->rebro = obj->count_of_facets / 2;
  }
  return error_target;
}

int pars_obj(FILE *file, data_t *obj) {
  int error_target = 0;
  first_run_file(file, obj);
  error_target = !(obj->count_of_facets && obj->count_of_vertexes);
  if (!error_target) {
    malloc_struct(obj, &error_target);
    second_run_file(file, obj);
  }
  return error_target;
}

void second_run_file(FILE *file, data_t *obj) {
  rewind(file);
  long unsigned int index_v = 0, index_f = 0;
  char buffer[1000];
  while(fgets(buffer,1000,file)) {
    if (buffer[0] != 'v' && buffer[0] != 'f') {
      continue;
    }
    if (vertexes_check(buffer)) {
      vertexes_pars(buffer, obj, &index_v);
    }
    if (facets_check(buffer)) {
      facets_pars(buffer, obj, &index_f);
    }
  }
}

void vertexes_pars(char *buffer, data_t *obj, long unsigned int *index_v) {
  for (int i = 1, j = 0; buffer[i]; i++) {
    if (buffer[i - 1] == ' ' && ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '-') && j < 3) {
      double x = 0;
      x = atof(buffer + i);
      obj->matrix[*index_v][j] = x;
      if (!j) {
        obj->max_x = x > obj->max_x ? x : obj->max_x;
        obj->min_x = x < obj->min_x ? x : obj->min_x;
      } else if (j == 1) {
        obj->max_y = x > obj->max_y ? x : obj->max_y;
        obj->min_y = x < obj->min_y ? x : obj->min_y;
      } else if (j == 2) {
        obj->max_z = x > obj->max_z ? x : obj->max_z;
        obj->min_z = x < obj->min_z ? x : obj->min_z;
      }
      j++;
    }
  }
  *index_v += 1;
}

void facets_pars(char *buffer, data_t *obj, long unsigned int *index_f) {
  unsigned long int first_num = 0, target = 0;
  for (int i = 1; buffer[i]; i++) {
    if (buffer[i - 1] == ' ' && (buffer[i] >= '0' && buffer[i] <= '9')) {
      unsigned long temp = atoi(buffer + i) - 1;
      obj->facets[*index_f] = temp;
      *index_f += 1;
      if (!target) {
        first_num = obj->facets[*index_f - 1];
        target = 1;
      } else {
        obj->facets[*index_f] = obj->facets[*index_f - 1];
        *index_f += 1;
      }
    }
  }
  obj->facets[*index_f] = first_num;
  *index_f += 1;
}

void first_run_file(FILE *file, data_t *obj) {
  int count_of_facets = 0;
  int count_of_vertexes = 0;
  char buffer[1000];
  while(fgets(buffer,1000,file)) {
    if (buffer[0] != 'v' && buffer[0] != 'f')
      continue;
    count_of_vertexes += vertexes_check(buffer);
    if (facets_check(buffer)) {
      count_of_facets += facets_caunt_num(buffer);
    }
  }
  if (!count_of_facets || !count_of_vertexes) {
    free_struct(obj);
  } else {
    obj->count_of_facets = count_of_facets;
    obj->count_of_vertexes = count_of_vertexes;
  }
}

int vertexes_check(char *buffer) {
  return buffer[0] == 'v' && buffer[1] == ' ';
}

int facets_check(char *buffer) {
  return buffer[0] == 'f' && buffer[1] == ' ';
}

unsigned long int facets_caunt_num(char *buffer) {
  unsigned long int caunt = 0;
  for(unsigned long int i = 0; buffer[i]; i++) {
    if (buffer[i + 1]) {
      if (buffer[i] == ' ' && (buffer[i+1] >= '0' && buffer[i+1] <= '9'))
        caunt++;
    }
  }
  return caunt * 2;
}

void normalization_vector(data_t *obj, int index, double min, double max) {
    if (min < 0) {
      for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
          obj->matrix[i][index] += fabs(min);
      }
    } else if (min > 0) {
      for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
            obj->matrix[i][index] -= min;
      }
    }
    if (index == 0) {
        obj->max_x = max - min;
        obj->min_x = 0;
    } else if (index == 1) {
        obj->max_y = max - min;
        obj->min_y = 0;
    } else {
        obj->max_z = max - min;
        obj->min_z = 0;
    }
}

void normalization(data_t *obj) {
  double scale_normal = 1;
  normalization_vector(obj, 0, obj->min_x, obj->max_x);
  normalization_vector(obj, 1, obj->min_y, obj->max_y);
  normalization_vector(obj, 2, obj->min_z, obj->max_z);
  double x = obj->max_x / 2;
  double y = obj->max_y / 2;
  double z = obj->max_z / 2;
  for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
      obj->matrix[i][0] -= x;
      obj->matrix[i][1] -= y;
      obj->matrix[i][2] -= z;
  }
  obj->max_x -= x;
  obj->min_x -= x;
  obj->max_y -= y;
  obj->min_y -= y;
  obj->max_z -= z;
  obj->min_z -= z;

  double max = fabs(obj->max_x) > fabs(obj->min_x) ? fabs(obj->max_x) : fabs(obj->min_x);
  max = max < fabs(obj->max_y) ? fabs(obj->max_y) : max;
  max = max < fabs(obj->min_y) ? fabs(obj->min_y) : max;
  max = max < fabs(obj->max_z) ? fabs(obj->max_z) : max;
  max = max < fabs(obj->min_z) ? fabs(obj->min_z) : max;

  obj->max_x  *= scale_normal / max;
  obj->min_x  *= scale_normal / max;
  obj->max_y  *= scale_normal / max;
  obj->min_y  *= scale_normal / max;
  obj->max_z  *= scale_normal / max;
  obj->min_z  *= scale_normal / max;

  for (unsigned long i = 0, j = 0; i < obj->count_of_vertexes; obj->matrix[i][j++] *= scale_normal / max , j > 2 ? j = 0, i++ : 0) {
  }
}
