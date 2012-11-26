#include "science.h"

#define SET_DOUBLE_LIST \
    ERL_NIF_TERM list = argv[0]; \
    unsigned len; \
    if (!enif_get_list_length(env, list, &len)) { \
        return enif_make_badarg(env); \
    } \
    double * double_list = enif_alloc(len * sizeof(double)); \
    if (double_list == NULL) { \
        return enif_make_badarg(env); \
    } \
    if (!populate_double_list(env, list, double_list, len)) { \
        return enif_make_badarg(env); \
    }

// Takes an Erlang list, and a pointer to an array to overwrite of size
// sizeof(double)*len bytes.
int populate_double_list(ErlNifEnv * env, ERL_NIF_TERM list, double double_list[], size_t len) {
    ERL_NIF_TERM head, tail;
    double dbl;
    ErlNifSInt64 lng;
    int i;
    for (i=0; i<len; i++) {
        enif_get_list_cell(env, list, &head, &tail);
        if (enif_get_double(env, head, &dbl)) {
            double_list[i] = dbl;
        } else if (enif_get_int64(env, head, &lng)) {
            double_list[i] = (double)lng;
        } else {
            return 0;
        }
        list = tail;
    }
    return 1;
}

static ERL_NIF_TERM variance(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_variance(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM arithmetic_mean(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_variance(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM max(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_max(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM min(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_min(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM kurtosis(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_kurtosis(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM median(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    gsl_sort(double_list, 1, len);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_median_from_sorted_data(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM skewness(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_skew(double_list, 1, len));
    enif_free(double_list);
    return final;
}

static ERL_NIF_TERM quantile(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    SET_DOUBLE_LIST;
    double quantile;
    if (!enif_get_double(env, argv[1], &quantile)) {
        return enif_make_badarg(env);
    }
    if (quantile > 1 || quantile < 0) {
        return enif_make_badarg(env);
    }
    gsl_sort(double_list, 1, len);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_quantile_from_sorted_data(double_list, 1, len, quantile));
    enif_free(double_list);
    return final;
}

static ErlNifFunc funcs[] = {
    {"arithmetic_mean", 1, arithmetic_mean},
    {"variance", 1, variance},
    {"min", 1, min},
    {"max", 1, max},
    {"kurtosis", 1, kurtosis},
    {"median", 1, median},
    {"skewness", 1, skewness},
    {"quantile", 2, quantile},
};

int reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
    return 0;
}

int upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info) {
    return 0;
}

ERL_NIF_INIT(science, funcs, NULL, &reload, &upgrade, NULL);
