#include <iostream>
#include <ctime> 
#include <cstdlib>
#include <utility> 
#include <random>
#include "../../modules/headers/population.h"
#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"
#include "../../modules/headers/binary_tournament.h"
#include "../../modules/headers/crowding_distance.h"
#include "../../modules/headers/non_dominated_sorting.h"

using namespace std;

int main(){

  //Initializing the random number generator 
  default_random_engine re{(unsigned)time(nullptr)};
  uniform_real_distribution<double> dist(0.0, 1.0);

  //Information that must be extracted from each instance
  int num_turb = 3;

  //NGSAII paramets 
  int size_population = 10; //Size of the population
  double cross_prob = 0.8;
  double mutation_prob = 0.4;
  int max_generations = 3;

  //Initial population
  vector<Solution> population = create_initial_population(size_population, num_turb); 

  cout << endl;
  cout << "------------Initial population ------------ " << endl;
  for(auto& i : population){
    cout << "<" << i.fitness.first << ", " << i.fitness.second << ">" << endl;
  }
  cout << "------------------------------------------- " << endl << endl;

  int generation = 0;

  while(generation < max_generations){

    cout << "======================= GENERATION: " << generation << "=======================" << endl;

    vector<Solution> offspring_population;

    for(int i = 0; i < size_population; i++){
      //Parent selection
      pair<Solution, Solution> parents = binary_tornament(population);
      cout << endl;
      cout << "Parent 1: " << parents.first.fitness.first << " " << parents.first.fitness.second << endl;
      cout << "Parent 2: " << parents.second.fitness.first << " " << parents.second.fitness.second << endl;
      
      //Crossover
      Solution child1, child2;
      double k = (double) rand() / RAND_MAX;

      if(k < cross_prob){
        child1 = crossover(parents.first, parents.second);
        child2 = crossover(parents.second, parents.first);
      }
      else{
        child1 = parents.first;
        child2 = parents.second;
      }

      //Mutation
      k = (double) rand() / RAND_MAX;

      if(k < mutation_prob){
        mutation(child1);
        mutation(child2);
      }

      offspring_population.push_back(child1);
      offspring_population.push_back(child2);
    }

    //Mergin 'population' (size: N) + 'offspring_population' (size: 2N) = 'total_population' (size: 3N)
    //Adding the offspring_population at the end of the 'population' in 'total_population'
    vector<Solution> total_population = population;
    total_population.insert(total_population.end(), offspring_population.begin(), offspring_population.end()); 

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