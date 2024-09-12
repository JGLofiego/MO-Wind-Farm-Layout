#include <utility>
#include <cstdlib>
#include <iostream>
#include <set>
#include "../headers/generate_rSolution.h"
#include "../headers/binary_tournament.h"

pair<Solution, Solution> binary_tornament(vector<Solution>& population){
  pair<Solution, Solution> parents;
  set<int> used_indices;

  //Getting a random index for a solution 
  int i1 = rand() % population.size();
  int i2 = rand() % population.size();
  int i3 = rand() % population.size();
  int i4 = rand() % population.size();

  Solution candidate1 = population[i1];
  Solution candidate2 = population[i2];
  Solution candidate3 = population[i3];
  Solution candidate4 = population[i4];

  //Choosing the best solution in the first objective
  if(candidate1.fitness.first <= candidate2.fitness.first){
    cout << candidate1.fitness.first << " <= " << candidate2.fitness.first << endl;
    parents.first = candidate1;
  } 
  else{
    cout << candidate1.fitness.first << " > " << candidate2.fitness.first << endl;
    parents.first = candidate2;
  } 

  //Choosing the best solution in the second objective
  if(candidate3.fitness.second <= candidate4.fitness.second){
    cout << candidate3.fitness.second << " <= " << candidate4.fitness.second << endl;
    parents.second = candidate3;
  } 
  else{
    cout << candidate3.fitness.second << " > " << candidate4.fitness.second << endl;
    parents.second = candidate4;
  } 

  return parents;
}