#ifndef ARENA_NON_DOMINATED_SORTING_V3_H
#define ARENA_NON_DOMINATED_SORTING_V3_H

#include "../../../global_modules/generate_initial_population/generate_rSolution.h"
#include "../../../globals.h"

#include <vector>

void arena_non_dominated_sorting_v3(std::vector<Solution*> &population, std::vector<Solution *> F[SIZE_OF_POPULATION * 5]);

#endif 