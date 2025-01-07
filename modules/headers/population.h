#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "generate_rSolution.h"
#include "../../adaptive_grid/BoundedParetoSet.cpp"
using namespace std;

extern BoundedParetoSet * pareto;
extern int countRevalue;
extern string instance;
extern string algorithm;
extern string root_folder;
extern int stop_criteria;

vector<Solution> create_initial_population(int size_population);

#endif 
