#include <vector>
#include "../../../headers/features/landscapeElement.h"
#include "../../../headers/features/normalization.h"

void normalization(vector<vector<LandscapeElement>>& landscapes){
  double max = numeric_limits<double>::lowest();
  double min = numeric_limits<double>::infinity();

  for(auto& landscape : landscapes){
    for(auto& element : landscape){
      if(element.tch_current_solution < min){
        min = element.tch_current_solution;
      }
      if(element.tch_current_solution > max){
        max = element.tch_current_solution;
      }
      for(auto& neighbor : element.tchebycheff_neighbors){
        if(neighbor < min){
          min = neighbor;
        }
        if(neighbor > max){
          max = neighbor;
        }
      }
    }
  }

  for(auto& landscape : landscapes){
    for(auto& element : landscape){
      element.tch_current_solution = (element.tch_current_solution - min) / (max - min);

      for(auto& neighbor : element.tchebycheff_neighbors){
        neighbor = (neighbor - min) / (max - min);
      }
    }
  }

}