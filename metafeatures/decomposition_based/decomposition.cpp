#include <vector>
#include <random>
#include <iostream>
#include <limits> 

#include "../../headers/metafeatures/weight_vectors_metafeatures.h"
#include "../../headers/metafeatures/tchebycheff_metafeatures.h"
#include "../../headers/metafeatures/global_z_point.h"
#include "../../headers/metafeatures/get_neighborhood.h"
#include "../../headers/metafeatures/random_walk.h"
#include "../../headers/metafeatures/adaptative_walk.h"
#include "../../headers/metafeatures/normalization.h"
#include "../../headers/metafeatures/so_features_decomposition.h"
#include "../../headers/metafeatures/mo_features_decomposition.h"

#include "../../headers/metafeatures/landscapeMetrics.h"
#include "../../headers/metafeatures/landscapeElement.h"

#include "../../headers/utils/features_csv.h"

void mo_features_extraction_decomposition(int qtd_of_landscapes, int walk_lenght, int number_of_neighbors){

  //Building the lambda vector, ie, the vector of weights to each subproblem i
  vector<pair<double, double>> lambda_vector = build_weight_vector_metafeatures(qtd_of_landscapes);

  //Building a landscape for each subproblem
  vector<vector<LandscapeElement>> landscapes_random_walk(qtd_of_landscapes);
  vector<vector<LandscapeElement>> landscapes_adaptative_walk(qtd_of_landscapes);

  //Getting the min and max values of all solutions x, ie, {max/min(F(x)) | 'x' in landscapes}
  double max = numeric_limits<double>::lowest();
  double min = numeric_limits<double>::infinity();

  //Getting the global z_point
  pair<double, double> global_z_point = get_global_z_point();

  for(int i = 0; i < qtd_of_landscapes; i++){
    //Landscape i refers to the landscape of the subproblem i
    //lambda_vector i refers to the weight vector of the subproblem i
    landscapes_random_walk[i] = random_walk(walk_lenght, number_of_neighbors, lambda_vector[i], global_z_point, max, min);
    landscapes_adaptative_walk[i] = adaptive_walk(number_of_neighbors, lambda_vector[i], global_z_point, max, min);
  }

  //Normalizing the landscapes elements
  normalization(landscapes_random_walk, max, min);
  normalization(landscapes_adaptative_walk, max, min);

  //Getting the metrics (single objective features) of each landscape of each type (random walk and adaptative walk)
  auto random_wak_so_features = so_features_extraction(landscapes_random_walk);
  auto adaptative_walk_so_features = so_features_extraction(landscapes_adaptative_walk);

  //Getting the multiobjective features of each landscape of each type (random walk and adaptative walk)
  auto random_wak_mo_features = mo_features_extraction(random_wak_so_features);
  auto adaptative_walk_mo_features = mo_features_extraction(adaptative_walk_so_features);

  //Buiding the csv
  build_csv(random_wak_mo_features, "mo_features_random_walk_decomposition.csv");
  build_csv(adaptative_walk_mo_features, "mo_features_adaptative_walk_decomposition.csv");
}