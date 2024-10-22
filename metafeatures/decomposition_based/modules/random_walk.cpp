#include <vector>
#include <utility>
#include <iostream>

#include "../../../headers/features/landscapeElement.h"
#include "../headers/tchebycheff_metafeatures.h"
#include "../headers/random_walk.h"
#include "../headers/get_neighborhood.h"
#include "../../../modules/headers/population.h"

using namespace std;

vector<LandscapeElement> random_walk(int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, double &max, double &min){

  vector<LandscapeElement> S;
  Solution current_solution = create_initial_population(1)[0];

  //Definition of z_point
  pair<double, double> z_point;
  // z_point.first = -12313123123123;
  // z_point.second = 30.4;
  z_point.first = current_solution.fitness.first;
  z_point.second = current_solution.fitness.second;

  for(int step = 0; step < walk_lenght; step++){
    LandscapeElement element;
    element.current_solution = current_solution; //Adding the 'current_solution' to S

    //Getting the value of tchebycheff function for the current solution 
    double current_solution_fitness = calculate_gte_metafeatures(current_solution.fitness, lambda, z_point);
    element.tch_current_solution = current_solution_fitness;

    //Getting the min and max values of all solutions x
    if(current_solution_fitness < min){
      min = current_solution_fitness;
    }

    if(current_solution_fitness > max){
      max = current_solution_fitness;
    }

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(current_solution, number_of_neighbors);
    element.neighborhod = neighborhood; //Adding the neighborhood of 'current_solution' to S

    double best_cost = current_solution.fitness.first;
    double best_power = current_solution.fitness.second;

    for (Solution& neighbor : neighborhood) {
      double neighborSolution_fitness = calculate_gte_metafeatures(neighbor.fitness, lambda, z_point);
      element.tchebycheff_neighbors.push_back(neighborSolution_fitness);

      //Getting the min and max values of all solutions x
      if(neighborSolution_fitness < min){
        min = neighborSolution_fitness;
      }
      if(neighborSolution_fitness > max){
        max = neighborSolution_fitness;
      }

      //Getting the best objective values to update the z_point later
      if(neighbor.fitness.first > best_cost){
        best_cost = neighbor.fitness.first;
      }
      if(neighbor.fitness.second > best_power){
        best_power = neighbor.fitness.second;
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

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    current_solution = random_neighbor;
  }

  return S;
}
