#include "../../headers/population.h"
#include "../../headers/generate_rSolution.h"
#include <iostream>
#include <time.h>
using namespace std;

vector<Solution> create_initial_population(int size_population) {

  vector<Solution> population;

  for (int i = 0; i < size_population; i++) {
    Solution * sol = new Solution(generate_solution());
    population.push_back(*sol);
    pareto->adicionarSol(sol);

    countRevalue++;

    if(countRevalue % 100000 == 0){
      fprintf(f, "============== %d Revalues ==============\n", countRevalue);
      pareto->printAllSolutions(f);
    }

    delete sol;
  }

  return population;
}