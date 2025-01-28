#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include "../../../../headers/metaheuristics/nsga2/modules/arena_non_dominated_sorting_v3.h"
#include "../../../../headers/global_modules/dominates.h"
#include "../../../../headers/global_modules/isEqual.h"
#include "../../../../headers/globals.h"

vector<Solution*> build_front_v3(vector<Solution*>& population) {
  vector<Solution*>* Q = new vector<Solution*>(population.begin(), population.end()); 
  vector<Solution*> Nds; 

  while (!Q->empty()) {
    vector<Solution*> RK, R;  
    Solution* X = Q->back(); 
    Q->pop_back();

    for (auto it = Q->begin(); it != Q->end();) {
      if (dominates(*X, **it)) {
        it = Q->erase(it);  // Q = Q − {Y}
      } else if (dominates(**it, *X)) {
        X = *it;  // X = Y
        it = Q->erase(it);  // Q = Q − {Y}
        RK.insert(RK.end(), R.begin(), R.end());  // RK = RK ∪ R
        R.clear();  // R = ∅
      } else {  
        R.push_back(*it);  // R = R ∪ {Y}
        it = Q->erase(it);  // Q = Q − {Y}
      }
    }

    vector<Solution*> RK_2;

    for (int i = 0; i < RK.size(); ++i) {
      if (!dominates(*X, *RK[i])) {
        RK_2.push_back(RK[i]);
      }
    }

    Nds.push_back(X); 

    Q->insert(Q->end(), RK_2.begin(), RK_2.end());
    Q->insert(Q->end(), R.begin(), R.end());

    if (Q->size() <= 1) {
      Nds.insert(Nds.end(), Q->begin(), Q->end());
      break;
    }
  }

  for (int i = 0; i < Nds.size(); ++i) {
    for (auto it = population.begin(); it != population.end(); ) {
      if (isEqual(*Nds[i], **it)) {
        it = population.erase(it);  
      } else {
        ++it;
      }
    }
  }

  delete Q; 

  return Nds; 
}

void arena_non_dominated_sorting_v3(vector<Solution*> &population, vector<Solution *> F[SIZE_OF_POPULATION * 5]) {
  int population_count = 0; 
  int front_index = 0;
  vector<vector<Solution *>> fronts_teste;

  while (!population.empty()) {
    vector<Solution *> front = build_front_v3(population);
    population_count += front.size();

    fronts_teste.push_back(front);
    F[front_index] = front; 
    front_index++;

    if (population_count >= SIZE_OF_POPULATION) {
      break;
    }
  }
}

