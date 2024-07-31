#include "../../headers/population.h"
#include "../../headers/crossover.h"
#include <cstdlib>
#include <vector>
#include <iostream>

// Function to check if a turbine_id is in the grid vector of the child solution
bool notInChild(int turbine_id, const vector<int> &grid) {
  for (int id : grid) {
    if (id == turbine_id) {
      return false;
    }
  }
  return true;
}

Solution crossover(Solution &parent_solutionA, Solution &parent_solutionB){
  Solution child_solution;
  child_solution.grid.resize(parent_solutionA.grid.size(), 0);

  int rand_int = rand() % parent_solutionA.grid.size();

  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    child_solution.grid[i] = parent_solutionA.grid[i];
    lastIndex = i;
  }

  // Second part of crossover with parent_solutionA
  for(int i = 0; i < parent_solutionB.grid.size(); i++){
    if(parent_solutionB.grid[i] != 0){
      if(notInChild(parent_solutionB.grid[i], child_solution.grid)){
        child_solution.grid[lastIndex + 1] = parent_solutionB.grid[i];
        lastIndex++;
      }
    }
  }

  return child_solution;
}