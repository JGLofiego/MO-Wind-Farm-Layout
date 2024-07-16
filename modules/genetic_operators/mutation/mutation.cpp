#include "../../generate_initial_population/generate_population/population.h"
#include "../../headers/mutation.h"
#include <cstdlib>
using namespace std;

void mutation(Solution &solution){

    // Select one available and one unavailable position at random
    int rand_intA = rand() % solution.available_positions.size();
    int rand_intB;

    // Ensure that rand_intA and rand_intB are different
    do{
      rand_intB = rand() % solution.n_available_positions.size();
    } while(rand_intA == rand_intB);

    int gene_available = solution.available_positions[rand_intA];
    int gene_unavailable = solution.n_available_positions[rand_intB];

    // Remove unavailable position from the unavailable list, because now it's available
    solution.n_available_positions.erase(solution.n_available_positions.begin() + rand_intB); 
    // Add the available position to the unavailable list, because the available position it is now unavailable 
    solution.n_available_positions.push_back(gene_available);

    // Remove available position from the available list, because now it's unavailable
    solution.available_positions.erase(solution.available_positions.begin() + rand_intA);  
    // Add the unavailable position to the available list, because the unavailable position it is now available 
    solution.available_positions.push_back(gene_unavailable); 

    // Update the grid
    solution.grid[gene_available] = solution.grid[gene_unavailable]; //Filling the available position with the number of the turbine
    solution.grid[gene_unavailable] = 0;
}