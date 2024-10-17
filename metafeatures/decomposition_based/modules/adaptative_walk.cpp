#include <vector>
#include <utility>
#include "../headers/adaptative_walk.h"
#include "../../../headers/features/landscape.h"
#include "../headers/tchebycheff_metafeatures.h"
#include "../../../modules/headers/population.h"
#include "../headers/get_neighborhood.h"

using namespace std;

void adaptive_walk(Landscape &landscape, int number_of_neighbors, pair<double, double> &lambda, int num_turb) {
  Solution currentSolution = create_initial_population(1, num_turb)[0];

  //Definition of z_point
  pair<double, double> z_point;
  z_point.first = currentSolution.fitness.first;
  z_point.second = currentSolution.fitness.second;

  vector<double> fitness_values;
  vector<double> fitness_differences;

  while (true) {
    double currentSolution_fitness = calculate_gte_metafeatures(currentSolution.fitness, lambda, z_point);
    // Storing the fitness value (fv_*) in the landscape
    landscape.fitness_values.push_back(currentSolution_fitness);

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(currentSolution, number_of_neighbors);
      
    //Finding the best neighbor and calculating its fitness
    double best_neighbor_fitness = numeric_limits<double>::infinity();
    int index_best_neighbor;

    // Fitness difference (fd_*) and Improving neighbors (in_*) 
    double total_difference = 0.0;
    int improving_neighbors_count = 0;
    double best_cost, best_power;   

    for(int i = 0; i < neighborhood.size(); i++){
      double neighborSolution_fitness = calculate_gte_metafeatures(neighborhood[i].fitness, lambda, z_point);
      if(neighborSolution_fitness < best_neighbor_fitness){
        best_neighbor_fitness = neighborSolution_fitness;
        index_best_neighbor = i;
        improving_neighbors_count++;
      }

      //Getting the best objective values to update the z_point later
      best_cost = max(z_point.first, neighborhood[i].fitness.first);
      best_power = max(z_point.second, neighborhood[i].fitness.second);

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

    if(best_neighbor_fitness < currentSolution_fitness){
      currentSolution = neighborhood[index_best_neighbor];
    } else{
      break;
    }
       
  }
}
