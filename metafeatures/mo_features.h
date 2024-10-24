#ifndef MO_METAFEATURES_H
#define MO_METAFEATURES_H

#include <vector>
#include "../modules/headers/generate_rSolution.h"
#include "../headers/features/landscape.h"

vector<double> mo_features_extraction(std::vector<Landscape> landscapes_vector);

#endif 
