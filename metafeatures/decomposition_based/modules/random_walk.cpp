#include <vector>
#include <utility>

#include "../../../headers/features/landscape.h"
#include "../../../headers/features/landscapeElement.h"
#include "../headers/tchebycheff_metafeatures.h"
#include "../headers/random_walk.h"
#include "../headers/get_neighborhood.h"
#include "../../../modules/headers/population.h"

using namespace std;

vector<LandscapeElement> random_walk(Landscape &landscape, int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, int num_turb){

  vector<LandscapeElement> S;

  Solution current_solution = create_initial_population(1, num_turb)[0];

  //Definition of z_point
  pair<double, double> z_point;
  z_point.first = current_solution.fitness.first;
  z_point.second = current_solution.fitness.second;

  for(int step = 0; step < walk_lenght; step++){
    LandscapeElement element;
    element.current_solution = current_solution; //Adding the 'current_solution' to S

    //Getting the value of tchebycheff function for the current solution 
    double current_solution_fitness = calculate_gte_metafeatures(current_solution.fitness, lambda, z_point);
    element.tch_current_solution = current_solution_fitness;

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(current_solution, number_of_neighbors);
    //Faz a copia na mesma ordem que neighborhood foi criado?
    element.neighborhod = neighborhood; //Adding the neighborhood of 'current_solution' to S

    double best_cost = z_point.first;
    double best_power = z_point.second;

    for (Solution& neighbor : neighborhood) {
      double neighborSolution_fitness = calculate_gte_metafeatures(neighbor.fitness, lambda, z_point);
      element.tchebycheff_neighbors.push_back(neighborSolution_fitness);

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
    z_point.first = best_cost;
    z_point.second = best_power;

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    current_solution = random_neighbor;
  }

  return S;
}
