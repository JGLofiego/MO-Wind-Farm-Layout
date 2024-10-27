#include <vector>
#include <utility>

#include "../../../headers/metafeatures/landscapeElement.h"
#include "../../../headers/metafeatures/tchebycheff_metafeatures.h"
#include "../../../headers/metafeatures/random_walk.h"
#include "../../../headers/metafeatures/get_neighborhood.h"
#include "../../../modules/headers/population.h"

using namespace std;

vector<LandscapeElement> random_walk(int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, std::pair<double, double> &global_z_point, double &max, double &min){

  vector<LandscapeElement> S;
  Solution current_solution = create_initial_population(1)[0];

  //Definition of z_point
  pair<double, double> z_point;
  // z_point.first = -12313123123123;
  // z_point.second = 30.4;
  z_point.first = global_z_point.first;
  z_point.second = global_z_point.second;

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

    //Calculating Dominance Metrics
    double num_neighbors = (double) neighborhood.size();

    int countDominating = 0;    // Number of neighbors that Current Solution Dominates
    int countIsDominated = 0;   // Number of neighbors that dominates Current Solution
    for(int i = 0; i < neighborhood.size(); i++){
      if(dominates(current_solution, neighborhood[i])){
        countDominating++;
      } else if(dominates(neighborhood[i], current_solution)){
        countIsDominated++;
      }
    }

    element.inf = countDominating / num_neighbors ;
    element.sup = countIsDominated / num_neighbors;
    element.inc = 1.0 - (element.inf + element.sup);


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
    }

    S.push_back(element);

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    current_solution = random_neighbor;
  }

  return S;
}
