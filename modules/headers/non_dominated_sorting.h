#ifndef NON_DOMINATED_SORTING_H
#define NON_DOMINATED_SORTING_H

#include "generate_rSolution.h"
#include <vector>
using namespace std;

vector<vector<pair<Solution, int>>> non_dominated_sorting(vector<Solution>& population_rt);

#endif 
