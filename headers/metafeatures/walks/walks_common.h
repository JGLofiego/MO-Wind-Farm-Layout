#ifndef WALKS_COMMON_H
#define WALKS_COMMON_H

#include "../landscapeElement.h"
#include "../landscapeMetrics.h"

bool add_front_0(Solution &solution, vector<Solution> &front_0){
  for(int i = 0; i < front_0.size(); i++){
    if(dominates(front_0[i], solution)){
      return false;
    }
  }

  for(int i = 0; i < front_0.size(); i++){
    if(dominates(solution, front_0[i])){
      front_0.erase(front_0.begin() + i);
    }
  }

  front_0.push_back(solution);
  return true;
}

int number_pareto_front(LandscapeElement &landscape){
  vector<Solution> pareto_front;
  Solution solution_0 = landscape.neighborhod[0];

  for(int i = 0; i < landscape.neighborhod.size(); i++){
    if(dominates(landscape.neighborhod[i], solution_0)){
      solution_0 = landscape.neighborhod[i];
    }
  }

  pareto_front.push_back(solution_0);

  for(int i = 1; i < landscape.neighborhod.size(); i++){
    add_front_0(landscape.neighborhod[i], pareto_front);
  }
  
  return pareto_front.size();
}

#endif