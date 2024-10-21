#ifndef ADAPTATIVE_WALK_H
#define ADAPTATIVE_WALK_H

#include <utility>
#include "../../../headers/features/landscapeElement.h"

std::vector<LandscapeElement> adaptive_walk(int number_of_neighbors, std::pair<double, double> &lambda, int num_turb, double &max, double &min);

#endif 