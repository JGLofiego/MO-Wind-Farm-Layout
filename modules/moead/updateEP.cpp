#include "../headers/generate_rSolution.h"
#include "../headers/dominates.h"
#include "../headers/isEqual.h"
#include "../headers/updateEP.h"

void updateEP(vector<Solution *> &EP, Solution *child){
  // Step 2.5: Update EP for child1
  // Remove dominated solutions from EP and add the new solutions (child) if it's not dominated
  
  // // Remove solutions dominated by child
  // EP.erase(remove_if(EP.begin(), EP.end(), [&](const Solution &sol) {
  //   return dominates(child, sol);
  // }), EP.end());

  vector<Solution *>::iterator i = EP.begin();
		vector< vector<Solution *>::iterator > remover;
		while (i != EP.end()) {
			if (dominates(*child, **i)) {
				remover.push_back(i);
				//printf("Dominada -> (%.3lf,%.3lf) por (%.3lf,%.3lf)!\n",(**i).getObj(0),(**i).getObj(1),s->getObj(0),s->getObj(1));
			}
			if (dominatesP(**i, *child)|| equals(**i, *child)){
				return;
			}
			i++;
	}

  vector< vector<Solution *>::iterator >::iterator j = remover.begin();
		while (j != remover.end()) {
			
			delete( **j );
			// remove do conjunto pareto
			EP.erase( *j );
			j++;
		}

  // Check if the new child is dominated by any solution in EP or if it's already in EP
  bool is_dominated = false;
  bool already_exists = false;

  for (const auto sol : EP) {
    if (dominates(*sol, *child)) {
      is_dominated = true;
      break;
    }
    if (isEqual(*sol, *child)) {
      already_exists = true;
      break;
    }
  }  

  if (!is_dominated && !already_exists) {
    Solution *t = new Solution;
    *t = *child;
    EP.push_back(t);
  }
}