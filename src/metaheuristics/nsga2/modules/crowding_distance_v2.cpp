#include <list>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../../../headers/main.h"
using namespace std;

bool cmp_second_v2(const pair<int, double>& a, const pair<int, double>& b){
    return a.second < b.second;
}

bool cmp_cd_v2(const pair<int, double>&a, const pair<int, double>&b){
    return a.second >= b.second;
}

list<Solution*> crowding_distance_v2(list<Solution*> &population){
    // Constantes Reutilizáveis
    int num = population.size();
    pair<int, double> dfault = make_pair(0, 1);
    float infinity = numeric_limits<float>::max();
    
    // Inicializa um vetor de índices que vai servir como base para vários vetores
    vector<pair<int, double>> base(num, dfault);
    int i = 0;
    for(auto it = population.begin(); it != population.end(); ++it, ++i){
        base[i].first = i;
    }

    // Inicializa 3 vetores de pair(int, double)
    // byf1 é o vetor que armazena o índice no first e o valor na função 1 no second
    // byf2 é o vetor que armazena os índices no first e o valor na função 2 no second
    // final é o vetor que armazena os índices no first e o valor do crowding distance no second
    // aux é uma cópia da população para auxiliar a rearranjar o vetor
    vector<pair<int, double>> byF1, byF2, final;
    byF1 = byF2 = final = base;
    list<Solution*> aux = population;

    // Loop que a cada iteração coloca o valor do second como sendo o valor da respectiva função
    i = 0;
    for(auto it = population.begin(); it != population.end(); ++it, ++i){
        byF1[i].second = (*it)->fitness.first;
        byF2[i].second = (*it)->fitness.second * -1;
    }

    // Ordena os vetores baseados no second
    stable_sort(byF1.begin(), byF1.end(), cmp_second_v2);
    stable_sort(byF2.begin(), byF2.end(), cmp_second_v2);

    // Inicializa outros dois vetores de pares para armazenar os resultados do crowding distance de cada uma das funções
    vector<pair<int, double>> distancesF1, distancesF2;
    distancesF1 = byF1;
    distancesF2 = byF2;

    // Atribui as pontas um valor muito grande
    distancesF1[0].second = infinity;
    distancesF2[0].second = infinity;
    distancesF1[num-1].second = infinity;
    distancesF2[num-1].second = infinity;

    // Atribui no second o valor do Crowding distance daquela solução em relação aos vizinhos
    for(int i = 1; i < num-1; i++){
        // Obtém o iterador correspondente ao índice
        auto itF1_prev = next(byF1.begin(), i-1);
        auto itF1_next = next(byF1.begin(), i+1);
        auto itF2_prev = next(byF2.begin(), i-1);
        auto itF2_next = next(byF2.begin(), i+1);

        // Agora acessa os elementos apontados pelos iteradores
        distancesF1[i].second = (*itF1_next).second - (*itF1_prev).second;
        distancesF2[i].second = (*itF2_next).second - (*itF2_prev).second;
    }

    // Coloca no vetor final o valor da multiplicação do crowding de f1 com o crowding de f2
    for(i = 0; i < num; i++) {
        final[distancesF1[i].first].second *= distancesF1[i].second;
        final[distancesF2[i].first].second *= distancesF2[i].second;
    }

    // Ordena o vetor de forma decrescente em relação ao second
    stable_sort(final.begin(), final.end(), cmp_cd_v2);

    // Função para printar os valores das funções e o cd, como forma de debugar
    // for(int i = 0; i < final.size(); i++) {
    //     cout << population[final[i].first].fitness.first << " " << population[final[i].first].fitness.second << " " << final[i].second << endl;
    // }

    // Pega o valor do índice correto na ordenação e copia para os elementos de population
    i = 0;
    for(auto it = population.begin(); it != population.end(); ++it, ++i) {
        auto aux_it = next(aux.begin(), i); 
        *it = *aux_it;
    }

    return population;
}

// Teste do algorítmo
// int main(){
//     list<Solution*> v;
//     vector<vector<int>> grid;
//     vector<vector<Turbine>> turb;

//     Solution* sol0 = new Solution({
//         grid,
//         turb,
//         make_pair(-20, 70)
//     });
//     Solution* sol1 = new Solution({
//         grid,
//         turb,
//         make_pair(-25, 80)
//     });
//     Solution* sol2 = new Solution({
//         grid,
//         turb,
//         make_pair(-10, 30)
//     });
//     Solution* sol3 = new Solution({
//         grid,
//         turb,
//         make_pair(-9, 25)
//     });
//     Solution* sol4 = new Solution({
//         grid,
//         turb,
//         make_pair(-18, 40)
//     });
//     Solution* sol5 = new Solution({
//         grid,
//         turb,
//         make_pair(-19, 41)
//     });

//     v.push_back(sol0);
//     v.push_back(sol1);
//     v.push_back(sol2);
//     v.push_back(sol3);
//     v.push_back(sol4);
//     v.push_back(sol5);

//     crowding_distance(v);

//     cout << "RESULTADO FINAL:\n";
//     for(auto it = v.begin(); it != v.end(); ++it){
//         cout << (*it)->fitness.first << " " << (*it)->fitness.second << endl;
//     }
// }
