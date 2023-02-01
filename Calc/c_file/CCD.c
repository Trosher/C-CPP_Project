#include "smartcalc.h"

void res_CCD(long double data_v, long double sum_v, long double proc_v, \
            long double *proc_res, long double *sum_res) {
    *sum_res = sum_v;
    for (int i = 0; i < data_v && sum_v >= 0; i++) {
        *sum_res = *sum_res + (*sum_res / 100 * proc_v / 12);
    }
    *proc_res = *sum_res - sum_v;
}
