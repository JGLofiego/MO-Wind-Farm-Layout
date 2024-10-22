#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include <vector>
#include <utility>

#include "../../../headers/features/landscapeElement.h"
#include "../../../headers/features/landscape.h"

std::vector<LandscapeElement> random_walk(int walk_lenght, int number_of_neighbors, std::pair<double, double> &lambda, double &max, double &min);

#endif 