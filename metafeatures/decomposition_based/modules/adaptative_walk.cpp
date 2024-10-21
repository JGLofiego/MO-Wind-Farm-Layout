#include <vector>
#include <utility>
#include "../headers/adaptative_walk.h"
#include "../../../headers/features/landscapeElement.h"
#include "../headers/tchebycheff_metafeatures.h"
#include "../../../modules/headers/population.h"
#include "../headers/get_neighborhood.h"

using namespace std;

vector<LandscapeElement> adaptive_walk(int number_of_neighbors, pair<double, double> &lambda, int num_turb) {
  
  vector<LandscapeElement> S;
  Solution currentSolution = create_initial_population(1, num_turb)[0];

  //Definition of z_point
  pair<double, double> z_point;
  z_point.first = -119586168.719194576144;
  z_point.second = 20.4;
  
  while (true) {
    LandscapeElement element;
    element.current_solution = currentSolution;

    //Getting the value of tchebycheff function for the current solution 
    double currentSolution_fitness = calculate_gte_metafeatures(currentSolution.fitness, lambda, z_point);
    element.tch_current_solution = currentSolution_fitness;

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(currentSolution, number_of_neighbors);
    element.neighborhod = neighborhood;

    //Finding the best neighbor and calculating its fitness
    double best_neighbor_fitness = numeric_limits<double>::infinity();
    int index_best_neighbor;

    double best_cost = currentSolution.fitness.first;
    double best_power = currentSolution.fitness.second;

    for(int i = 0; i < neighborhood.size(); i++){
      double neighborSolution_fitness = calculate_gte_metafeatures(neighborhood[i].fitness, lambda, z_point);
      element.tchebycheff_neighbors.push_back(neighborSolution_fitness);

      if(neighborSolution_fitness < best_neighbor_fitness){
        best_neighbor_fitness = neighborSolution_fitness;
        index_best_neighbor = i;
      }

      //Getting the best objective values to update the z_point later
      if(neighborhood[i].fitness.first > best_cost){
        best_cost = neighborhood[i].fitness.first;
      }
      if(neighborhood[i].fitness.second > best_power){
        best_power = neighborhood[i].fitness.second;
      }
    }

    S.push_back(element);

    //Z-point update
    if(best_cost > z_point.first){
      z_point.first = best_cost;
    }
    if(best_power > z_point.second){
      z_point.second = best_power;
    }

    if(best_neighbor_fitness < currentSolution_fitness){
      currentSolution = neighborhood[index_best_neighbor];
    } else{
      break;
    }
  }
  return S;
}
