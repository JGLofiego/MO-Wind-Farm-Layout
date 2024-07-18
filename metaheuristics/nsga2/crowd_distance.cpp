#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include "../../modules/headers/main.h"
using namespace std;

bool cmp_second(pair<int, double>& a, pair<int, double>& b){
    return a.second < b.second;
}

bool cmp_cd(pair<int, double>& a, pair<int, double>&b){
    return a.second >= b.second;
}

vector<Solution> crowding_distance(vector<Solution> &population){
    //Constantes Reutilizáveis
    int num = population.size();
    pair<int, double> dfault = make_pair(0, 1);
    float infinity = numeric_limits<float>::max();
    
    //Inicializa um vetor de índices que vai servir como base para vários vetores
    vector<pair<int, double>> base(num, dfault);
    for(int i = 0; i < num; i++){
        base[i].first = i;
    }

    //Inicializa 3 vetores de pair(int, double)
    //byf1 é o vetor que armazena o índice no first e o valor na função 1 no second
    //byf2 é o vetor que armazena os índices no first e o valor na função 2 no second
    //final é o vetor que armazena os índices no first e o valor do crowding distance no second
    //aux é uma cópia da população para auxiliar a rearranjar o vetor
    vector<pair<int, double>> byF1, byF2, final;
    byF1 = byF2 = final = base;
    vector<Solution> aux = population;

    //loop que a cada iteração coloca o valor do second como sendo o valor da respectiva função
    for(int i=0; i<num; i++){
        byF1[i].second = population[i].fitness.first;
        byF2[i].second = population[i].fitness.second;
    }

    //Ordena os vetores baseados no second
    sort(byF1.begin(), byF1.end(), cmp_second);
    sort(byF2.begin(), byF2.end(), cmp_second);

    //Inicializa outros dois vetores de pares para armazenar os resultados do crowding distance de cada uma das funções 
    vector<pair<int, double>> distancesF1, distancesF2;
    distancesF1 = byF1;
    distancesF2 = byF2;

    //Atribui as pontas um valor muito grande
    distancesF1[0].second = infinity;
    distancesF2[0].second = infinity;
    distancesF1[num-1].second = infinity;
    distancesF2[num-1].second = infinity;

    //Atribui no second o valor do Crowding distance daquela solução em relação aos vizinhos
    for(int i = 1; i < num-1; i++){
        distancesF1[i].second = population[byF1[i+1].first].fitness.first - population[byF1[i-1].first].fitness.first;
        distancesF2[i].second = population[byF2[i+1].first].fitness.second - population[byF2[i-1].first].fitness.second;
    }

    //Coloca no vetor final o valor da multiplicação do crowding de f1 com o crowding de f2
    for(int i = 0; i < num; i++) {
        final[distancesF1[i].first].second *= distancesF1[i].second;
        final[distancesF2[i].first].second *= distancesF2[i].second;
    }

    //Ordena o vetor de forma decrescente em relação ao second
    sort(final.begin(), final.end(), cmp_cd);

    //Pega o o valor do índice correto na ordenação e copia para os elementos de population
    for(int i = 0; i < num; i++) {
        population[i] = aux[final[i].first];
    }

    return population;
}

// Teste do algorítmo
int main(){
    vector<Solution> v;
    vector<int> grid;
    vector<int> v1, v2;
    Solution sol0 = {
        grid,
        v1,
        v2,
        make_pair(20, 40)
    };
    Solution sol1 = {
        grid,
        v1,
        v2,
        make_pair(25, 30)
    };
    Solution sol2 = {
        grid,
        v1,
        v2,
        make_pair(10, 60)
    };
    Solution sol3 = {
        grid,
        v1,
        v2,
        make_pair(9, 75)
    };
    Solution sol4 = {
        grid,
        v1,
        v2,
        make_pair(18, 50)
    };
    Solution sol5 = {
        grid,
        v1,
        v2,
        make_pair(19, 41)
    };

    v.push_back(sol0);
    v.push_back(sol1);
    v.push_back(sol2);
    v.push_back(sol3);
    v.push_back(sol4);
    v.push_back(sol5);

    crowding_distance(v);

    cout << "RESULTADO FINAL:\n";
    for(int i = 0; i < v.size(); i++){
        cout << v[i].fitness.first << " " << v[i].fitness.second << endl;
    }
}

