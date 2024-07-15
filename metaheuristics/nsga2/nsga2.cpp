#include "../../modules/generate_initial_population/generate_population/population.h"
#include <iostream>
#include <ctime> 
using namespace std;

int main(){

  srand(time(0)); //Initializing the random number generator 

  //Information that must be extracted from each instance
  int num_turb = 50;
  int upperBoundX = 20;
  int upperBoundY = 20;
  int size_population = 3; //Size of the population

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
  
}