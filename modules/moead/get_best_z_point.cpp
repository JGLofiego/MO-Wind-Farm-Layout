#include <vector>
#include <limits>
#include <iostream>
#include <utility>
#include "../headers/get_best_z_point.h"

using namespace std;

pair<double, double> get_best_z_point(vector<Solution>& population) {
  double best_f_i = numeric_limits<double>::infinity(); 
  double best_f_j = numeric_limits<double>::infinity();

  for (auto& individual : population) {
    // For minimization: find the smallest values ​​of f_i(x) and f_j(x)
    if (individual.fitness.first < best_f_i) {
      best_f_i = individual.fitness.first;
    }
    if (individual.fitness.second < best_f_j) {
      best_f_j = individual.fitness.second;
    }
  }

  return make_pair(best_f_i, best_f_j);
}