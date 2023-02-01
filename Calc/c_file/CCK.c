#include "smartcalc.h"

long double mes_p(long double data_k, long double sum_k, long double proc_k) {
    long double aga1 = proc_k / 12 / 100, aga2 = 0;
    aga2 = (aga1 * pow((1 + aga1), data_k) / (pow(1+aga1, data_k) - 1));
    return aga2 * sum_k;
}

void res_CCKDA(long double data_k, long double sum_k, long double proc_k, \
                    long double *mes_plata, long double *proc, long double *p_sim_d) {
    *mes_plata = mes_p(data_k, sum_k, proc_k);
    *p_sim_d = *mes_plata * data_k;
    *proc = *p_sim_d - sum_k;
}

void res_CCKDD(long double data_k, long double sum_k, long double proc_k, \
                    long double *mes_plata_min, long double *mes_plata_max, long double *proc, \
                    long double *p_sim_d) {
    *p_sim_d = 0;
    *proc = sum_k;
    proc_k = proc_k / 100;
    long double mes_plata = sum_k / data_k;
    *mes_plata_max = mes_plata+(sum_k*proc_k*30.0/365.0);
    for (int i = 0; i < data_k && sum_k >= 0; i++) {
        *p_sim_d += mes_plata+(sum_k*proc_k*30.0/365.0);
        sum_k -= mes_plata;
        if (i == data_k - 1) {
            *mes_plata_min = mes_plata+(sum_k*proc_k*30.0/365.0);
        }
    }
    *proc = *p_sim_d - *proc;
}
