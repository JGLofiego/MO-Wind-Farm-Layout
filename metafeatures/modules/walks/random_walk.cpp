#include <vector>
#include <utility>
#include <iostream>

#include "../../../headers/metafeatures/landscapeElement.h"
#include "../../../headers/metafeatures/decomposition_based/tchebycheff_metafeatures.h"
#include "../../../headers/metafeatures/walks/random_walk.h"
#include "../../../headers/metafeatures/decomposition_based/get_neighborhood.h"
#include "../../../modules/headers/population.h"
#include "../../../headers/metafeatures/features_extraction.h"

using namespace std;

extern int* countReval;
extern int mode, defaultDecompPace, defaultDomPace;
extern vector<vector<LandscapeElement>> *updated_mult_walk;
extern vector<LandscapeElement> *updated_single_walk;

vector<LandscapeElement> random_walk(int walk_lenght, int number_of_neighbors, pair<double, double> &lambda, std::pair<double, double> &global_z_point, double &max, double &min){

  vector<LandscapeElement> S;
  updated_single_walk = &S;
  Solution current_solution = create_initial_population(1)[0];
  *countReval = *countReval + 1;

  if(mode == 0 && *countReval % defaultDecompPace == 0){
    auto result = decomposition_extraction(*updated_mult_walk);
  } else if (mode == 1 && *countReval % defaultDomPace == 0){
    auto result = dominance_extraction(*updated_single_walk);
  }

  for(int step = 0; step < walk_lenght; step++){
    LandscapeElement element;
    element.current_solution = current_solution; //Adding the 'current_solution' to S

    //Building the neighborhood of the current solution
    vector<Solution> neighborhood = get_neighborhood(current_solution, number_of_neighbors);
    element.neighborhod = neighborhood; //Adding the neighborhood of 'current_solution' to S

    calculate_decomp_metrics(element);
    calculate_dominance_metrics(element);

    S.push_back(element);

    //Getting a random neighbor of the neighborhood of the current solution
    Solution random_neighbor = neighborhood[rand() % neighborhood.size()];

    current_solution = random_neighbor;
  }

  return S;
}
