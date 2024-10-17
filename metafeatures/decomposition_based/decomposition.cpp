#include <vector>
#include <random>
#include <iostream>
#include <limits> 

#include "./headers/weight_vectors_metafeatures.h"
#include "./headers/tchebycheff_metafeatures.h"
#include "./headers/z_point_metafeatures.h"

#include "../headers/landscape.h"

#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/isEqual.h"
#include "../../modules/headers/population.h"

bool isEqualNeighborhood(Solution &new_neighbor, vector<Solution> &neighborhood ){
  for(auto &solution : neighborhood){
    if(isEqual(new_neighbor, solution)){
      return true;
    }
  }
  return false;
}

vector<Solution> get_neighborhood(Solution &currentSolution, int number_of_neighbors){
  vector<Solution> neighborhood;
  Solution new_neighbor = currentSolution;

  for(int i = 0; i < number_of_neighbors; i++){
 
    mutation(new_neighbor);
    //WARNING: RISK OFF INFINITE LOOP
    while(isEqualNeighborhood(new_neighbor, neighborhood)){
      new_neighbor = currentSolution;
      mutation(new_neighbor);
    }

    neighborhood.push_back(new_neighbor);
  }

  return neighborhood;
} 

void randomWalk(Landscape &landscape, int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, int num_turb){

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

void adaptiveWalk(Landscape &landscape, int number_of_neighbors, pair<double, double> &lambda, pair<double, double> &z_point, int num_turb) {
    Solution currentSolution = create_initial_population(1, num_turb)[0];
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

vector<Landscape> landscapes_decomposition(int population_size){

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector_metafeatures(population_size);

  //Building a landscape for each subproblem
  vector<Landscape> landscapes(population_size);

  for(int i = 0; i < landscapes.size(); i++){
    //Landscape i refers to the landscape of the subproblem i
    //lambda_vector i refers to the weight vector of the subproblem i
    randomWalk(landscapes[i], 8, 5, lambda_vector[i], 26);
  }

  cout << "========================== LANDSCAPES ==========================" << endl;

  cout << "------- " << "FITNESS DIFFERENCE " << "-------" << endl;

  for(int i = 0; i < landscapes.size(); i++){
    cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
    cout << "[";
    for(int j = 0; j < landscapes[i].fitness_differences.size(); j++){
      cout << landscapes[i].fitness_differences[j] << ",";
    }
    cout << "]" << endl << endl;
  }

  cout << "------- " << "FITNESS VALUES " << "-------" << endl;

  for(int i = 0; i < landscapes.size(); i++){
    cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
    cout << "[";
    for(int j = 0; j < landscapes[i].fitness_values.size(); j++){
      cout << landscapes[i].fitness_values[j] << ",";
    }
    cout << "]" << endl << endl;
  }

    cout << "------- " << "IMPROVING NEIGHBORS " << "-------" << endl;

  for(int i = 0; i < landscapes.size(); i++){
    cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
    cout << "[";
    for(int j = 0; j < landscapes[i].improving_neighbors_count.size(); j++){
      cout << landscapes[i].improving_neighbors_count[j] << ",";
    }
    cout << "]" << endl << endl;
  }

  return landscapes;
}