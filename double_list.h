#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include "erl_nif.h"

typedef struct double_list {
    unsigned length;
    double * list;
} double_list;

double_list alloc_double_list(ErlNifEnv * env, ERL_NIF_TERM list);
void free_double_list(double_list dl);
int populate_double_list(ErlNifEnv * env, ERL_NIF_TERM list, double_list dl);

#endif
