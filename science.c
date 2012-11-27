#include "science.h"

#define ARG_ERROR_IF_DL_IS_NULL(l) if (l.list == NULL) { return enif_make_badarg(env); }

static ERL_NIF_TERM variance(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_variance(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM arithmetic_mean(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_mean(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM max(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_max(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM min(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_min(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM kurtosis(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_kurtosis(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM median(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_NIF_TERM final;
    double_list dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    gsl_sort(dl.list, 1, dl.length);
    final = enif_make_double(env, gsl_stats_median_from_sorted_data(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM skewness(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double_list dl = alloc_double_list(env, argv[0]);
    ERL_NIF_TERM final = enif_make_double(env, gsl_stats_skew(dl.list, 1, dl.length));
    free_double_list(dl);
    return final;
}

static ERL_NIF_TERM quantile(ErlNifEnv * env, int argc, const ERL_NIF_TERM argv[]) {
    double quantile;
    double_list dl;
    ERL_NIF_TERM final;
    if (!enif_get_double(env, argv[1], &quantile)) {
        return enif_make_badarg(env);
    }
    if (quantile > 1 || quantile < 0) {
        return enif_make_badarg(env);
    }

    dl = alloc_double_list(env, argv[0]);
    ARG_ERROR_IF_DL_IS_NULL(dl);
    gsl_sort(dl.list, 1, dl.length);
    final = enif_make_double(env, gsl_stats_quantile_from_sorted_data(dl.list, 1, dl.length, quantile));
    free_double_list(dl);
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

ERL_NIF_INIT(science, funcs, NULL, &reload, &upgrade, NULL)
