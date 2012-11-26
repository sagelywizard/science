-module(science).
-export([arithmetic_mean/1, variance/1, min/1, max/1, kurtosis/1, median/1, quantile/2, skewness/1]).
-on_load(init/0).

init() ->
    ok = erlang:load_nif("./science", 1).

arithmetic_mean(_X) ->
    exit(nif_library_not_loaded).

variance(_X) ->
    exit(nif_library_not_loaded).

min(_X) ->
    exit(nif_library_not_loaded).

max(_X) ->
    exit(nif_library_not_loaded).

kurtosis(_X) ->
    exit(nif_library_not_loaded).

median(_X) ->
    exit(nif_library_not_loaded).

quantile(_X, _Y) ->
    exit(nif_library_not_loaded).

skewness(_X) ->
    exit(nif_library_not_loaded).
