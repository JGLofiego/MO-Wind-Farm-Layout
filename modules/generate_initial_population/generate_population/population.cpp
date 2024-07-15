#include "population.h"
#include "../generate_random_solution/generate_rSolution.h"
#include <iostream>
using namespace std;

vector<Solution> create_initial_population(int size_population, int num_turb, int upperBoundX, int upperBoundY) {
  vector<Solution> population;

  for (int i = 0; i < size_population; i++) {
    population.push_back(generate_solution(num_turb, upperBoundX, upperBoundY));
  }

  return population;
}