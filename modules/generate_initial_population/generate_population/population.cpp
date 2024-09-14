#include "../../headers/population.h"
#include "../../headers/generate_rSolution.h"
#include <iostream>
#include <time.h>
using namespace std;

vector<Solution> create_initial_population
  (
  int size_population,
  int num_turb,
  float& wind,
  float& power,
  float& thrust_coef,
  float& angle,
  vector<double> *&costs
  ) {

  vector<Solution> population;

  for (int i = 0; i < size_population; i++) {
    population.push_back(generate_solution(num_turb, wind, power, thrust_coef, angle, costs));
  }

  return population;
}