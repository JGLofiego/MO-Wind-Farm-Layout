#include <list>
#include <vector>
#include <utility>
#include <set>
#include <iostream>
#include "../../../../headers/metaheuristics/nsga2/modules/arena_non_dominated_sorting_v2.h"
#include "../../../../headers/global_modules/dominates.h"
#include "../../../../headers/global_modules/isEqual.h"
#include "../../../../headers/globals.h"

list<Solution *> build_front_v2(list<Solution *> &population) {
  list<Solution *> Q = population;
  list<Solution *> Nds;

  while (!Q.empty()) {
    list<Solution *> RK, R;
    Solution *X = Q.back();
    Q.pop_back();

        for (auto it = Q.begin(); it != Q.end();) {
            if (dominates(*X, **it)) {
                it = Q.erase(it); // Q = Q − {Y}
            } else if (dominates(**it, *X)) {
                X = *it; // X = Y
                it = Q.erase(it); // Q = Q − {Y}
                RK.insert(RK.end(), R.begin(), R.end()); // RK = RK ∪ R
                R.clear(); // R = ∅
            } else {
                R.push_back(*it); // R = R ∪ {Y}
                it = Q.erase(it); // Q = Q − {Y}
            }
        }

        list<Solution *> RK_2;

        for (Solution *rk_sol : RK) {
            if (!dominates(*X, *rk_sol)) {
                RK_2.push_back(rk_sol);
            }
        }

        Nds.push_back(X);

        Q.insert(Q.end(), RK_2.begin(), RK_2.end());
        Q.insert(Q.end(), R.begin(), R.end());

        if (Q.size() <= 1) {
            Nds.insert(Nds.end(), Q.begin(), Q.end());
            break;
        }
    }

    cout << "Tamanho da população antes da remoção: " << population.size() << endl;
    cout << "Tamanho do Nds antes de remover da população: " << Nds.size() << endl;

    for (auto itNds = Nds.begin(); itNds != Nds.end(); ++itNds) {
    for (auto it = population.begin(); it != population.end(); ) {
        if (isEqual(*(*itNds), *(*it))) {
        it = population.erase(it);  
        } else {
        ++it;
        }
    }
    }

    cout << "Tamanho da população depois da remoção: " << population.size() << endl;

    return Nds;
}

void arena_non_dominated_sorting_v2(list<Solution *> &population, list<Solution *> F[SIZE_OF_POPULATION * 5]) {
    int population_count = 0; 
    size_t front_index = 0;

    while (!population.empty()) {
        cout << "TAMANHO DA POPULACAO DENTRO DO ARENA: " << population.size() << endl;
        list<Solution *> front = build_front_v2(population);
        population_count += front.size();
        cout << "Adicionando um front de " << front.size() << " solucoes ao vetor" << endl;
        cout << "POPULATION COUNT: " << population_count << endl;

        F[front_index++] = move(front);

        if (population_count >= SIZE_OF_POPULATION) {
            cout << "FINALIZANDO FRONTS POIS POPULATION_COUNT: " << population_count << endl << endl;

            cout << "-----------------------------" << endl;
            int qtd=0;
            for (int i = 0; i < F->size(); i++) {
                qtd += F[i].size();
            }
            cout << "QUANTIDADE DE SOLUCOES DO ARENA: " << qtd << endl;
            cout << "-----------------------------" << endl;

            break;
        }
    }
}
