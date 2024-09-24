#include <iostream>
#include <ctime> 
#include <cstdlib>
#include <utility> 
#include <random>
#include "../../modules/headers/population.h"
#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"
#include "../../modules/nsga2/binary_tournament.cpp"
#include "../../modules/nsga2/crowding_distance.cpp"
#include "../../modules/nsga2/non_dominated_sorting.cpp"

using namespace std;

vector<Solution> nsga2(vector<Solution>& population){

  //Initializing the random number generator 
  default_random_engine re{(unsigned)time(nullptr)};
  uniform_real_distribution<double> dist(0.0, 1.0);

  //NGSAII paramets 
  int size_population = population.size(); //Size of the population
  double cross_prob = 0.8;
  double mutation_prob = 0.4;
  int max_generations = 3;

  cout << endl;
  cout << "------------INITIAL POPULATION ------------ " << endl;
  for(auto& i : population){
    cout << "<" << i.fitness.first << ", " << i.fitness.second << ">" << endl;
  }
  cout << "------------------------------------------- " << endl << endl;

  cout << "SIZE OF INITIAL POPULATION: " << population.size() << endl << endl;

  int generation = 0;

  while(generation < max_generations){

    cout << "======================= GENERATION: " << generation << "=======================" << endl << endl;

    vector<Solution> offspring_population;

    for(int i = 0; i < size_population; i++){
      //Parent selection
      pair<Solution, Solution> parents = binary_tornament(population);
  
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
    cout << "SIZE OF TOTAL POPULATION: " << total_population.size() << endl << endl;

    //Non dominated sorting
    vector<vector<Solution>> fronts = non_dominated_sorting(total_population);

    cout << "========================== FRONTS ==========================" << endl << endl;
    for(int i = 0; i < fronts.size(); i++){
      cout << "----------------------- FRONT: "<< i << " -----------------------" << endl;
      for(int j = 0; j < fronts[i].size(); j++){
        cout << "<" << fronts[i][j].fitness.first << ", " << fronts[i][j].fitness.second << ">"<< endl;
      }
    } cout << endl;

    population.clear(); //Cleaning the population to generates the next generation
    
    int k = 0;
    for (auto& front : fronts) {
      if (population.size() + front.size() <= size_population) {
        // Add the entire front if it fits in the population
        cout << "ADDING THE WHOLE FRONT " << k << endl;
        for (auto& solution : front) {
          population.push_back(solution);
        }
      } 
      else {
        // If the front doesn't fit all the way, sort by crowding distance and add the missing solutions
        auto front_sorted = crowding_distance(front);
        cout << "ADDING PART OF FRONT " << k << " (crowding distance)" << endl;
        
        // Calculate how many solutions are missing to complete the population
        int remaining_spots = size_population - population.size();
        
        // Add missing solutions
        for (int i = 0; i < remaining_spots; i++) {
          population.push_back(front_sorted[i]);
        }
        
        // The population is complete, we can exit the loop
        break;
      }
      k++;
    }

    generation++;
  }

  cout << endl;
  cout << "------------FINAL POPULATION ------------ " << endl;
  for(auto& i : population){
    cout << "<" << i.fitness.first << ", " << i.fitness.second << ">" << endl;
  }
  cout << "------------------------------------------- " << endl << endl;

  cout << "SIZE OF FINAL POPULATION: " << population.size() << endl << endl;

  return population;
}