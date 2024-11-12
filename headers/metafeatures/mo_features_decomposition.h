#ifndef MO_METAFEATURES_H
#define MO_METAFEATURES_H

#include <vector>
#include "../../modules/headers/generate_rSolution.h"
#include "./landscapeMetrics.h"

vector<double> mo_features_extraction(std::vector<LandscapeMetrics> landscapes_vector);

#endif 
