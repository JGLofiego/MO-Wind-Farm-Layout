#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "../generate_random_solution/generate_rSolution.h"
using namespace std;

vector<Solution> create_initial_population(int size_population, int num_turb, int upperBoundX, int upperBoundY);

#endif 
