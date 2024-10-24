#include <vector>
#include "../../../headers/features/get_neighborhood.h"
#include "../../../modules/headers/isEqual.h"
#include "../../../modules/headers/mutation.h"

bool isEqualNeighborhood(Solution &new_neighbor, vector<Solution> &neighborhood ){
  for(auto &solution : neighborhood){
    if(isEqual(new_neighbor, solution)){
      return true;
    }
  }
  return false;
}

vector<Solution> get_neighborhood(Solution &currentSolution, int number_of_neighbors){
  vector<Solution> neighborhood;
  Solution new_neighbor = currentSolution;

  for(int i = 0; i < number_of_neighbors; i++){
 
    mutation(new_neighbor);
    //WARNING: RISK OFF INFINITE LOOP
    while(isEqualNeighborhood(new_neighbor, neighborhood)){
      new_neighbor = currentSolution;
      mutation(new_neighbor);
    }

    neighborhood.push_back(new_neighbor);
  }

  return neighborhood;
} 
