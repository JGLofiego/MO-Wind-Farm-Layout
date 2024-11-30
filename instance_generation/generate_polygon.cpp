#include <math.h>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

pair<double, double> left_most_point = make_pair(150000, 0);

extern default_random_engine rd;
extern uniform_real_distribution<double> points_x;
extern uniform_real_distribution<double> points_y;

bool polygon_order(const pair<double, double>& a, const pair<double, double>& b){
    return atan2(a.second - left_most_point.second, a.first - left_most_point.first)
         < atan2(b.second - left_most_point.second, b.first - left_most_point.first);
}

vector<pair<double, double>> generate_polygon(int num_vertex){
    vector<pair<double, double>> points;
    pair<double, double> aux;

    int i_leftMost = 0;

    for(int i = 0; i < num_vertex; i++){
        aux.first = points_x(rd);
        aux.second = points_y(rd);

        if(aux.first < left_most_point.first){
            left_most_point = aux;
            i_leftMost = i;
        }

        points.push_back(aux);
    }

    aux = points[0];
    points[0] = points[i_leftMost];
    points[i_leftMost] = aux;

    stable_sort(points.begin() + 1, points.end(), polygon_order);
    return points;
}