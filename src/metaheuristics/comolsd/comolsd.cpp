#include <utility>
#include <vector>
#include <iostream>
#include <ctime> 
#include <algorithm>

#include "../../../headers/global_modules/generate_initial_population/population.h"
#include "../../../headers/global_modules/generate_initial_population/generate_rSolution.h"

#include "../../../headers/metaheuristics/comolsd/modules/calculate_ws.h"
#include "../../../headers/metaheuristics/comolsd/modules/local_search.h"
#include "../../../headers/metaheuristics/comolsd/modules/codvs.h"
#include "../../../headers/metaheuristics/comolsd/modules/update_population.h"
#include "../../../headers/metaheuristics/comolsd/modules/get_nadir_point.h"
#include "../../../headers/metaheuristics/comolsd/modules/aggregation_wrapper.h"
#include "../../../headers/metaheuristics/comolsd/modules/make_population_pointers.h"

#include "../../../headers/metaheuristics/moead/modules/generate_weight_vectors.h"
#include "../../../headers/metaheuristics/moead/modules/generate_neighborhood.h"
#include "../../../headers/metaheuristics/moead/modules/get_best_z_point.h"

using namespace std;

void comolsd(vector<Solution>& population_p){

  //COMOLS_D parameters 
  int size_population = population_p.size();
  int number_of_neighbors = 10;
  
  //Building the first predefined direction vector (w1), ie, the vector of weights to each subproblem i
  vector<pair<double, double>> w1 = build_weight_vector(size_population); 
  
  //Getting z_point
  pair<double, double> ideal_point = get_best_z_point(population_p);
  pair<double, double> nadir_point = get_nadir_point(population_p);

  //Building the neighborhood (B) of each lambda vector i (or each subproblem i)
  vector<vector<int>> neighborhood = build_neighborhood(number_of_neighbors, w1, size_population);

  //Set Q
  vector<Solution> population_q;
  
  while (countRevalue < stop_criteria) {
    local_search(make_population_pointers(population_p), w1, ideal_point, neighborhood, make_aggregation_function(calculate_ws));

    vector<Solution> union_pq = population_p;
    union_pq.insert(union_pq.end(), population_q.begin(), population_q.end());

    // Update of the ideal z* point and the nadir point
    for (const auto& sol : union_pq) {
        // Updates ideal point (z*)
        ideal_point.first = max(ideal_point.first, sol.fitness.first);
        ideal_point.second = max(ideal_point.second, sol.fitness.second);
        
        // Updates nadir point (z^nad)
        nadir_point.first = min(nadir_point.first, sol.fitness.first);
        nadir_point.second = min(nadir_point.second, sol.fitness.second);
    }

    auto w2 = codvs(nadir_point, population_p, population_q, size_population);

    population_q = update_population(w2, union_pq, nadir_point, make_aggregation_function(calculate_ipbi));
    //verificar envio de vizinhança
    local_search(make_population_pointers(population_q), w2, nadir_point, neighborhood, make_aggregation_function(calculate_ipbi));

    population_p = update_population(w1, union_pq, ideal_point, make_aggregation_function(calculate_ws));
  }

}