#include <vector>
#include <utility>
#include <iostream>
#include "../headers/non_dominated_sorting.h"

//Check if a SolutionA dominates a SolutionB
bool dominates(Solution solutionA, Solution solutionB){
  return (solutionA.fitness.first >= solutionB.fitness.first && solutionA.fitness.second >= solutionB.fitness.second) && (solutionA.fitness.first > solutionB.fitness.first || solutionA.fitness.second > solutionB.fitness.second);
}

//Building the fronts
vector<vector<Solution>> non_dominated_sorting(vector<Solution>& solutions){
  vector<vector<Solution>> fronts;

  while (!solutions.empty()) { //Run until all the solutions are classified
    vector<Solution> front;
    vector<int> to_remove_indices;

    // For each solution in 'solutions', check if it is not dominated by any other
    for (int i = 0; i < solutions.size(); ++i) {
      bool is_dominated = false;

      // Check if the current solution is dominated by any other solution in the set
      for (int j = 0; j < solutions.size(); ++j) {
        if (i != j && dominates(solutions[j], solutions[i])) {
          is_dominated = true;
          break;
        }
      }

      // If the solution is not dominated, it belongs to the current front
      if (!is_dominated) {
        front.push_back(solutions[i]);
        to_remove_indices.push_back(i); // Marke the index to remove later
      }
    }

    // Remove all solutions added to the current front, starting with the highest indices
    // This ensures that the removal does not change the positions of other solutions
    for (int k = to_remove_indices.size() - 1; k >= 0; --k) {
      solutions.erase(solutions.begin() + to_remove_indices[k]);
    }

    // Add the current front to the list of fronts
    fronts.push_back(front);
  }

  return fronts;
}