#include <vector>
#include <iostream>
#include "../headers/generate_neighborhood.h"
using namespace std;

vector<vector<int>> build_neighborhood(int number_of_neighbors, vector<pair<double, double>>& lambda_vector, int size_population){

  /*Contains all the indices of the neighbors of a given lambda vector i.
  Ex: for lambda vector (subproblem) i, there is a neighbor vector, i.e. a vector of neighboring indices j*/
  vector<vector<int>> neighborhood; 

  //The number of neighbors cannot be greater than the population size minus 1.
  if (number_of_neighbors > size_population-1) {
    throw runtime_error("ERROR - MOEAD:generate_neighbood ==> The number of neighbors cannot be greater than the population size minus 1.");
  }

  //Building the neighborhood of a lambda vector (subproblem) i by fingind the 't' nearest neighbors of i. t = number_of_neighbors
  for(size_t i = 0; i < lambda_vector.size(); i++){
    vector<int> nearest_neighbors;

    //Initialize the left and right indexes
    int left = i - 1;
    int right = i + 1;

    for(int j = 0; j < number_of_neighbors; j++){
      //Toggle between adding the predecessor and successor
      if (j % 2 == 0 && left >= 0) {
        nearest_neighbors.push_back(left--);
      } else if (right < lambda_vector.size()) { //Add successors even when there are no predecessors (left == 0)
        nearest_neighbors.push_back(right++);
      } else if (left >= 0) { //If successors run out, add more predecessors
        nearest_neighbors.push_back(left--);
      }
    }

    neighborhood.push_back(nearest_neighbors);
  }  

  return neighborhood;
}