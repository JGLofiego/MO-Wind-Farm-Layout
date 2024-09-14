#include "../../headers/population.h"
#include "../../headers/crossover.h"
#include <cstdlib>
#include <vector>
#include <iostream>

int find_turbine(vector<Turbine> &vec, int value){
  for(int i = 0; i < vec.size(); i++){
    if(vec[i].id == value){
      return i;
    }
  }
  return -1;
}

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

  int index = -1;

  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    offspring_solution.grid[i] = parent_solutionA.grid[i];

    if(parent_solutionA.grid[i] != 0){
      index = find_turbine(parent_solutionA.turbines, parent_solutionA.grid[i]);
      offspring_solution.turbines.push_back(parent_solutionA.turbines[index]);
    }

    lastIndex = i;
  }

  // Second part of crossover with parent_solutionA
  
  for(int i = 0; i < parent_solutionB.grid.size(); i++){
    if(parent_solutionB.grid[i] != 0){
      if(notInOffspring(parent_solutionB.grid[i], offspring_solution.grid)){
        offspring_solution.grid[lastIndex + 1] = parent_solutionB.grid[i];
        lastIndex++;

        index = find_turbine(parent_solutionB.turbines, parent_solutionB.grid[i]);
        offspring_solution.turbines.push_back(parent_solutionB.turbines[index]);
      }
    }
  }

  calculate_cost(offspring_solution);
  calculate_power(offspring_solution);

  return offspring_solution;
}