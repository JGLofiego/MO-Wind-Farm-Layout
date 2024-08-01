#include "../../modules/headers/main.h"
#include <iostream>
#include <ctime> 
#include <utility> 
using namespace std;

int main(){

  srand(time(0)); //Initializing the random number generator 

  //Information that must be extracted from each instance
  int num_turb = 3;
  int upperBoundX = 3;
  int upperBoundY = 3;

  //NGSAII paramets 
  int size_population = 2; //Size of the population
  double probCross = 0.8;
  double probMutacao = 0.4;
  int max_generations = 3;

  //Initial population
  vector<Solution> population = create_initial_population(size_population, num_turb, upperBoundX, upperBoundY);  
  
  int generation = 0;
  while(generation < max_generations){
    vector<Solution> offspring;

    for(int i = 0; i < size_population; i++){
      //Parent selection
      pair<Solution, Solution> parents = binary_tornament(population);
      
      //Crossover
      Solution child1, child2;
      double k = (double) rand() / RAND_MAX;

      if(k < probCross){
        child1 = crossover(parents.first, parents.second);
        child2 = crossover(parents.second, parents.first);
      }
      else{
        child1 = parents.first;
        child2 = parents.second;
      }

      //Mutation
      k = (double) rand() / RAND_MAX;

      if(k < probMutacao){
        child1 = mutation(child1);
        child2 = mutation(child2);
      }

      offspring.push_back(child1);
      offspring.push_back(child2);
    }

    //Mergin 'population' + 'offspring' = 'total_population'
    vector<Solution> total_population = population;
    //Adding the offspring at the end of the 'population' in 'total_population'
    total_population.insert(total_population.end(), offspring.begin(), offspring.end()); 

    //Non dominated sorting
    vector<vector<Solution>> fronts = non_dominated_sorting(total_population);

    population.clear(); //Cleaning the population to generates the next generation

    for (auto& front : fronts) {
      if(population.size() + front.size() <=size_population){
        for(auto& solution : front){
          population.push_back(solution);
        }
      }
      else{
        auto front_sorted = crowding_distance(front);
        for(int i = 0; i < size_population - population.size(); i++){
          population.push_back(front_sorted[i]);
        }
        break;
      }
    }
    generation++;
  }
  
}