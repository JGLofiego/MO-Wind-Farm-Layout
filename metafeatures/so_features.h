#ifndef SO_METAFEATURES_H
#define SO_METAFEATURES_H

#include <vector>
#include "../modules/headers/generate_rSolution.h"
#include "../headers/features/landscapeMetrics.h"
#include "../headers/features/landscapeElement.h"

std::vector<LandscapeMetrics> so_features_extraction(std::vector<std::vector<LandscapeElement>> &landscapes);

#endif 
