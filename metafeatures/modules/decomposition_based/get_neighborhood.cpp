#include <vector>
#include <iostream>
#include "../../../headers/metafeatures/decomposition_based/get_neighborhood.h"
#include "../../../modules/headers/isEqual.h"
#include "../../../modules/headers/mutationFeature.h"
#include "../../../headers/metafeatures/features_extraction.h"


extern int* countReval;
extern int mode, defaultDecompPace, defaultDomPace;
extern vector<vector<LandscapeElement>> *updated_mult_walk;
extern vector<LandscapeElement> *updated_single_walk;


bool isEqualNeighborhood(Solution &new_neighbor, vector<Solution> &neighborhood ){
  for(auto &solution : neighborhood){
    if(isEqual(new_neighbor, solution)){
      return true;
    }
  }
  return false;
}

Solution get_neighbor(Solution &currentSolution){

  Solution new_neighbor = currentSolution;

  mutationFeature(new_neighbor);
  *countReval = *countReval + 1;

  return new_neighbor;
}

vector<Solution> get_neighborhood(Solution &currentSolution, int number_of_neighbors){
  vector<Solution> neighborhood;
  Solution new_neighbor = currentSolution;

  auto actual = *updated_mult_walk;

  for(int i = 0; i < number_of_neighbors; i++){
 
    mutationFeature(new_neighbor);
    *countReval = *countReval + 1;

    if(mode == 0 && *countReval % defaultDecompPace == 0){
      auto result = decomposition_extraction(actual);
      cout << *countReval << ". Decomposition ";
      for (double d : result){
        cout << d << " ";
      } cout << endl;
    } else if (mode == 1 && *countReval % defaultDomPace == 0){
      auto result = dominance_extraction(*updated_single_walk);
      cout << *countReval << ". Dominance: ";
      for (double d : result){
        cout << d << " ";
      } cout << endl;
    }

    //WARNING: RISK OFF INFINITE LOOP
    while(isEqualNeighborhood(new_neighbor, neighborhood)){
      new_neighbor = currentSolution;
      mutationFeature(new_neighbor);
      *countReval = *countReval + 1;

      if(mode == 0 && *countReval % defaultDecompPace == 0){
        auto result = decomposition_extraction(actual);
        cout << *countReval << ". Decomposition ";
        for (double d : result){
          cout << d << " ";
        } cout << endl;
      } else if (mode == 1 && *countReval % defaultDomPace == 0){
        auto result = dominance_extraction(*updated_single_walk);
        cout << *countReval << ". Dominance: ";
        for (double d : result){
          cout << d << " ";
        } cout << endl;
      }
    }

    neighborhood.push_back(new_neighbor);
  }

  return neighborhood;
} 
