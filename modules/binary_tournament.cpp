#include "../headers/generate_rSolution.h"
#include "../headers/binary_tournament.h"

#include <utility>

pair<Solution, Solution> binary_tornament(Solution& ParentX, Solution& ParentY, Solution& ParentW, Solution& ParentZ){
  pair<Solution, Solution> parents;

  //Choosing the solution that is better in the first objective
  if(ParentX.fitness.first >= ParentY.fitness.first) parents.first = ParentX;
  else parents.first = ParentY;

  //Choosing the solution that is better in the second objective
  if(ParentW.fitness.second >= ParentZ.fitness.second) parents.second = ParentW;
  else parents.second = ParentZ;

  return parents;
}