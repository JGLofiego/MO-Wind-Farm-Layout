#include <utility>
#include <vector>
#include <iostream>
#include <ctime> 
#include <algorithm> 
#include "../../modules/headers/population.h"
#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/generate_weight_vectors.h"
#include "../../modules/headers/generate_neighborhood.h"
#include "../../modules/headers/get_best_z_point.h"
#include "../../modules/headers/tchebycheff.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/crossover.h"

using namespace std;

bool dominates(Solution solutionA, Solution solutionB){
  return (solutionA.fitness.first <= solutionB.fitness.first && solutionA.fitness.second >= solutionB.fitness.second) && (solutionA.fitness.first < solutionB.fitness.first || solutionA.fitness.second > solutionB.fitness.second);
}

vector<Solution> moead(int num_turb, float& wind, float& power, float& thrust_coef, float& angle, vector<double> *&costs, vector<Foundation> *&foundations){

  //srand(time(0)); //Initializing the random number generator 

  //MOAED parameters 
  int size_population = 10; //Size of the population
  double probCross = 0.8;
  double probMutacao = 0.4;
  int number_of_neighbors = 5;
  int max_generations = 3;
 
  //Initial population
  vector<Solution> population = create_initial_population(size_population, num_turb, wind, power, thrust_coef, angle, costs, foundations);  

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector(size_population); 

  //Building the neighborhood (B) of each lambda vector i (or each subproblem i)
  vector<vector<int>> neighborhood = build_neighborhood(number_of_neighbors, lambda_vector, size_population);
  
  //z_point
  pair<double, double> z_point = get_best_z_point(population);

  /*tch_vector = vector with the value of tchebycheff function to each subproblem (weight vector) i 
  Each index i of tch_vector (to reference the lambda vector i, neighborhood i of a subproblem i) contains the TCH of the subproblem i*/
  vector<double> tch_vector(size_population);

  for(int i = 0; i < tch_vector.size(); i++){
    tch_vector[i] = calculate_gte(population[i].fitness, lambda_vector[i], z_point);
  }

  // Step 1.1: Initialize EP (External Population)
  vector<Solution> EP = population;

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
      double cross_prob = (double) rand() / RAND_MAX;

      if(cross_prob < probCross){
        child1 = crossover(population[k], population[l]);
        child2 = crossover(population[l], population[k]);
      }
      else{
        child1 = population[k];
        child2 = population[l];
      }

      //Mutation
      double mutation_prob = (double) rand() / RAND_MAX;

      if(mutation_prob < probMutacao){
        mutation(child1);
        mutation(child2);
      }

      // Step 2.3: Update of z point
      z_point.first = min(z_point.first, min(child1.fitness.first, child2.fitness.first));
      z_point.second = min(z_point.second, min(child1.fitness.second, child2.fitness.second));

      // Step 2.4: Neighboring solutions update
      for (int j : neighborhood[i]) {
        double child1_tch = calculate_gte(child1.fitness, lambda_vector[j], z_point);
        if (child1_tch <= tch_vector[j]) {
          population[j] = child1;
          tch_vector[j] = child1_tch;
        }
      }
    }

    // Step 2.5: Update EP for child1
    // Remove dominated solutions from EP and add the new solution if it's not dominated
    auto it = EP.begin();
    bool flag1 = true;

    while (it != EP.end()) {
      if (dominates(child1, *it)) {
        it = EP.erase(it);  // Remove solutions dominated by child1
      } 
      else if (dominates(*it, child1)) {
        flag1 = false;
        break;  // child1 is dominated, we don't add it to EP
      } 
      else {
        ++it;
      }
    }
    if (flag1) {
      EP.push_back(child1);  // Add child1 if not dominated
    }

    // Step 2.5: Update EP for child2
    it = EP.begin();  
    bool flag2 = true;

    while (it != EP.end()) {
      if (dominates(child2, *it)) {
        it = EP.erase(it);  // Remove solutions dominated by child2
      } 
      else if (dominates(*it, child2)) {
        flag2 = false;
        break;  // child2 is dominated, we don't add it to EP
      } 
      else {
        ++it;
      }
    }
    if (flag2) {
      EP.push_back(child2);  // Add child2 if not dominated
    }

    generation++;
  }
  cout << "===================== EP =====================" << endl;

  for(auto& i : EP){
    cout << "<" << i.fitness.first << ", " << i.fitness.second << ">" << endl;
  }

  return EP;
}