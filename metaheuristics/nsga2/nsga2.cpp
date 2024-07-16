#include "../../modules/generate_initial_population/generate_population/population.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"
#include <iostream>
#include <ctime> 
using namespace std;

int main(){

  srand(time(0)); //Initializing the random number generator 

  //Information that must be extracted from each instance
  int num_turb = 3;
  int upperBoundX = 3;
  int upperBoundY = 3;
  int size_population = 2; //Size of the population

  //Initial population
  vector<Solution> initial_population = create_initial_population(size_population, num_turb, upperBoundX, upperBoundY);  
  
  for (int i = 0; i < initial_population.size(); i++) {
      cout << "Solution " << i + 1 << ":\n";
      // Print the 1D grid as a 2D grid (matrix)
      for (int j = 0; j < upperBoundY; j++) {
        for (int k = 0; k < upperBoundX; k++) {
          cout << initial_population[i].grid[j * upperBoundX + k] << " ";
        }
        cout << endl;
      }
  }

  /*Mutation
  mutation(initial_population[0]);
    
  for (int i = 0; i < initial_population.size(); i++) {
      cout << "Solution " << i + 1 << ":\n";
      // Print the 1D grid as a 2D grid (matrix)
      for (int j = 0; j < upperBoundY; j++) {
        for (int k = 0; k < upperBoundX; k++) {
          cout << initial_population[i].grid[j * upperBoundX + k] << " ";
        }
        cout << endl;
      }
  }*/

  //Crossover
  Solution sol = crossover(initial_population[0], initial_population[1]);
    
  for (int i = 0; i < initial_population[0].grid.size(); i++) {
    cout << sol.grid[i] << " ";
  }
  
}