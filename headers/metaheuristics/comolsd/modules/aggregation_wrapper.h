#ifndef AGGREGATION_WRAPPER_H
#define AGGREGATION_WRAPPER_H

#include <functional>
#include <utility>
#include "calculate_ws.h"
#include "calculate_ipbi.h"
#include "normalize_objectives.h"

// Para funções que recebem 2 argumentos (ex.: calculate_ws)
std::function<double(const std::pair<double, double>&,
                     const std::pair<double, double>&,
                     const std::pair<double, double>&)>
make_aggregation_function(
    double (*aggregation)(const std::pair<double, double>&,
                          const std::pair<double, double>&),
    const std::pair<double, double>& global_ideal_point,
    const std::pair<double, double>& global_nadir_point);

// Para funções que recebem 3 argumentos (ex.: calculate_ipbi)
std::function<double(const std::pair<double, double>&,
                     const std::pair<double, double>&,
                     const std::pair<double, double>&)>
make_aggregation_function(
    double (*aggregation)(const std::pair<double, double>&,
                          const std::pair<double, double>&,
                          const std::pair<double, double>&),
    const std::pair<double, double>& global_ideal_point,
    const std::pair<double, double>& global_nadir_point);

#endif
