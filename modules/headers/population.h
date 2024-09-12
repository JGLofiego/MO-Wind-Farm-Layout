#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "generate_rSolution.h"
using namespace std;

vector<Solution> create_initial_population(
    int size_population,
    int num_turb,
    float& wind,
    float& power,
    float& thrust_coef,
    float& angle,
    vector<double> *&costs,
    vector<Foundation> *&foundations
    );

#endif 
