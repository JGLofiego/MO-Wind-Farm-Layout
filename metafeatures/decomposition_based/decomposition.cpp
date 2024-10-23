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
#include "../so_features.h"
#include "../extraction.h"

#include "../../modules/headers/generate_rSolution.h"
#include "../../modules/headers/mutation.h"
#include "../../modules/headers/isEqual.h"
#include "../../modules/headers/population.h"

pair<vector<vector<LandscapeElement>>, vector<vector<LandscapeElement>>> landscapes_decomposition(int population_size){

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector_metafeatures(population_size);

  //Building a landscape for each subproblem
  vector<vector<LandscapeElement>> landscapes_random_walk(population_size);
  vector<vector<LandscapeElement>> landscapes_adaptative_walk(population_size);

  //Getting the min and max values of all solutions x, ie, {max/min(F(x)) | 'x' in landscapes}

  double max = numeric_limits<double>::lowest();
  double min = numeric_limits<double>::infinity();

  for(int i = 0; i < landscapes_random_walk.size(); i++){
    //Landscape i refers to the landscape of the subproblem i
    //lambda_vector i refers to the weight vector of the subproblem i
    landscapes_random_walk[i] = random_walk(8, 5, lambda_vector[i], max, min);
    landscapes_adaptative_walk[i] = adaptive_walk(5, lambda_vector[i], max, min);
  }

  normalization(landscapes_random_walk, max, min);
  normalization(landscapes_adaptative_walk, max, min);

  auto random_wak_so_features = so_features_extraction(landscapes_random_walk);
  auto adaptative_walk_so_features = so_features_extraction(landscapes_adaptative_walk);

  metafeatures_extraction(adaptative_walk_so_features);

  pair<vector<vector<LandscapeElement>>, vector<vector<LandscapeElement>>> landscapes;
  landscapes.first = landscapes_random_walk;
  landscapes.second = landscapes_adaptative_walk;

  return landscapes;
}