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
  vector<vector<vector<bool>>> initial_population = create_initial_population(size_population, num_turb, upperBoundX, upperBoundY);  
  
  for (int k = 0; k < initial_population.size(); ++k) {
        cout << "Solution " << k + 1 << ":\n";
    for (int i = 0; i < initial_population[k].size(); ++i) {
      for (int j = 0; j < initial_population[k][i].size(); ++j) {
        cout << initial_population[k][i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}