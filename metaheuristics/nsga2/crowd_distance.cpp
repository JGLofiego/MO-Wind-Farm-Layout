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

vector<Solution> sort_distance(vector<Solution> &population){
    int num = population.size();
    pair<int, double> dfault = make_pair(0, 1);
    float infinity = numeric_limits<float>::max();

    vector<pair<int, double>> byF1(num, dfault), byF2(num, dfault), final(num, dfault);
    vector<Solution> aux = population;

    for(int i=0; i<num; i++){
        byF1[i].first = i;
        byF2[i].first = i;
        final[i].first = i;
        byF1[i].second = population[i].fitness.first;
        byF2[i].second = population[i].fitness.second;
    }

    sort(byF1.begin(), byF1.end(), cmp_second);
    sort(byF2.begin(), byF2.end(), cmp_second);

    vector<pair<int, double>> distancesF1(num, dfault), distancesF2(num, dfault);

    for(int i = 0; i < num; i++){
        distancesF1[i].first = byF1[i].first;
        distancesF2[i].first = byF2[i].first;
    }

    distancesF1[0].second = infinity;
    distancesF2[0].second = infinity;
    distancesF1[num-1].second = infinity;
    distancesF2[num-1].second = infinity;

    for(int i = 1; i < num-1; i++){
        distancesF1[i].second = population[byF1[i+1].first].fitness.first - population[byF1[i-1].first].fitness.first;
        distancesF2[i].second = population[byF2[i+1].first].fitness.second - population[byF2[i-1].first].fitness.second;
    }

    for(int i = 0; i < num; i++) {
        final[distancesF1[i].first].second *= distancesF1[i].second;
        final[distancesF2[i].first].second *= distancesF2[i].second;
    }

    sort(final.begin(), final.end(), cmp_cd);

    for(int i = 0; i < num; i++) {
        population[i] = aux[final[i].first];
    }

    return population;
}

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

    sort_distance(v);

    cout << "RESULTADO FINAL:\n";
    for(int i = 0; i < v.size(); i++){
        cout << v[i].fitness.first << " " << v[i].fitness.second << endl;
    }
}

