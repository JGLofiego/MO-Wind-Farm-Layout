#ifndef ADAPTATIVE_WALK_H
#define ADAPTATIVE_WALK_H

#include "walks_common.h"

std::vector<LandscapeElement> adaptive_walk(int number_of_neighbors, std::pair<double, double> &lambda, double &max, double &min);

#endif 