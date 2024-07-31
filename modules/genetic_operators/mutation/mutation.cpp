#include "../../headers/generate_rSolution.h"
#include "../../headers/mutation.h"
#include <cstdlib>
using namespace std;

Solution mutation(Solution& solution){

    int grid_size = solution.grid.size();
    int rand_intA, rand_intB;

    // Select two positions at random
    // Ensure that rand_intA and rand_intB are different and both are not a available position
    do{
      rand_intA = rand() % grid_size;
      rand_intB = rand() % grid_size;
    } while(rand_intA == rand_intB || (solution.grid[rand_intA] == 0 && solution.grid[rand_intB] == 0));

    // Swapping the genes between grid[rand_intA] e grid[rand_intB]
    int geneA = solution.grid[rand_intA];
    int geneB = solution.grid[rand_intB];

    solution.grid[rand_intA] = geneB;
    solution.grid[rand_intB] = geneA;

    return solution;
}