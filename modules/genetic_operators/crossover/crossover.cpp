#include "../../generate_initial_population/generate_population/population.h"
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
  cout << endl;
  cout << parent_solutionA.grid[rand_int];
  cout << endl;
  cout << endl;

  /*The crossover point initiates at 0 to rand_int in parent_solutionA 
  and continues from rand_int to the remainder of the grid size of the offspring_solution
  in the parent_solutionB, using lastIndex to track the current position in offspring_solution.*/

  int lastIndex = 0;

  // First part of crossover with parent_solutionA
  for(int i = 0; i <= rand_int; i++){
    offspring_solution.grid[i] = parent_solutionA.grid[i];
    lastIndex = i;
    if(parent_solutionA.grid[i] == 0)
      offspring_solution.available_positions.push_back(i);
    else
      offspring_solution.n_available_positions.push_back(i);
  }

  // Second part of crossover with parent_solutionA
  for(int i = rand_int; i < parent_solutionB.grid.size(); i++){
    if(notInOffspring(parent_solutionB.grid[i], offspring_solution.grid)){
      offspring_solution.grid[lastIndex + 1] = parent_solutionB.grid[i];
      lastIndex++;
      if(parent_solutionB.grid[lastIndex] == 0)
        offspring_solution.available_positions.push_back(lastIndex);
      else
        offspring_solution.n_available_positions.push_back(lastIndex);
    }
    else{
      if(parent_solutionB.grid[i] == 0){
        offspring_solution.grid[lastIndex + 1] = 0;
        lastIndex++;
        offspring_solution.available_positions.push_back(lastIndex);
      }
    }
  }

  return offspring_solution;
}