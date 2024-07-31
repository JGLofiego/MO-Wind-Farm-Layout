#include "../headers/generate_rSolution.h"
#include "../headers/binary_tournament.h"

#include <utility>
#include <set>

int get_random_index(int population_size, const set<int>& used_indices) {
  int index;
  do {
    index = rand() % population_size;
  } while (used_indices.find(index) != used_indices.end());

  return index;
}

pair<Solution, Solution> binary_tornament(vector<Solution>& population){
  pair<Solution, Solution> parents;
  set<int> used_indices;

  //Getting unique indexes for candidates
  int i1 = get_random_index(population.size(), used_indices);
  used_indices.insert(i1);
  int i2 = get_random_index(population.size(), used_indices);
  used_indices.insert(i2);
  int i3 = get_random_index(population.size(), used_indices);
  used_indices.insert(i3);
  int i4 = get_random_index(population.size(), used_indices);
  used_indices.insert(i4);

  Solution candidate1 = population[i1];
  Solution candidate2 = population[i2];
  Solution candidate3 = population[i3];
  Solution candidate4 = population[i4];

  //Choosing the solution that is better in the first objective
  if(candidate1.fitness.first >= candidate2.fitness.first) parents.first = candidate1;
  else parents.first = candidate2;

  //Choosing the solution that is better in the second objective
  if(candidate3.fitness.second >= candidate4.fitness.second) parents.second = candidate3;
  else parents.second = candidate4;

  return parents;
}