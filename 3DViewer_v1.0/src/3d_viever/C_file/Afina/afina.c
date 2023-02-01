#include "afina.h"

void rotation_by_ox(data_t *obj, int angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
    double temp_y = obj->matrix_print[i][1];
    double temp_z = obj->matrix_print[i][2];
    obj->matrix_print[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
    obj->matrix_print[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oy(data_t *obj, int angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int i = 0; i < obj->count_of_vertexes; i++) {
    double temp_y = obj->matrix_print[i][0];
    double temp_z = obj->matrix_print[i][2];
    obj->matrix_print[i][0] = cos(angle) * temp_y - sin(angle) * temp_z;
    obj->matrix_print[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void rotation_by_oz(data_t *obj, int angle_i) {
  double angle = (double)angle_i * (3.14f / 180.0f);
  for (unsigned long int  i = 0; i < obj->count_of_vertexes; i++) {
    double temp_y = obj->matrix_print[i][0];
    double temp_z = obj->matrix_print[i][1];
    obj->matrix_print[i][0] = cos(angle) * temp_y - sin(angle) * temp_z;
    obj->matrix_print[i][1] = sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void copy_state(data_t *obj) {
  for (unsigned long int  i = 0, j = 0; i < obj->count_of_vertexes; j > 2 ? i++, j = 0 : j++) {
    obj->matrix_print[i][j] = obj->matrix[i][j];
  }
}
