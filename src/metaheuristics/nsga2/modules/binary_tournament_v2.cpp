#include <utility>
#include <random>
#include "../../../../headers/global_modules/generate_initial_population/generate_rSolution.h"
#include "../../../../headers/metaheuristics/nsga2/modules/binary_tournament_v2.h"
#include <list>
using namespace std;

Solution** binary_tournament_v2(list<Solution*>& population){
  Solution** parents = new Solution*[2];

  parents[0] = new Solution;
  parents[1] = new Solution;

  // Getting a random index for a solution
  auto it1 = population.begin();
  advance(it1, rand() % population.size());
  auto it2 = population.begin();
  advance(it2, rand() % population.size());
  auto it3 = population.begin();
  advance(it3, rand() % population.size());
  auto it4 = population.begin();
  advance(it4, rand() % population.size());

  Solution* candidate1 = *it1;
  Solution* candidate2 = *it2;
  Solution* candidate3 = *it3;
  Solution* candidate4 = *it4;

  // Choosing the best solution in the first objective
  if(candidate1->fitness.first >= candidate2->fitness.first){
    *parents[0] = *candidate1; 
  } else{
    *parents[0] = *candidate2;
  }  

  // Choosing the best solution in the second objective
  if(candidate3->fitness.second >= candidate4->fitness.second) *parents[1] = *candidate3;
  else *parents[1] = *candidate4;

  return parents;
}
