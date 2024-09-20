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

void crossoverAux(Solution &parent_solutionA, Solution &parent_solutionB, Solution &offspring_solution, int zona){
  offspring_solution.grid[zona].resize(parent_solutionA.grid[zona].size(), 0);


  int rand_int = rand() % parent_solutionA.grid[zona].size();
  int index = -1;
  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    offspring_solution.grid[zona][i] = parent_solutionA.grid[zona][i];

    if(parent_solutionA.grid[zona][i] != 0){
      index = find_turbine(parent_solutionA.turbines[zona], parent_solutionA.grid[zona][i]);
      offspring_solution.turbines[zona].push_back(parent_solutionA.turbines[zona][index]);
    }

    lastIndex = i;
  }

  // Second part of crossover with parent_solutionB
  
  for(int i = 0; i < parent_solutionB.grid[zona].size(); i++){
    if(parent_solutionB.grid[zona][i] != 0){
      if(notInOffspring(parent_solutionB.grid[zona][i], offspring_solution.grid[zona])){
        offspring_solution.grid[zona][lastIndex + 1] = parent_solutionB.grid[zona][i];
        lastIndex++;

        index = find_turbine(parent_solutionB.turbines[zona], parent_solutionB.grid[zona][i]);
        offspring_solution.turbines[zona].push_back(parent_solutionB.turbines[zona][index]);
      }
    }
  }
}

Solution crossover(Solution &parent_solutionA, Solution &parent_solutionB){

  Solution offspring_solution;
  offspring_solution.grid.resize(num_zones);
  offspring_solution.turbines.resize(num_zones);

  for(int j = 0; j < num_zones; j++){
    crossoverAux(parent_solutionA, parent_solutionB, offspring_solution, j);
  }

  calculate_cost(offspring_solution);
  calculate_power(offspring_solution);

  return offspring_solution;
}