#ifndef SCIENCE_H
#define SCIENCE_H

#include "erl_nif.h"
#include "gsl/gsl_statistics.h"
#include "double_list.h"

void gsl_sort(double * data, size_t stride, size_t n);

#endif
