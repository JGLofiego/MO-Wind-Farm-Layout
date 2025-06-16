#include "../../../../headers/metaheuristics/comolsd/modules/local_search.h"
#include "../../../../headers/global_modules/genetic_operators/mutation.h"

using namespace std;

void local_search(vector<Solution*>& population,
                  const vector<pair<double, double>>& weight_vectors,
                  const pair<double, double>& reference_point,
                  const vector<vector<int>>& neighborhood,
                  function<double(const pair<double, double>&, const pair<double, double>&, const pair<double, double>&)> aggregation_function) {

    int size_population = population.size();
    vector<bool> isSearched(size_population, false);

    bool all_searched = false;

    while (!all_searched) {
        all_searched = true;

        for (int i = 0; i < size_population; i++) {
            if (isSearched[i]) continue;
            
            isSearched[i] = true; // Mark as searched
            all_searched = false;

            // Searching for xi's neighbors
            vector<int> neighbors_indices = neighborhood[i]; //Indices of the neighbors of solution i
            
            vector<Solution*> neighbors;
            for(int j = 0; j < neighbors_indices.size(); j++) 
              neighbors.push_back(population[neighbors_indices[j]]);

            Solution* current = population[i]; //Current solution
            for (Solution* y : neighbors) {
                double y_value = aggregation_function(y->fitness, weight_vectors[i], reference_point);
                double xi_value = aggregation_function(current->fitness, weight_vectors[i], reference_point);

                //!!! preciso atualizar a vizinhanca?
                if (y_value <= xi_value) {
                    *population[i] = *y;
                    isSearched[i] = false; // mark as "unsearched" as it has been updated
                }

                //!!!Preciso deletar y?
                //delete y;
            }
        }
    }
}
