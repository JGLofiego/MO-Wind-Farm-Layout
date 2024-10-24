#ifndef ADAPTATIVE_WALK_H
#define ADAPTATIVE_WALK_H

#include "walks_common.h"
#include <vector>
#include <utility>

std::vector<LandscapeElement> adaptive_walk(int number_of_neighbors, std::pair<double, double> &lambda, std::pair<double, double> &global_z_point, double &max, double &min);

#endif 