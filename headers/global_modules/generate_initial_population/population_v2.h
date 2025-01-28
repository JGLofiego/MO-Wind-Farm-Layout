#ifndef POPULATION_V2_H
#define POPULATION_V2_H

#include <list>
#include <string>
#include "generate_rSolution.h"
#include "../../adaptative_grid/BoundedParetoSet.h"

extern BoundedParetoSet * pareto;
extern int countRevalue;
extern std::string instance;
extern std::string algorithm;
extern std::string root_folder;
extern int stop_criteria;

std::list<Solution> create_initial_population_v2(int size_population);

#endif
