#include <string>
#include <random>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include "generate_polygon.cpp"
using namespace std;


default_random_engine rd{(unsigned)time(NULL)};
mt19937 gen(rd());

uniform_real_distribution<double> points_x(100000.0, 140000.0);
uniform_real_distribution<double> points_y(100000.0, 140000.0);

int main(){
    cout << fixed << setprecision(11);

    uniform_int_distribution<int> zone(1, 3);
    uniform_int_distribution<int> polygon_vertex(3, 9);
    uniform_int_distribution<int> available_positions(3238, 21709); 
    uniform_int_distribution<int> depth(10, 40);
    uniform_int_distribution<int> obstacles(0, 3);
    uniform_int_distribution<int> obstacles_vertex(2, 4);
    uniform_int_distribution<int> turbines_fixed(5, 75);
    uniform_int_distribution<int> turbines_per_zone(10, 100);

    auto test = generate_polygon(polygon_vertex(rd));

    // double scale = 0.7;

    // double x_pace = left_most_point.first - left_most_point.first * scale;
    // double y_pace = left_most_point.second - left_most_point.second * scale;

    // for(int i = 0; i < test.size(); i++){
    //     aux = test[i];
    //     aux.first = aux.first * scale;
    //     aux.second = aux.second * scale;
    //     aux.first += x_pace;
    //     aux.second += y_pace;
    //     test[i] = aux;
    // }

    for(int i = 0; i < test.size(); i++){
        cout << test[i].first << " " << test[i].second << endl;
    }
}