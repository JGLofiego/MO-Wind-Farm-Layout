#include "../../headers/population.h"
#include "../../headers/mutation.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

int find_index(vector<Turbine> &vec, int value){
  for(int i = 0; i < vec.size(); i++){
    if(vec[i].id == value){
      return i;
    }
  }

  return -1;
}

void mutationAux(Solution &solution, int zona){

    int grid_size = solution.grid[zona].size();
    int rand_intA, rand_intB;
    int indexA = -1;
    int indexB = -1;

    // Select two positions at random
    // Ensure that rand_intA and rand_intB are different and both are not a available position
    do{
      rand_intA = rand() % grid_size;
      rand_intB = rand() % grid_size;
    } while(rand_intA == rand_intB || (solution.grid[zona][rand_intA] == 0 && solution.grid[zona][rand_intB] == 0));

    // Swapping the genes betwen grid[rand_intA] e grid[rand_intB]
    int geneA = solution.grid[zona][rand_intA];
    int geneB = solution.grid[zona][rand_intB];

    if(solution.grid[zona][rand_intA] != 0){
      indexA = find_index(solution.turbines[zona], solution.grid[zona][rand_intA]);
    }

    if(solution.grid[zona][rand_intB] != 0){
      indexB = find_index(solution.turbines[zona], solution.grid[zona][rand_intB]);
    }

    if(indexA != -1 && indexB != -1){
      int index;
      double x, y;

      index = solution.turbines[zona][indexA].index;
      x = solution.turbines[zona][indexA].x;
      y = solution.turbines[zona][indexA].y;

      solution.turbines[zona][indexA].index = solution.turbines[zona][indexB].index;
      solution.turbines[zona][indexA].x = solution.turbines[zona][indexB].x;
      solution.turbines[zona][indexA].y = solution.turbines[zona][indexB].y;

      solution.turbines[zona][indexB].index = index;
      solution.turbines[zona][indexB].x = x;
      solution.turbines[zona][indexB].y = y;
    } else if (indexA != -1 && indexB == -1){
      solution.turbines[zona][indexA].index = rand_intB;
      solution.turbines[zona][indexA].x = foundations[zona][rand_intB].x;
      solution.turbines[zona][indexA].y = foundations[zona][rand_intB].y;
    } else {
      solution.turbines[zona][indexB].index = rand_intA;
      solution.turbines[zona][indexB].x = foundations[zona][rand_intA].x;
      solution.turbines[zona][indexB].y = foundations[zona][rand_intA].y;
    }

    solution.grid[zona][rand_intA] = geneB;
    solution.grid[zona][rand_intB] = geneA;
}

void mutation(Solution &solution){
  for(int i = 0; i < num_zones; i++){
    mutationAux(solution, i);
  }

  calculate_cost(solution);
  calculate_power(solution);
}