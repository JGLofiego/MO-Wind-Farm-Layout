#include "../generate_population/population.h"
#include "../generate_random_solution/generate_rSolution.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void mutation(Solution &solution){
  vector<int> &available_positions = solution.available_positions;
  vector<int> &n_available_positions = solution.n_available_positions;

  // Select one available and one unavailable position at random
  int rand_intA = rand() % available_positions.size();
  int gene_available = available_positions[rand_intA];

  int rand_intB = rand() % n_available_positions.size();
  int gene_n_available = n_available_positions[rand_intB];

  // Remove unavailable position from list, because now it's available
  n_available_positions.erase(n_available_positions.begin() + rand_intB); 
  // Add the available position to the unavailable list, because the available position it is now unavailable 
  solution.n_available_positions.push_back(gene_available);

  // Remove avaible position from list, because now it's unavailable
  available_positions.erase(available_positions.begin() + rand_intA);  
  // Add the unavailable position to the available list, because the unavailable position it is now available 
  solution.available_positions.push_back(gene_n_available); 

  // Update the grid
  solution.grid[gene_available] = true;
  solution.grid[gene_n_available] = false;
}