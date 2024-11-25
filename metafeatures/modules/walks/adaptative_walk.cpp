#include <vector>
#include <utility>
#include <limits>
#include <iostream>

#include "../../../headers/metafeatures/walks/adaptative_walk.h"
#include "../../../headers/metafeatures/landscapeElement.h"
#include "../../../headers/metafeatures/decomposition_based/tchebycheff_metafeatures.h"
#include "../../../modules/headers/population.h"
#include "../../../headers/metafeatures/decomposition_based/get_neighborhood.h"
#include "../../../headers/metafeatures/features_extraction.h"

using namespace std;

extern int *countReval;
extern int mode, defaultDecompPace, defaultDomPace;
extern vector<vector<LandscapeElement>> *updated_mult_walk;
extern vector<LandscapeElement> *updated_single_walk;

extern vector<pair<double, double>> lambda_vector;
extern pair<double, double> global_z_point;
extern double maximal, minimal;
extern int iLandscape;

vector<LandscapeElement> adaptive_walk_decomp(int number_of_neighbors) {

  pair<double, double> lambda = lambda_vector[iLandscape];
  vector<LandscapeElement> S;
  updated_single_walk = &S;
  Solution current_solution = create_initial_population(1)[0];
  *countReval = *countReval + 1;

  if(mode == 0 && *countReval % defaultDecompPace == 0){
    auto result = decomposition_extraction(*updated_mult_walk);
  } else if (mode == 1 && *countReval % defaultDomPace == 0){
    auto result = dominance_extraction(*updated_single_walk);
  }

  //Definition of z_point
  pair<double, double> z_point;
  z_point.first = global_z_point.first;
  z_point.second = global_z_point.second;
  
  while (true) {
    LandscapeElement element;
    element.current_solution = current_solution;

    //Getting the value of tchebycheff function for the current solution 
    double current_solution_fitness = calculate_gte_metafeatures(current_solution.fitness, lambda, z_point);
    element.tch_current_solution = current_solution_fitness;

    //Getting the min and max values of all solutions x
    if(current_solution_fitness < minimal){
      minimal = current_solution_fitness;
    }

    if(current_solution_fitness > maximal){
      maximal = current_solution_fitness;
    }

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(current_solution, number_of_neighbors);
    element.neighborhod = neighborhood; //Adding the neighborhood of 'current_solution' to S

    //Finding the best neighbor and calculating its fitness
    double best_neighbor_fitness = numeric_limits<double>::infinity();
    int index_best_neighbor;

    for(int i = 0; i < neighborhood.size(); i++){
      double neighbor_solution_fitness = calculate_gte_metafeatures(neighborhood[i].fitness, lambda, z_point);
      element.tchebycheff_neighbors.push_back(neighbor_solution_fitness);

      //Getting the min and max values of all solutions x
      if(neighbor_solution_fitness < minimal){
        minimal = neighbor_solution_fitness;
      }
      if(neighbor_solution_fitness > maximal){
        maximal = neighbor_solution_fitness;
      }

      if(neighbor_solution_fitness < best_neighbor_fitness){
        best_neighbor_fitness = neighbor_solution_fitness;
        index_best_neighbor = i;
      }
    }

    calculate_dominance_metrics(element);

    S.push_back(element);

    //Defining the next 'current_solution' of the walk
    if(best_neighbor_fitness < current_solution_fitness){
      current_solution = neighborhood[index_best_neighbor];
    } else{
      break;
    }
  }
  return S;
}

vector<LandscapeElement> adaptive_walk(int number_of_neighbors, Solution (*next_solution) (const LandscapeElement &)){

  vector<LandscapeElement> S;
  updated_single_walk = &S;
  Solution current_solution = create_initial_population(1)[0];
  *countReval = *countReval + 1;
  
  if(mode == 0 && *countReval % defaultDecompPace == 0){
    auto result = decomposition_extraction(*updated_mult_walk);
  } else if (mode == 1 && *countReval % defaultDomPace == 0){
    auto result = dominance_extraction(*updated_single_walk);
  }

  while (true) {
    LandscapeElement element;
    element.current_solution = current_solution;

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(current_solution, number_of_neighbors);
    element.neighborhod = neighborhood; //Adding the neighborhood of 'current_solution' to S

    //Getting the value of tchebycheff function for the current solution 
    double current_solution_fitness = calculate_gte_metafeatures(current_solution.fitness, lambda_vector[iLandscape], global_z_point);
    element.tch_current_solution = current_solution_fitness;

    for(int i = 0; i < neighborhood.size(); i++){
      double neighbor_solution_fitness = calculate_gte_metafeatures(neighborhood[i].fitness, lambda_vector[iLandscape], global_z_point);
      element.tchebycheff_neighbors.push_back(neighbor_solution_fitness);
    }

    calculate_dominance_metrics(element);

    S.push_back(element);

    current_solution = next_solution(element);

    if(current_solution.fitness.first == element.current_solution.fitness.first && current_solution.fitness.second == element.current_solution.fitness.second){
      break;
    }
  }

  return S;
}

Solution pareto_next_solution(const LandscapeElement &element){
  Solution best_solution;

  best_solution = element.current_solution;

  for(Solution sol : element.neighborhod){
    if(dominates(sol, best_solution)){
      return sol;
    }
  }

  return best_solution;
}