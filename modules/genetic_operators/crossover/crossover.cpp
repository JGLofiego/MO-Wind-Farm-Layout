#include "../../headers/population.h"
#include "../../headers/crossover.h"
#include <cstdlib>
#include <vector>
#include <iostream>

/*The goal of the crossover is: randomly select a position in zone i (rand_int) and copy all the turbines
from 0 to rand_int from parent_solutionA to the offspring solution (offspring_solution).

Then, for each position in parent_solutionB that is not zero (i.e. has a turbine) and that turbine
has not already been added to the offspring, we add that turbine to the offspring.

PS: THIS IS DONE FOR ALL ZONES i SUCH AS i < num_zones.*/


//Function to find the index of a turbine (searching for its id) within of a vector of turbines in zone i.
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

void crossoverAux(Solution &parent_solutionA, Solution &parent_solutionB, Solution &offspring_solution, int zone){
  offspring_solution.grid[zone].resize(parent_solutionA.grid[zone].size(), 0);

  int rand_int = rand() % parent_solutionA.grid[zone].size();
  int index = -1;
  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    offspring_solution.grid[zone][i] = parent_solutionA.grid[zone][i];

    if(parent_solutionA.grid[zone][i] != 0){
      index = find_turbine(parent_solutionA.turbines[zone], parent_solutionA.grid[zone][i]);
      offspring_solution.turbines[zone].push_back(parent_solutionA.turbines[zone][index]);
    }

    lastIndex = i;
  }

  // Second part of crossover with parent_solutionB
  
  for(int i = 0; i < parent_solutionB.grid[zone].size(); i++){
    if(parent_solutionB.grid[zone][i] != 0){
      if(notInOffspring(parent_solutionB.grid[zone][i], offspring_solution.grid[zone])){
        offspring_solution.grid[zone][lastIndex + 1] = parent_solutionB.grid[zone][i];
        lastIndex++;

        index = find_turbine(parent_solutionB.turbines[zone], parent_solutionB.grid[zone][i]);
        offspring_solution.turbines[zone].push_back(parent_solutionB.turbines[zone][index]);
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