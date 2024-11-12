#include <vector>
#include <random>
#include <iostream>
#include <limits> 

#include "../headers/metafeatures/weight_vectors_metafeatures.h"
#include "../headers/metafeatures/tchebycheff_metafeatures.h"
#include "../headers/metafeatures/global_z_point.h"
#include "../headers/metafeatures/get_neighborhood.h"
#include "../headers/metafeatures/random_walk.h"
#include "../headers/metafeatures/adaptative_walk.h"
#include "../headers/metafeatures/normalization.h"

#include "../headers/metafeatures/metrics_extraction.h"
#include "../headers/metafeatures/mo_features_decomposition.h"
#include "../headers/metafeatures/mo_features_pareto.h"

#include "../headers/metafeatures/landscapeMetrics.h"
#include "../headers/metafeatures/landscapeElement.h"

#include "../headers/utils/features_csv.h"

vector<string> column_names_decomp = {
      "FV_avg_avg", "FV_avg_sd", "FV_sd_avg", "FV_sd_sd", "FV_r1_avg", 
      "FV_r1_sd", "FV_kr_avg", "FV_kr_sd", "FV_sk_avg", "FV_sk_sd",
      "FD_avg_avg", "FD_avg_sd", "FD_sd_avg", "FD_sd_sd", "FD_r1_avg", 
      "FD_r1_sd", "FD_kr_avg", "FD_kr_sd", "FD_sk_avg", "FD_sk_sd",
      "IN_avg_avg", "IN_avg_sd", "IN_sd_avg", "IN_sd_sd", "IN_r1_avg", 
      "IN_r1_sd", "IN_kr_avg", "IN_kr_sd", "IN_sk_avg", "IN_sk_sd",
};

vector<string> column_names_dom = {
  "INF.avg", "INF.sd", "INF.r1", "INF.kr", "INF.sk",
  "SUP.avg", "SUP.sd", "SUP.r1", "SUP.kr", "SUP.sk",
  "INC.avg", "INC.sd", "INC.r1", "INC.kr", "INC.sk"
};

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

  //METRICS -> Getting the metrics of each landscape of each type (random walk and adaptative walk)
  auto RW_metrics = metrics_extraction(landscapes_random_walk);
  auto AW_metrics = metrics_extraction(landscapes_adaptative_walk);

  //DECOMPOSTION -> Getting the multiobjective features of each landscape of each type (random walk and adaptative walk)
  auto RW_mo_decomposition_features = mo_features_extraction(RW_metrics);
  auto AW_mo_decomposition_features = mo_features_extraction(AW_metrics);
  
  //PARETO -> Getting the multiobjective features of each landscape of each type (random walk and adaptative walk)
  auto RW_mo_pareto_features = mo_features_extraction_pareto(RW_metrics);
  auto AW_mo_pareto_features = mo_features_extraction_pareto(AW_metrics);

  //Buiding the csv
  build_csv(RW_mo_decomposition_features, column_names_decomp, "mo_features_random_walk_decomposition.csv");
  build_csv(AW_mo_decomposition_features, column_names_decomp, "mo_features_adaptative_walk_decomposition.csv");

  build_csv(RW_mo_pareto_features, column_names_dom, "mo_features_random_walk_dominance.csv");
  build_csv(AW_mo_pareto_features, column_names_dom, "mo_features_adaptative_walk_dominance.csv");
}