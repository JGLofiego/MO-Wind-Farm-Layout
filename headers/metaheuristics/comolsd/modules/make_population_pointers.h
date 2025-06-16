#ifndef MAKE_POPULATION_POINTERS_H
#define MAKE_POPULATION_POINTERS_H

#include <vector>
#include "solution.h"

// Converts a vector<Solution> to vector<Solution*>
std::vector<Solution*> make_population_pointers(std::vector<Solution>& population);

#endif
