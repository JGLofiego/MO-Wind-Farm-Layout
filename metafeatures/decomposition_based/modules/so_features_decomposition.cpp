#include <vector>
#include <utility>

#include "../../../headers/metafeatures/landscapeElement.h"
#include "../../../headers/metafeatures/landscapeMetrics.h"
#include "../../../headers/metafeatures/so_features_decomposition.h"

vector<LandscapeMetrics> so_features_extraction(vector<vector<LandscapeElement>> &landscapes){

  vector<LandscapeMetrics> landscape_so_features;

  for(const auto& landscape : landscapes){
    LandscapeMetrics landscape_metrics;

    for(const auto& element : landscape){
      double current_solution_fitness = element.tch_current_solution;
      int improving_count = 0;
      double total_difference = 0.0;

      // Storing the fitness value (fv_*) in the landscape_metrics
      landscape_metrics.fitness_values.push_back(current_solution_fitness);

      for(const auto& neighbor_fitness: element.tchebycheff_neighbors){
        if(neighbor_fitness < current_solution_fitness){
          improving_count++; // Improving neighbors (in_*) 
        }

        double difference = current_solution_fitness - neighbor_fitness;
        total_difference += difference;
      }

      // Storing the average fitness difference (fd_*) and the count of improved neighbors (in_*) in the landscape
      double avg_fitness_difference = total_difference / element.tchebycheff_neighbors.size();
      landscape_metrics.fitness_differences.push_back(avg_fitness_difference);
      
      // Normalizing the count of improved neighbors (in_*)
      double normalized_improving_neighbors = static_cast<double>(improving_count);
      if(improving_count > 0){
        normalized_improving_neighbors = static_cast<double>(improving_count) / element.tchebycheff_neighbors.size();
      }

      landscape_metrics.improving_neighbors_count.push_back(normalized_improving_neighbors);
    }

    landscape_so_features.push_back(landscape_metrics);
  }

  return landscape_so_features;
}