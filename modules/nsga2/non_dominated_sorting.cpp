#include <vector>
#include <utility>
#include <set>
#include "../headers/non_dominated_sorting.h"

//Check if a SolutionA dominates a SolutionB
bool dominates(Solution solutionA, Solution solutionB){
  return (solutionA.fitness.first <= solutionB.fitness.first && solutionA.fitness.second <= solutionB.fitness.second) && (solutionA.fitness.first < solutionB.fitness.first || solutionA.fitness.second < solutionB.fitness.second);
}

//A struct to compare solutions by id inside of the set
struct SolutionComparator {
  bool operator()(const pair<Solution, int>& SolutionA, const pair<Solution, int>& SolutionB) const {
    return SolutionA.second < SolutionB.second;
  }
};

//Building the fronts
vector<vector<pair<Solution, int>>> build_fronts(set<pair<Solution, int>, SolutionComparator>& solutions){
  vector<vector<pair<Solution, int>>> fronts;

  while(!solutions.empty()){ //Run until all the solutions are classified

    //Finding the 'best_solution', that is, the solution not dominated by any other 
    auto firstElement = solutions.begin();
    pair<Solution, int> best_solution = *firstElement;

    for(auto it = solutions.begin(); it != solutions.end(); ++it){
      if(best_solution.second == it->second) continue;
      if (!dominates(best_solution.first, it->first)) {
        best_solution = *it;
      }
    }

    vector<pair<Solution, int>> front;
    front.push_back(best_solution);
    solutions.erase(best_solution); // Removing the solution from the set

    vector<pair<Solution, int>> to_remove;
    for(auto solution : solutions){
      bool dominated = false;
      for(const auto& front_solution : front){
        if(dominates(front_solution.first, solution.first)){
          dominated = true;
          break;
        }
      }

      if(!dominated){
        front.push_back(solution);
        to_remove.push_back(solution);
      }
    }

    // Remove all solutions added to the current front
    for(const auto& solution : to_remove){
      solutions.erase(solution);
    }

    fronts.push_back(front);
  }
  return fronts;
}

vector<vector<Solution>> non_dominated_sorting(vector<Solution>& population_rt){
  set<pair<Solution, int>, SolutionComparator> solutions;

  //Filling the set 'solutions' with the solutions given by the arguments and given them an id. 
  for(int i = 0; i < population_rt.size(); i++){
    solutions.insert(make_pair(population_rt[i], i));
  }

  //Building the front
  vector<vector<pair<Solution, int>>> fronts_raw = build_fronts(solutions);
  vector<vector<Solution>> fronts;

  //Extracting solutions from 'fronts_raw', ignoring the 'id'
  for(auto& front_raw : fronts_raw){
    vector<Solution> front;
    for(auto& solution : front_raw){
      front.push_back(solution.first);
    }
    fronts.push_back(front);
  }

  return fronts;
}