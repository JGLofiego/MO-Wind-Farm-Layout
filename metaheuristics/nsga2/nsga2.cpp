#include "../../modules/headers/main.h"
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
  
  for(int i = 0; i < 10; i++){
    for(auto& solution: initial_population){
      //Parent selection
      
    }
  }
  
}