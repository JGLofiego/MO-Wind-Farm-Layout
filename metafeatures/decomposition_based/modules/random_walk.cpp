#include <vector>
#include <utility>

#include "../../../headers/features/landscape.h"
#include "../headers/tchebycheff_metafeatures.h"
#include "../headers/random_walk.h"
#include "../headers/get_neighborhood.h"
#include "../../../modules/headers/population.h"

using namespace std;

void random_walk(Landscape &landscape, int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, int num_turb){

  Solution currentSolution = create_initial_population(1, num_turb)[0];

  //Definition of z_point
  pair<double, double> z_point;
  z_point.first = currentSolution.fitness.first;
  z_point.second = currentSolution.fitness.second;

  vector<double> fitness_values;
  vector<double> fitness_differences;
  
  for(int step = 0; step < walk_lenght; step++){
    //Getting the value of tchebycheff function for the current solution 
    double currentSolution_fitness = calculate_gte_metafeatures(currentSolution.fitness, lambda, z_point);

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(currentSolution, number_of_neighbors);

    // Storing the fitness value (fv_*) in the landscape
    landscape.fitness_values.push_back(currentSolution_fitness);

    // Fitness difference (fd_*) and Improving neighbors (in_*) 
    double total_difference = 0.0;
    int improving_neighbors_count = 0;
    double best_cost, best_power;

    for (Solution& neighbor : neighborhood) {
      double neighborSolution_fitness = calculate_gte_metafeatures(neighbor.fitness, lambda, z_point);
      if(neighborSolution_fitness < currentSolution_fitness){
        improving_neighbors_count++; // Improving neighbors (in_*) 
      }

      //Getting the best objective values to update the z_point later
      best_cost = max(z_point.first, neighbor.fitness.first);
      best_power = max(z_point.second, neighbor.fitness.second);

      double proportional_difference = abs(currentSolution_fitness - neighborSolution_fitness) / currentSolution_fitness;
      total_difference += proportional_difference;
    }

    double mean_fitness_difference = total_difference / neighborhood.size();

    // Storing the average fitness difference (fd_*) and the count of improved neighbors (in_*) - already normalized in line 83 - in the landscape
    landscape.fitness_differences.push_back(mean_fitness_difference);

    double normalized_improving_neighbors = static_cast<double>(improving_neighbors_count) / neighborhood.size();
    landscape.improving_neighbors_count.push_back(normalized_improving_neighbors);

    //Z-point update
    z_point.first = best_cost;
    z_point.second = best_power;

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    currentSolution = random_neighbor;
  }
}
