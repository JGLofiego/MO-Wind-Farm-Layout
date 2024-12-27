#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "generate_rSolution.h"
#include "../../adaptive_grid/BoundedParetoSet.cpp"
using namespace std;

extern BoundedParetoSet * pareto;
extern FILE * f;
extern int countRevalue;

vector<Solution> create_initial_population(int size_population);

#endif 
