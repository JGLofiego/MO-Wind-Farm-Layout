#include <iostream>
#include <ctime> 
#include <cstdlib>
#include <utility> 
#include <random>
#include <list>
#include "../../../headers/global_modules/generate_initial_population/population.h"
#include "../../../headers/global_modules/generate_initial_population/generate_rSolution.h"
#include "../../../headers/global_modules/genetic_operators/mutation.h"
#include "../../../headers/global_modules/genetic_operators/crossover.h"
#include "../../../headers/metaheuristics/nsga2/modules/binary_tournament.h"
#include "../../../headers/metaheuristics/nsga2/modules/binary_tournament_v2.h"
#include "../../../headers/metaheuristics/nsga2/modules/crowding_distance.h"
#include "../../../headers/metaheuristics/nsga2/modules/crowding_distance_v2.h"
#include "../../../headers/metaheuristics/nsga2/modules/non_dominated_sorting.h"
#include "../../../headers/metaheuristics/nsga2/modules/arena_non_dominated_sorting.h"
#include "../../../headers/metaheuristics/nsga2/modules/arena_non_dominated_sorting_v2.h"

#include "../../../headers/global_modules/dominates.h"
#include "../../../headers/global_modules/isEqual.h"
#include "../../../headers/metaheuristics/nsga2/nsga2_v2.h"
#include "../../../headers/globals.h"


// Checking if there are copies of 'solution' in population
void add_v2(list<Solution*>& population, Solution* solution){
  for (auto& existing_solution : population) {
    if (isEqual(*existing_solution, *solution)) {
      delete solution; 
      return;          
    }
  }
  population.push_back(solution);
}

list<Solution*> nsga2_v2(list<Solution>& pop){

  list<Solution*> * population = new list<Solution*>(); 

  for(auto& sol : pop){
    Solution * s = new Solution(sol);
    add_v2(*population, s);
  }

  //Initializing the random number generator 
  default_random_engine re{(unsigned)time(nullptr)};
  uniform_real_distribution<double> dist(0.0, 1.0);

  // Parâmetros NGSAII
  int size_population = population->size(); //Size of the population
  double cross_prob = 0.95;
  double mutation_prob = 0.05;
  int stop_criteria = 1000000;

  ofstream infoRunNSGA2(root_folder + "infoRun.txt");

  int generation = 0;

  while(countRevalue < stop_criteria){

    infoRunNSGA2 << "Generation " << generation << " | Revalues: " << countRevalue << " | GridSize: " << pareto->getSize() << endl;

    list<Solution*> * offspring_population = new list<Solution*>(); 

    for(int i = 0; i < size_population; i++){
      //Parent selection
      Solution** parents = binary_tournament_v2(*population);
  
      // Crossover
      Solution * child1 = new Solution;
      Solution * child2 = new Solution;
      *child1 = *parents[0];
      *child2 = *parents[1];
      double k = dist(re);

      if((static_cast<double>(rand()) / RAND_MAX) < cross_prob){
        *child1 = crossover(*parents[0], *parents[1]);
        *child2 = crossover(*parents[1], *parents[0]);

        add_v2(*offspring_population, new Solution(*child1));
        add_v2(*offspring_population, new Solution(*child2));
      }

      //Mutation
      k = dist(re);

      if((static_cast<double>(rand()) / RAND_MAX) < mutation_prob){
        mutation(*child1);
        mutation(*child2);

        add_v2(*offspring_population, new Solution(*child1));
        add_v2(*offspring_population, new Solution(*child2));
      }

      delete parents[0];
      delete parents[1];
      delete[] parents; 

      delete child1;
      delete child2;
    }

    //Merging 'population' (size: N) + 'offspring_population' (size: 4N) = 'total_population' (size: 5N)
    //Adding the offspring_population at the end of the 'population' in 'total_population'
    list<Solution*> * total_population = new list<Solution*>();

    for(auto i : *population){
      total_population->push_back(new Solution(*i));
    }

    for (auto i : *offspring_population){
      total_population->push_back(new Solution(*i));
      delete i;
    }

    delete offspring_population;

    cout << "SIZE OF TOTAL POPULATION: " << total_population->size() << endl << endl;

    // Non dominating sorting
    list<Solution*> fronts[SIZE_OF_POPULATION * 5];
    arena_non_dominated_sorting_v2(*total_population, fronts);

    int qtd = 0;
    for (int i = 0; i < fronts->size(); i++) {
      if (!fronts[i].empty())
        qtd += fronts[i].size();
    }

    cout << "POPULACAO ARENA -> " << qtd << endl << endl;

    for(auto i : *total_population){
      delete i;
    }

    delete total_population;

    for(auto i : *population){
      delete i;
    }

    population->clear();
    
    // cout << "Fronts size: " << fronts->size() << std::endl;

    cout << "========================== FRONTS - ARENA ==========================" << endl << endl;

    for (size_t i = 0; i < fronts->size(); i++) {
      cout << "----------------------- FRONT: " << i << " -----------------------" << endl;
      cout << "FRONT SIZE: " << fronts[i].size() << endl;
      cout << "TESTE: "<< i << endl;
      for (auto* solution : fronts[i]) {
        cout << "<" << solution->fitness.first << ", " << solution->fitness.second << ">" << endl;
      }
    }
    
    break;  
        
    int k = 0;
    for (auto& front : fronts) {
      if (population->size() + front.size() <= size_population) {
        // Add the entire front if it fits in the population
        for (auto solution : front) {
          population->push_back(new Solution(*solution));
        }
      }
      else {
        // If the front doesn't fit all the way, sort by crowding distance and add the missing solutions
        auto * front_sorted = new list<Solution*>();  
        *front_sorted = crowding_distance_v2(front);
        
        // Calculate how many solutions are missing to complete the population
        int remaining_spots = size_population - population->size();

        auto it = front_sorted->begin();
        
        // Add missing solutions
        for (int i = 0; i < remaining_spots; i++) {
          population->push_back(new Solution(**it));
          ++it;
        }

        delete front_sorted;
        
        // The population is complete, we can exit the loop
        break;
      }
      k++;
    }

    for(auto& front : fronts){
      for(auto solution : front){
        delete solution;
      }
    }

    generation++;
  }

  infoRunNSGA2.close();
  return *population;
}
