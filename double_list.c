#include "science.h"

double_list alloc_double_list(ErlNifEnv * env, ERL_NIF_TERM list) {
    double_list dl;
    if (!enif_get_list_length(env, list, &dl.length)) {
        dl.list = NULL;
        return dl;
    }
    // Might be NULL if enif_alloc fails.
    dl.list = enif_alloc(dl.length * sizeof(double));
    if (dl.list == NULL) {
        dl.list = NULL;
        return dl;
    }
    if (!populate_double_list(env, list, dl)) {
        enif_free(dl.list);
        dl.list = NULL;
        return dl;
    }
    return dl;
}

void free_double_list(double_list dl) {
    enif_free(dl.list);
}

// Takes an Erlang list, and a pointer to an array to overwrite of size
// sizeof(double)*len bytes.
int populate_double_list(ErlNifEnv * env, ERL_NIF_TERM list, double_list dl) {
    ERL_NIF_TERM head, tail;
    double dbl;
    ErlNifSInt64 lng;
    for (unsigned i=0; i<dl.length; i++) {
        enif_get_list_cell(env, list, &head, &tail);
        if (enif_get_double(env, head, &dbl)) {
            dl.list[i] = dbl;
        } else if (enif_get_int64(env, head, &lng)) {
            dl.list[i] = (double)lng;
        } else {
            return 0;
        }
        list = tail;
    }
    return 1;
}
