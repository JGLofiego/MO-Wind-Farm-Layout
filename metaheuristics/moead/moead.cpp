#include <utility>
#include <vector>
#include <iostream>
#include <ctime> 
#include <algorithm>
#include <random>
#include "../../modules/headers/population.h"
#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/generate_weight_vectors.h"
#include "../../modules/headers/generate_neighborhood.h"
#include "../../modules/headers/get_best_z_point.h"
#include "../../modules/headers/tchebycheff.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"

#include "../../modules/headers/dominates.h"
#include "../../modules/headers/isEqual.h"

using namespace std;

vector<Solution> initializeEP(vector<Solution>& population){
  // Step 1.1: Initialize EP (External Population)
  //The EP vector will contain only the non-dominated and not equal solutions from the initial population
  vector<Solution> EP;

  for (int i = 0; i < population.size(); i++) {
    bool isDominated = false;
        
    // Check if the solution is dominated by any other solution
    for (int j = 0; j < population.size(); j++) {
      if (i != j && dominates(population[j], population[i])) {
        isDominated = true;
        break;
      }
    }

    // If the solution is not dominated, check if it is already in EP
    if (!isDominated) {
      bool alreadyInEP = false;
      
      for (const auto& sol : EP) {
        if (isEqual(sol, population[i])) {
          alreadyInEP = true;
          break;
        }
      }

      // Only add the solution if it's not already in EP
      if (!alreadyInEP) {
        EP.push_back(population[i]);
      }
    }
  }

  return EP;
}

void updateEP(vector<Solution> &EP, Solution &child1, Solution &child2){
  // Step 2.5: Update EP for child1
  // Remove dominated solutions from EP and add the new solutions (child1 e child2) if it's not dominated
  auto it = EP.begin();
  bool flag1 = true;

  while (it != EP.end()) {
    if (dominates(child1, *it)) {
      it = EP.erase(it);  // Remove solutions dominated by child1
    } 
    else {
      if (dominates(*it, child1)) {
        flag1 = false;  // Mark that child1 is dominated, keep checking
      }
      ++it;
    }
  }

  // Check if child1 is already present in EP
  bool already_exists1 = false;
  for (const auto& sol : EP) {
    if (isEqual(child1, sol)) {
      already_exists1 = true;
      break;
    }
  }

  // Add child1 to EP if it is not dominated (flag1) and not duplicated (!already_exists1)
  if (flag1 && !already_exists1) {
    EP.push_back(child1);
  }

  // Step 2.5: Update EP for child2
  it = EP.begin();
  bool flag2 = true;

  while (it != EP.end()) {
    if (dominates(child2, *it)) {
      it = EP.erase(it);  // Remove solutions dominated by child2
    } 
    else {
      if (dominates(*it, child2)) {
        flag2 = false;  // Mark that child2 is dominated, keep checking
      }
      ++it;
    }
  }

  // Check if child2 is already present in EP
  bool already_exists2 = false;
  for (const auto& sol : EP) {
    if (isEqual(child2, sol)) {
      already_exists2 = true;
      break;
    }
  }

  // Add child2 to EP if it is not dominated (flag2) and not duplicated (!already_exists2)
  if (flag2 && !already_exists2) {
    EP.push_back(child2);
  }
}

vector<Solution> moead(vector<Solution>& population){

  //Initializing the random number generator 
  default_random_engine re{(unsigned)time(nullptr)};
  uniform_real_distribution<double> dist(0.0, 1.0);

  //MOAED parameters 
  int size_population = population.size();
  double input_cross_prob = 0.8;
  double input_mutation_prob = 0.4;
  int number_of_neighbors = 5;
  int max_generations = 3;

  // Step 1.1: Initialize EP (External Population)
  //The EP vector will contain only the non-dominated and not equal solutions from the initial population
  vector<Solution> EP = initializeEP(population);

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector(size_population); 

  //Step 1.2: Building the neighborhood (B) of each lambda vector i (or each subproblem i)
  vector<vector<int>> neighborhood = build_neighborhood(number_of_neighbors, lambda_vector, size_population);
  
  //Step 1.4: z_point
  pair<double, double> z_point = get_best_z_point(population);

  /*Step 1.3: tch_vector = vector with the value of tchebycheff function to each subproblem (weight vector) i 
  Each index i of tch_vector (to reference the lambda vector i, neighborhood i of a subproblem i) contains the TCH of the subproblem i*/
  vector<double> tch_vector(size_population);

  for(int i = 0; i < tch_vector.size(); i++){
    tch_vector[i] = calculate_gte(population[i].fitness, lambda_vector[i], z_point);
  }
  
  cout << endl;
  cout << "===================== INICIAL EP  =====================" << endl << endl;

  cout << "Size of EP: " << EP.size() << endl << endl;

  for(const auto& i : EP){
    cout << "<" << i.fitness.first * (-1) << ", " << i.fitness.second << ">" << endl;
  }

  cout << endl;

  cout << "======================================================" << endl << endl;

  //Step 2: Update

  int generation = 0;

  while (generation < max_generations) {

    Solution child1, child2;

    for (int i = 0; i < size_population; i++) {

      // Step 2.1: Reproduction
      // Randomly select two indices k and l from the neighborhood B(i)
      int k = neighborhood[i][rand() % neighborhood[i].size()];
      int l = neighborhood[i][rand() % neighborhood[i].size()];

      // Generate new solution y using genetic operators

      //Crossover
      double random_cross_prob = dist(re);

      if(random_cross_prob < input_cross_prob){ 
        child1 = crossover(population[k], population[l]);
        child2 = crossover(population[l], population[k]);
      }
      else{
        child1 = population[k];
        child2 = population[l];
      }

      // Step 2.5: Update EP after crossover
      // Remove dominated solutions from EP and add the new solutions (child1 e child2) if it's not dominated
      updateEP(EP, child1, child2);
      
      //Mutation
      double random_mutation_prob = dist(re);

      if(random_mutation_prob < input_mutation_prob){
        mutation(child1);
        mutation(child2);
      }

      // Step 2.5: Update EP after mutation
      // Remove dominated solutions from EP and add the new solutions (child1 e child2) if it's not dominated
      updateEP(EP, child1, child2);

      // Step 2.3: Update of z point
      z_point.first = max(z_point.first, max(child1.fitness.first, child2.fitness.first));
      z_point.second = max(z_point.second, max(child1.fitness.second, child2.fitness.second));

      // Step 2.4: Neighboring solutions update
      for (int j : neighborhood[i]) {
        double child1_tch = calculate_gte(child1.fitness, lambda_vector[j], z_point);
        if (child1_tch <= tch_vector[j]) {
          population[j] = child1;

          tch_vector[j] = child1_tch;
        }
        
        double child2_tch = calculate_gte(child2.fitness, lambda_vector[j], z_point);
        if (child2_tch <= tch_vector[j]) {
          population[j] = child2;
          tch_vector[j] = child2_tch;
        }
      }
    }
    generation++;
  }

  cout << "====================== FINAL EP  ======================" << endl << endl;
  cout << "Size of EP: " << EP.size() << endl;
  for(auto& i : EP){
    cout << "<" << i.fitness.first * (-1) << ", " << i.fitness.second << ">" << endl;
  }

  cout << endl;

  cout << "=======================================================" << endl << endl;

  return EP;
}