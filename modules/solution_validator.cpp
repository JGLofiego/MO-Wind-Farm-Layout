#include "../modules/headers/generate_rSolution.h"
using namespace std;

bool isValid(Solution &solution){

  for(int zone = 0; zone < num_zones; zone++){

    //Checking if the number of turbines in each zone is correct

    //Checking if each turbine in the grid is correct (according to foundations)

    for(int i = 0; i < solution.turbines[zone].size(); i++){
      int index_foundation = solution.turbines[zone][i].index;
      int turbine_id_grid = solution.grid[zone][index_foundation];
      int turbine_id = solution.turbines[zone][i].id;
      if(!(turbine_id_grid == turbine_id)){
        return false;
      }
    }

    //Checking if there are two turbines in the same position (x, y)
    for(int i = 0; i < solution.turbines[zone].size(); i++){
      for(int j = 0; j < solution.turbines[zone].size(); j++){
        if(i != j){
          if((solution.turbines[zone][i].index == solution.turbines[zone][j].index) ||
             (solution.turbines[zone][i].x == solution.turbines[zone][j].x) && (solution.turbines[zone][i].y == solution.turbines[zone][j].y)){
            return false;
          }
        }
      }
    }

    //Cheking if the index of each turbine in foundations corresponds to its position (x,y)

  }

  return true;
}