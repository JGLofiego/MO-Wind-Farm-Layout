#include <utility>
#include <vector>
#include <iostream>
#include <ctime> 
#include <algorithm>
#include <random>

#include "../../../headers/global_modules/generate_initial_population/population.h"
#include "../../../headers/global_modules/generate_initial_population/generate_rSolution.h"

#include "../../../headers/metaheuristics/comolsd/modules/calculate_ws.h"
#include "../../../headers/metaheuristics/comolsd/modules/local_search.h"
#include "../../../headers/metaheuristics/comolsd/modules/aggregation_wrapper.h"

#include "../../../headers/metaheuristics/moead/modules/generate_weight_vectors.h"
#include "../../../headers/metaheuristics/moead/modules/generate_neighborhood.h"
#include "../../../headers/metaheuristics/moead/modules/get_best_z_point.h"

using namespace std;

void comolsd(vector<Solution>& population_p){

  //Initializing the random number generator 
  random_device rd;
  mt19937 gen(rd());

  //COMOLS_D parameters 
  int size_population = population_p.size();
  int number_of_neighbors = 10;
  
  //Building the first predefined direction vector (w1), ie, the vector of weights to each subproblem i
  vector<pair<double, double>> w1 = build_weight_vector(size_population); 
  
  //Getting z_point || VERIFICAR ISSO
  pair<double, double> ideal_point = get_best_z_point(population_p);
  pair<double, double> nadir_point = get_best_z_point(population_p);

  //Building the neighborhood (B) of each lambda vector i (or each subproblem i)
  vector<vector<int>> neighborhood = build_neighborhood(number_of_neighbors, w1, size_population);
  
  while (countRevalue < stop_criteria) {
    vector<Solution*> population_p_ptrs;
    for (Solution& sol : population_p) {population_p_ptrs.push_back(&sol);}
    
    local_search(population_p_ptrs, w1, ideal_point, neighborhood, make_aggregation_function(calculate_ws));

  }

}