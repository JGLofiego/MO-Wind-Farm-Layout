#include "../generate_population/population.h"
#include "../generate_random_solution/generate_rSolution.h"
#include <iostream>
using namespace std;

void mutation(Solution &solution){
  vector<int> available_positions = solution.available_positions;
  vector<int> n_available_positions = solution.n_available_positions;

  int rand_intA = rand() % available_positions.size();
  int gene_available = available_positions[rand_intA];

  int rand_intB = rand() % n_available_positions.size();
  int gene_n_available = n_available_positions[rand_intB];

  n_available_positions.erase(n_available_positions.begin() + rand_intB);  
  solution.n_available_positions.push_back(gene_available);

  available_positions.erase(available_positions.begin() + rand_intA);  
  solution.available_positions.push_back(gene_n_available); 

  solution.grid[gene_available] = true;
  solution.grid[gene_n_available] = false;
}