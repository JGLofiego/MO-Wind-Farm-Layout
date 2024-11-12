#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <string>
#include <functional>

#include "../../../headers/metafeatures/landscapeMetrics.h"
#include "../../../headers/metafeatures/mo_features_pareto.h"
#include "../../../headers/metafeatures/statistical_functions.h"

using namespace std;

vector<double> get_mo_features_pareto(vector<LandscapeMetrics> &landscapes_vector, function<vector<double>(const LandscapeMetrics&)> get_feature){
  vector<double> mo_features;
  vector<double> s_mean;
  vector<double> s_sd;
  vector<double> s_r1;
  vector<double> s_kr;
  vector<double> s_sk;

  // ================= F?_s =================
  for(auto& landscape : landscapes_vector){
    vector<double> feature = get_feature(landscape);
    s_mean.push_back(mean(feature)); //F?_avg
    s_sd.push_back(sd(feature)); //F?_sd
    s_r1.push_back(r1(feature)); //F?_r1
    s_kr.push_back(kr(feature)); //F?_kr
    s_sk.push_back(sk(feature)); //F?_sk
  }

  mo_features.push_back(mean(s_mean));
  mo_features.push_back(mean(s_sd));
  mo_features.push_back(mean(s_r1));
  mo_features.push_back(mean(s_kr));
  mo_features.push_back(mean(s_sk));

  return mo_features;
}

vector<double> mo_features_extraction_pareto(vector<LandscapeMetrics> landscapesMetrics){
  vector<double> mo_dom_features;
  vector<double> inf_neighbors_features, sup_neighbors_features, inc_neighbors_features;

  inf_neighbors_features = get_mo_features_pareto(landscapesMetrics, [](const LandscapeMetrics& landscape) { return landscape.inf_neighbors;});
  sup_neighbors_features = get_mo_features_pareto(landscapesMetrics, [](const LandscapeMetrics& landscape) { return landscape.sup_neighbors;});
  inc_neighbors_features = get_mo_features_pareto(landscapesMetrics, [](const LandscapeMetrics& landscape) { return landscape.inc_neighbors;});

  mo_dom_features = inf_neighbors_features;
  mo_dom_features.insert(mo_dom_features.end(), sup_neighbors_features.begin(), sup_neighbors_features.end());
  mo_dom_features.insert(mo_dom_features.end(), inc_neighbors_features.begin(), inc_neighbors_features.end());

  return mo_dom_features;
}