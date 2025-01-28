#include "../../../../headers/global_modules/generate_initial_population/population_v2.h"
#include "../../../../headers/global_modules/generate_initial_population/generate_rSolution.h"

#include <iostream>
#include <time.h>
#include <list> 
using namespace std;

list<Solution> create_initial_population_v2(int size_population) {

  list<Solution> population; 

  for (int i = 0; i < size_population; i++) {
    Solution* sol = new Solution(generate_solution());

    population.push_back(*sol);
    pareto->adicionarSol(sol); 

    countRevalue++;

    if(countRevalue % 100000 == 0){
      string path = instance + "_" + algorithm + "_" + to_string(countRevalue) + ".txt";
            
      pareto->printAllSolutions(root_folder + path);

      if(countRevalue >= stop_criteria){
        pareto->printAllSolutionsLayout(root_folder + instance + "_" + algorithm + "_layout.txt");
      }
    }
    delete sol;
  }

  return population; 
}
