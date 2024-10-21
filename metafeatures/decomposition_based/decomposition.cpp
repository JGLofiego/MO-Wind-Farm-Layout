#include <vector>
#include <random>
#include <iostream>
#include <limits> 

#include "./headers/weight_vectors_metafeatures.h"
#include "./headers/random_walk.h"
#include "./headers/tchebycheff_metafeatures.h"
#include "./headers/z_point_metafeatures.h"
#include "./headers/get_neighborhood.h"
#include "./headers/adaptative_walk.h"

#include "../../headers/features/landscape.h"
#include "../../headers/features/normalization.h"
#include "../../headers/features/landscapeElement.h"

#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/isEqual.h"
#include "../../modules/headers/population.h"

vector<vector<LandscapeElement>> landscapes_decomposition(int population_size){

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector_metafeatures(population_size);

  //Building a landscape for each subproblem
  vector<vector<LandscapeElement>> landscapes(population_size);

  // for(int i = 0; i < landscapes.size(); i++){
  //   //Landscape i refers to the landscape of the subproblem i
  //   //lambda_vector i refers to the weight vector of the subproblem i
  //   // landscapes[i] = random_walk(8, 5, lambda_vector[i], 26);
  //   landscapes[i] = adaptive_walk(5, lambda_vector[i], 26);
  // }
  landscapes[0] = adaptive_walk(5, lambda_vector[0], 26);


  // cout << "BEFORE NORMALIZATION" << endl << endl;

  for(int i = 0; i < 1; i++){
    cout << "=============== LANDSCAPE " << i << " ===============" << endl << endl;
    for(int j = 0; j < landscapes[0].size(); j++){
      cout << "TCH CURRENT SOLUTION: " << landscapes[0][j].tch_current_solution << endl;
      for(int k = 0; k < landscapes[0][j].tchebycheff_neighbors.size(); k++){
        cout << "TCH NEIGHBOR " << k << ": " << landscapes[0][j].tchebycheff_neighbors[k] << endl;
      }cout << endl;
    } cout << endl;
  }

  // normalization(landscapes);

  // cout << "AFTER NORMALIZATION" << endl << endl;

  // for(int i = 0; i < 1; i++){
  //   cout << "=============== LANDSCAPE " << i << " ===============" << endl << endl;
  //   for(int j = 0; j < landscapes[0].size(); j++){
  //     cout << "TCH CURRENT SOLUTION: " << landscapes[0][j].tch_current_solution << endl;
  //     for(int k = 0; k < landscapes[0][j].tchebycheff_neighbors.size(); k++){
  //       cout << "TCH NEIGHBOR " << k << ": " << landscapes[0][j].tchebycheff_neighbors[k] << endl;
  //     }cout << endl;
  //   } cout << endl;
  // }

  // for(int i = 0; i < landscapes.size(); i++){
  //   cout << "=============== LANDSCAPE " << i << " ===============" << endl << endl;
  //   cout << "AMOUNT OF ELEMENTS: " << landscapes[i].size() << endl;
  //   for(int j = 0; j < landscapes[i].size(); j++){
  //     cout << "TCH CURRENT SOLUTION: " << landscapes[i][j].tch_current_solution << endl;
  //     // cout << "CURRENT SOLUTION FIT: " << landscapes[i][j].current_solution.fitness.first << ", " << landscapes[i][j].current_solution.fitness.second <<  endl;
  //     for(int k = 0; k < landscapes[i][j].tchebycheff_neighbors.size(); k++){
  //       cout << "TCH NEIGHBOR " << k << ": " << landscapes[i][j].tchebycheff_neighbors[k] << endl;
  //       // cout << "NEIGHBOR FIT: " << landscapes[i][j].neighborhod[k].fitness.first << ", " << landscapes[i][j].neighborhod[k].fitness.second <<  endl;
  //     }cout << endl;
  //   } cout << endl;
  // }

  // cout << "========================== LANDSCAPES ==========================" << endl;

  // cout << "------- " << "FITNESS DIFFERENCE " << "-------" << endl;

  // for(int i = 0; i < landscapes.size(); i++){
  //   cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
  //   cout << "[";
  //   for(int j = 0; j < landscapes[i].fitness_differences.size(); j++){
  //     cout << landscapes[i].fitness_differences[j] << ",";
  //   }
  //   cout << "]" << endl << endl;
  // }

  // cout << "------- " << "FITNESS VALUES " << "-------" << endl;

  // for(int i = 0; i < landscapes.size(); i++){
  //   cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
  //   cout << "[";
  //   for(int j = 0; j < landscapes[i].fitness_values.size(); j++){
  //     cout << landscapes[i].fitness_values[j] << ",";
  //   }
  //   cout << "]" << endl << endl;
  // }

  //   cout << "------- " << "IMPROVING NEIGHBORS " << "-------" << endl;

  // for(int i = 0; i < landscapes.size(); i++){
  //   cout << "+++++++++ " << "LANDSCAPE " << i << "+++++++++" << endl; 
  //   cout << "[";
  //   for(int j = 0; j < landscapes[i].improving_neighbors_count.size(); j++){
  //     cout << landscapes[i].improving_neighbors_count[j] << ",";
  //   }
  //   cout << "]" << endl << endl;
  // }

  return landscapes;
}