#ifndef ADAPTATIVE_WALK_H
#define ADAPTATIVE_WALK_H

#include <utility>
#include "../../../headers/features/landscape.h"

void adaptive_walk(Landscape &landscape, int number_of_neighbors, std::pair<double, double> &lambda, int num_turb);

#endif 