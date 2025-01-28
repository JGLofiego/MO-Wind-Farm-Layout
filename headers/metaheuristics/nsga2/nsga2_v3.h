#ifndef NSGA2_V3_H
#define NSGA2_V3_H

#include "../../global_modules/generate_initial_population/generate_rSolution.h"
#include <vector>
#include <fstream> 

void updatePopulation(vector<Solution*>& population);

std::vector<Solution*> nsga2_v3(std::vector<Solution>& pop);

extern ofstream infoRunNSGA2;

#endif 