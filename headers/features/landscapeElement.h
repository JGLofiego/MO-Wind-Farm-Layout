#ifndef LANDSCAPE_ELEMENT_H
#define LANDSCAPE_ELEMENT_H

#include <vector>
#include "../../modules/headers/generate_rSolution.h"

struct LandscapeElement {
  Solution current_solution;
  double tch_current_solution;
  std::vector<Solution> neighborhod;
  std::vector<double> tchebycheff_neighbors;
};

#endif 
