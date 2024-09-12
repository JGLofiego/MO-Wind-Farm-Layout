#include "../../headers/generate_rSolution.h"
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

void mutation(Solution &solution){

    int grid_size = solution.grid.size();
    int rand_intA, rand_intB;
    int indexA = -1;
    int indexB = -1;

    // Select two positions at random
    // Ensure that rand_intA and rand_intB are different and both are not a available position
    do{
      rand_intA = rand() % grid_size;
      rand_intB = rand() % grid_size;
    } while(rand_intA == rand_intB || (solution.grid[rand_intA] == 0 && solution.grid[rand_intB] == 0));

    // Swapping the genes between grid[rand_intA] e grid[rand_intB]
    int geneA = solution.grid[rand_intA];
    int geneB = solution.grid[rand_intB];

    if(solution.grid[rand_intA] != 0){
      indexA = find_index(solution.turbines, solution.grid[rand_intA]);
    }

    if(solution.grid[rand_intB] != 0){
      indexB = find_index(solution.turbines, solution.grid[rand_intB]);
    }

    if(indexA != -1 && indexB != -1){
      int index;
      double x, y;

      index = solution.turbines[indexA].index;
      x = solution.turbines[indexA].x;
      y = solution.turbines[indexA].y;

      solution.turbines[indexA].index = solution.turbines[indexB].index;
      solution.turbines[indexA].x = solution.turbines[indexB].x;
      solution.turbines[indexA].y = solution.turbines[indexB].y;

      solution.turbines[indexB].index = index;
      solution.turbines[indexB].x = x;
      solution.turbines[indexB].y = y;
    } else if (indexA != -1 && indexB == -1){
      solution.turbines[indexA].index = rand_intB;
      solution.turbines[indexA].x = (*solution.foundations)[rand_intB].x;
      solution.turbines[indexA].y = (*solution.foundations)[rand_intB].y;
    } else {
      solution.turbines[indexB].index = rand_intA;
      solution.turbines[indexB].x = (*solution.foundations)[rand_intA].x;
      solution.turbines[indexB].y = (*solution.foundations)[rand_intA].y;
    }

    solution.grid[rand_intA] = geneB;
    solution.grid[rand_intB] = geneA;

    calculate_cost(solution);
    calculate_power(solution);
}