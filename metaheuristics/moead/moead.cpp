#include "../../modules/headers/main.h"
#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

int main(){

  //Information that must be extracted from each instance
  int num_turb = 3;
  int upperBoundX = 3;
  int upperBoundY = 3;

  //MOAED parameters 
  int size_population = 2; //Size of the population
  double probCross = 0.8;
  double probMutacao = 0.4;
  int number_of_neighbors = 3;
  int max_generations = 3;
 
  //Initial population
  vector<Solution> population = create_initial_population(size_population, num_turb, upperBoundX, upperBoundY);  

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector(size_population);  

  //Building the neighborhood (B) of each lambda vector i (or each subproblem i)
  vector<vector<int>> neighborhood = build_neighborhood(number_of_neighbors, lambda_vector, size_population);

  //z_point
  pair<double, double> z_point = get_best_z_point(population);
  
  /*s_aux = Auxiliar solution <i, TCH_i>. 
  Each element of S_aux contains an index i (to reference the lambda vector i, neighborhood i of a subproblem i) and the TCH of the subproblem i*/
  vector<pair<int, double>> s_aux(size_population);

  for(int i = 0; i < s_aux.size(); i++){
    s_aux[i].first = i;
    s_aux[i].second = calculate_gte(population[i].fitness, lambda_vector[i], z_point);
  }

  int generation = 0;

  while (generation < max_generations) {
    for (int i = 0; i < size_population; i++) {
      // Step 2.1: Reproduction
      // Randomly select two indices k and l from the neighborhood B(i)
      int k = neighborhood[i][rand() % neighborhood[i].size()];
      int l = neighborhood[i][rand() % neighborhood[i].size()];

      // Generate new solution y using genetic operators

      //Crossover
      Solution new_solution_y;
      double k = (double) rand() / RAND_MAX;

      if(k < probCross){
        new_solution_y = crossover(population[k], population[j]);
        //child2 = crossover(population[j], population[k]);
      }
      else{
        new_solution_y = population[k];
        //child2 = parents.second;
      }

      //Mutation
      k = (double) rand() / RAND_MAX;

      if(k < probMutacao){
        new_solution_y = mutation(new_solution_y);
      }

      // Step 2.3: AZ point update ============> DUVIDA!!
      z_point.first = min(z_point.first, f_y.first);
      z_point.second = min(z_point.second, f_y.second);

      // Step 2.4: Neighboring solutions update
      for (int j : neighborhood[i]) {
        if (calculate_gte(new_solution_y.fitness, lambda_vector[j], z_point) <= calculate_gte(population[j].fitness, lambda_vector[j], z_point)) {
          population[j] = new_solution_y;
          s_aux[j].second = calculate_gte(population[j].fitness, lambda_vector[j], z_point);
        }
      }
    }
    generation++;
  }
  
}