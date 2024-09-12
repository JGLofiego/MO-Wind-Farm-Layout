#include <iostream>
#include <ctime> 
#include <cstdlib>
#include <utility> 
#include "../../modules/headers/population.h"
#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"
#include "../../modules/headers/binary_tournament.h"
#include "../../modules/headers/crowding_distance.h"
#include "../../modules/headers/non_dominated_sorting.h"

using namespace std;

int main(){

  srand(time(0)); //Initializing the random number generator 

  //Information that must be extracted from each instance
  int num_turb = 3;
  int upperBoundX = 3;
  int upperBoundY = 3;

  //NGSAII paramets 
  int size_population = 10; //Size of the population
  double probCross = 0.8;
  double probMutacao = 0.4;
  int max_generations = 3;

  //Initial population
  //vector<Solution> population = create_initial_population(size_population, num_turb, upperBoundX, upperBoundY); 
  vector<Solution> population(10);

  for (int i = 0; i < 10; i++) {
        population[i].grid = {0, 1, 0, 1, 0};  // Exemplo de grid com 5 posições
        population[i].available_positions = {0, 2, 4};  // Posições disponíveis
        population[i].n_available_positions = {1, 3};  // Posições ocupadas por turbinas
        population[i].fitness = {100.0 + i, 200.0 + i};  // Exemplo de fitness (custo, potência líquida)
  }

  population[0].fitness.first = 90;
  population[8].fitness.second = -100;

  for (int i = 0; i < 10; i++) {
        cout << "Solution " << i + 1 << ":" << endl;
        cout << "Grid: ";
        for (int j : population[i].grid) cout << j << " ";
        cout << endl;

        cout << "Available Positions: ";
        for (int j : population[i].available_positions) cout << j << " ";
        cout << endl;

        cout << "Occupied Positions: ";
        for (int j : population[i].n_available_positions) cout << j << " ";
        cout << endl;

        cout << "Fitness (Cost, Net Power): " << population[i].fitness.first << ", " << population[i].fitness.second << endl;
        cout << "--------------------------" << endl;
    }


  cout << endl;
  cout << "------------Initial population ------------ " << endl;
  for(auto& i : population){
    cout << i.fitness.first << " " << i.fitness.second << endl;
  }
  cout << "------------------------------------------- " << endl;

  int generation = 0;
  while(generation < max_generations){
    vector<Solution> offspring;

    for(int i = 0; i < size_population; i++){
      //Parent selection
      pair<Solution, Solution> parents = binary_tornament(population);
      cout << endl;
      cout << "Parent 1: " << parents.first.fitness.first << " " << parents.first.fitness.second << endl;
      cout << "Parent 2: " << parents.second.fitness.first << " " << parents.second.fitness.second << endl;
      
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
    //Adding the offspring at the end of the 'population' in 'total_population'
    vector<Solution> total_population = population;
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