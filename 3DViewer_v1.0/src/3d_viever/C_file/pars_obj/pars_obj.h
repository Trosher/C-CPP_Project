#include "../struct.h"

int pars_control(char const *file_name, data_t *obj);
int pars_obj(FILE *file, data_t *obj);
void first_run_file(FILE *file, data_t *obj);
int vertexes_check(char *buffer);
int facets_check(char *buffer);
unsigned long int facets_caunt_num(char *buffer);
void second_run_file(FILE *file, data_t *obj);
void vertexes_pars(char *buffer, data_t *obj, long unsigned int *index_v);
void facets_pars(char *buffer, data_t *obj, long unsigned int *index_f);
void normalization(data_t *obj);
void normalization_vector(data_t *obj, int index, double min, double max);
