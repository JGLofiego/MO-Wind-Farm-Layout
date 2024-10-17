#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include <utility>
#include "../../../headers/features/landscape.h"

void random_walk(Landscape &landscape, int walk_lenght, int number_of_neighbors, std::pair<double, double> &lambda, int num_turb);

#endif 