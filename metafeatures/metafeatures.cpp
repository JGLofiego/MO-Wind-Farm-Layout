#include <vector>
#include <random>
#include "./headers/weight_vectors_metafeatures.h"
#include "./headers/tchebycheff_metafeatures.h"
#include "./headers/z_point_metafeatures.h"

#include "../modules/headers/generate_rSolution.h"
#include "../modules/headers/mutation.h"
#include "../modules/headers/isEqual.h"
#include "../modules/headers/population.h"

// #include "./modules/weight_vectors_metafeatures.cpp"
// #include "./modules/tchebycheff_metafeatures.cpp"
// #include "./modules/get_best_z_point.cpp"

// #include "../modules/generate_initial_population/generate_random_solution/generate_rSolution.cpp"
// #include "../modules/generate_initial_population/generate_population/population.cpp"
// #include "../modules/genetic_operators/mutation/mutation.cpp"
// #include "../metaheuristics/general_modules/isEqual.cpp"

struct Landscape {
  vector<double> fitness_values; // Stores the fitness values ​​obtained during the walk
  vector<double> fitness_differences; // Stores the fitness differences between solutions and their neighbors
  vector<int> improving_neighbors_count; // Number of neighbors that improve the solution
};

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

    while(isEqualNeighborhood(new_neighbor, neighborhood)){
      new_neighbor = currentSolution;
      mutation(new_neighbor);
    }

    neighborhood.push_back(new_neighbor);
  }

  return neighborhood;
} 

void randomWalk(Landscape &landscape, int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, pair<double, double> &z_point, int num_turb){

  Solution currentSolution = create_initial_population(1, num_turb)[0];
  vector<double> fitness_values;
  vector<double> fitness_differences;
  
  for(int step = 0; step < walk_lenght; step++){
    //Getting the value of tchebycheff function for the current solution 
    double currentSolution_fitness = calculate_gte_metafeatures(currentSolution.fitness, lambda, z_point);

    //Z-point update
    z_point.first = max(z_point.first, max(currentSolution.fitness.first, currentSolution.fitness.first));

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(currentSolution, number_of_neighbors);

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    // Storing the fitness value (fv_*) in the landscape
    landscape.fitness_values.push_back(currentSolution_fitness);

    // Fitness difference (fd_*) and Improving neighbors (in_*) 
    double total_difference = 0.0;
    int improving_neighbors_count = 0;

    for (Solution& neighbor : neighborhood) {
      double neighborSolution_fitness = calculate_gte_metafeatures(neighbor.fitness, lambda, z_point);
      if(neighborSolution_fitness < currentSolution_fitness){
        improving_neighbors_count++; // Improving neighbors (in_*) 
      }
      total_difference += (currentSolution_fitness - neighborSolution_fitness);
    }

    double mean_fitness_difference = total_difference / neighborhood.size();

    // Storing the average fitness difference (fd_*) and the count of improved neighbors (in_*) in the landscape
    landscape.fitness_differences.push_back(mean_fitness_difference);
    landscape.improving_neighbors_count.push_back(improving_neighbors_count);

    currentSolution = random_neighbor;
  }
}

void metafeatures_extraction(vector<Solution> population){

  cout << "========================= INITIAL POPULATION =========================" << endl;

  for(int i = 0; i < population.size(); i++){
    cout << "<" << population[i].fitness.first * (-1) << ", " << population[i].fitness.second << ">" << endl;
  }

  cout << endl;
  
  /* 
  =================================================================
  ====== 2.2.1 First Step: Decomposicalculate_gte_metafeaturestion using Weight Vectors ===== 
  =================================================================  */

  int population_size = population.size();

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector_metafeatures(population_size);

  cout << "========================= WEIGH VECTOR =========================" << endl;

  for(int i = 0; i < lambda_vector.size(); i++){
    cout << "<" << lambda_vector[i].first << ", " << lambda_vector[i].second << ">" << endl;
  }

  cout << endl;

  //Step 1.4: z_point
  pair<double, double> z_point = get_z_point_metafeatures(population);

  cout << "========================= Z POINT =========================" << endl;
  cout << "<" << z_point.first *(-1) << ", " << z_point.second << ">" << endl << endl;

  /*tch_vector = vector with the value of tchebycheff function to each subproblem (weight vector) i 
  Each index i of tch_vector (to reference the lambda vector i, neighborhood i of a subproblem i) contains the TCH of the subproblem i*/
  vector<double> tch_vector(population_size);

  for(int i = 0; i < tch_vector.size(); i++){
    tch_vector[i] = calculate_gte_metafeatures(population[i].fitness, lambda_vector[i], z_point);
  }

  //!!!!!! What defines a subproblem? Is it it's tchebycheff value and weight vector?

  //Building a landscape for each subproblem
  vector<Landscape> landscapes(population_size);

  for(int i = 0; i < landscapes.size(); i++){
    randomWalk(landscapes[i], 8, 5, lambda_vector[i], z_point, 26);
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
}