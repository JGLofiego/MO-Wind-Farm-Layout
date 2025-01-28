#ifndef NSGA2_V2_H
#define NSGA2_V2_H

#include "../../global_modules/generate_initial_population/generate_rSolution.h"
#include <list>
#include <fstream> 

void updatePopulation(vector<Solution*>& population);

std::list<Solution*> nsga2_v2(std::list<Solution>& pop);

extern ofstream infoRunNSGA2;

#endif 