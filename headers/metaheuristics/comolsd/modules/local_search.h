#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <vector>
#include <functional>
#include "../../../global_modules/generate_initial_population/generate_rSolution.h"

void local_search(std::vector<Solution*>& population,
                  const std::vector<std::pair<double, double>>& weight_vectors,
                  const std::pair<double, double>& reference_point,
                  const std::vector<std::vector<int>>& neighborhood,
                  std::function<double(const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&)> aggregation_function);

#endif
