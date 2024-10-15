#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <vector>

struct Landscape {
  std::vector<double> fitness_values; // Stores the fitness values ​​obtained during the walk
  std::vector<double> fitness_differences; // Stores the fitness differences between solutions and their neighbors
  std::vector<double> improving_neighbors_count; // Stores the number of neighbors that improve the solution
};

#endif 
