#include "../../headers/population.h"
#include "../../headers/crossover.h"
#include <cstdlib>
#include <vector>
#include <iostream>

// Function to check if a turbine_id is in the grid vector of the offspring solution
bool notInOffspring(int turbine_id, const vector<int> &grid) {
  for (int id : grid) {
    if (id == turbine_id) {
      return false;
    }
  }
  return true;
}

Solution crossover(Solution &parent_solutionA, Solution &parent_solutionB){
  Solution offspring_solution;
  offspring_solution.grid.resize(parent_solutionA.grid.size(), 0);

  int rand_int = rand() % parent_solutionA.grid.size();

  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    offspring_solution.grid[i] = parent_solutionA.grid[i];
    lastIndex = i;
  }

  // Second part of crossover with parent_solutionA
  
  for(int i = 0; i < parent_solutionB.grid.size(); i++){
    if(parent_solutionB.grid[i] != 0){
      if(notInOffspring(parent_solutionB.grid[i], offspring_solution.grid)){
        offspring_solution.grid[lastIndex + 1] = parent_solutionB.grid[i];
        lastIndex++;
      }
    }
  }

  calculate_cost(offspring_solution);
  // ************ Adaptar para o ângulo e a velocidade do vento estejam guardados na solução. ************
  // calculate_power(offspring_solution);

  return offspring_solution;
}