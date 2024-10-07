#include <vector>
#include <limits>
#include <iostream>
#include <utility>
#include "../headers/z_point_metafeatures.h"

using namespace std;

pair<double, double> get_z_point_metafeatures(vector<Solution>& population) {
  // Initialize with small values ​​for maximization
  double best_cost = -numeric_limits<double>::infinity(); 
  double best_power = -numeric_limits<double>::infinity();

  for (auto& individual : population) {
    // Finding the largest values ​​of cost and power (for maximization)
    if (individual.fitness.first > best_cost) {
      best_cost = individual.fitness.first;
    }
    if (individual.fitness.second > best_power) {
      best_power = individual.fitness.second;
    }
  }

  return make_pair(best_cost, best_power);
}
