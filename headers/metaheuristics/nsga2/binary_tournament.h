#ifndef BINARY_TOURNAMENT_H
#define BINARY_TOURNAMENT_H

#include "../../global_modules/generate_initial_population/generate_rSolution.h"
#include <utility>
using namespace std;

pair<Solution, Solution> binary_tournament(vector<Solution>& population);

#endif 