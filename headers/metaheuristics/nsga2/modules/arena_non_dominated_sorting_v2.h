#ifndef ARENA_NON_DOMINATED_SORTING_V2_H
#define ARENA_NON_DOMINATED_SORTING_V2_H

#include "../../../global_modules/generate_initial_population/generate_rSolution.h"
#include "../../../globals.h"

#include <list>
using namespace std;

void arena_non_dominated_sorting_v2(std::list<Solution *> &population, std::list<Solution *> F[SIZE_OF_POPULATION * 5]);

#endif 