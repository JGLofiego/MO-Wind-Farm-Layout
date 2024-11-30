#include <string>
#include <random>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

pair<double, double> left_most_point = make_pair(150000, 0);

bool polygon_order(const pair<double, double>& a, const pair<double, double>& b){
    return atan2(a.second - left_most_point.second, a.first - left_most_point.first)
         < atan2(b.second - left_most_point.second, b.first - left_most_point.first);
}

int main(){

    default_random_engine rd{(unsigned)time(NULL)};
    mt19937 gen(rd());
    cout << fixed << setprecision(11);

    vector<pair<double, double>> test;
    pair<double, double> aux;

    int i_leftMost = 0;

    uniform_int_distribution<int> zone(1, 3);
    uniform_int_distribution<int> polygon_vertex(3, 9);
    uniform_int_distribution<int> available_positions(3238, 21709); 
    uniform_real_distribution<double> points_x(100000.0, 140000.0);
    uniform_real_distribution<double> points_y(100000.0, 140000.0);
    uniform_int_distribution<int> depth(10, 40);
    uniform_int_distribution<int> obstacles(0, 3);
    uniform_int_distribution<int> obstacles_vertex(2, 4);
    uniform_int_distribution<int> turbines_fixed(5, 75);
    uniform_int_distribution<int> turbines_per_zone(10, 100);

    for(int i = 0; i < polygon_vertex(rd); i++){
        aux.first = points_x(rd);
        aux.second = points_y(rd);

        if(aux.first < left_most_point.first){
            left_most_point = aux;
            i_leftMost = i;
        }

        test.push_back(aux);
    }

    aux = test[0];
    test[0] = test[i_leftMost];
    test[i_leftMost] = aux;

    stable_sort(test.begin() + 1, test.end(), polygon_order);

    for(int i = 0; i < test.size(); i++){
        cout << test[i].first << " " << test[i].second << endl;
    }
}