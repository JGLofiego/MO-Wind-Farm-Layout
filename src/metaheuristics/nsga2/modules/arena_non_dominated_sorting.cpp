#include <vector>
#include <utility>
#include <set>
#include "../../../../headers/metaheuristics/nsga2/modules/non_dominated_sorting.h"
#include "../../../../headers/global_modules/dominates.h"

vector<vector<Solution>> arena_non_dominated_sorting(vector<Solution> &population) {
  vector<vector<Solution>> fronts; 
  vector<Solution> Q = population;

  while (!Q.empty()) {
    vector<Solution> Nds; 
    vector<Solution> RK, R;  

    while (!Q.empty()) {
      Solution X = Q.back();
      Q.pop_back();

      for (auto it = Q.begin(); it != Q.end();) {
        if (dominates(X, *it)) {
          it = Q.erase(it); // Q = Q − {Y}
        } else if (dominates(*it, X)) {
          X = *it; // X = Y
          it = Q.erase(it); // Q = Q − {Y}
          RK.insert(RK.end(), R.begin(), R.end()); // RK = RK ∪ R
          R.clear(); // R = ∅
        } else {  
          R.push_back(*it); // R = R ∪ {Y}
          it = Q.erase(it); // Q = Q − {Y}
        }
      }

      vector<Solution> RK_2;

      for (size_t i = 0; i < RK.size(); ++i) {
        if (!dominates(X, RK[i])) {
          RK_2.push_back(RK[i]);
        }
      }

      Nds.push_back(X); // front = front ∪ {X}

      Q.insert(Q.end(), RK_2.begin(), RK_2.end());
      Q.insert(Q.end(), R.begin(), R.end());
      R.clear(); 
      RK.clear();
      RK_2.clear();

      if(Q.size() <= 1){
        Nds.insert(Nds.end(), Q.begin(), Q.end());
        break;
      }
    }

    fronts.push_back(Nds);

    // Q.erase(remove_if(Q.begin(), Q.end(), [&](const Solution &sol) {
    // return find(Nds.begin(), Nds.end(), sol) != Nds.end();
    // }), Q.end());
  }

  return fronts;
}
