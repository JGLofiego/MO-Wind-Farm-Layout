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

vector<pair<double, double>> bounding_box(vector<pair<double, double>>& points){
    double lowest_x = 150000.0;
    double lowest_y = 150000.0;
    double highest_x = 100000.0;
    double highest_y = 100000.0;

    for(int i = 0; i < points.size(); i++){
        if(points[i].first < lowest_x){
            lowest_x = points[i].first;
        } else if(points[i].first > highest_x){
            highest_x = points[i].first;
        }

        if(points[i].second < lowest_y){
            lowest_y = points[i].second;
        } else if(points[i].second > highest_y){
            highest_y = points[i].second;
        }
    }
    
    vector<pair<double, double>> box = 
           {make_pair(lowest_x, lowest_y), make_pair(lowest_x, highest_y),
            make_pair(highest_x, lowest_y), make_pair(highest_x, highest_y)};

    return box;
}

bool inBounding_box(pair<double, double>& point, vector<pair<double, double>>& bounding_box){
    double highest_x = bounding_box[3].first;
    double highest_y = bounding_box[3].second;
    double lowest_x = bounding_box[0].first;
    double lowest_y = bounding_box[0].second;

    return (lowest_x < point.first && point.first < highest_x) && (lowest_y < point.second && point.second < highest_y);
}

bool doIntersect(vector<pair<double, double>>& polygonA, vector<pair<double, double>>& polygonB){{
    vector<pair<double, double>> bounding_boxA = bounding_box(polygonA);
    vector<pair<double, double>> bounding_boxB = bounding_box(polygonB);

    for(int i = 0; i < bounding_boxA.size(); i++){
        if(inBounding_box(bounding_boxA[i], bounding_boxB)){
            return true;
        }
    }

    for(int i = 0; i < bounding_boxB.size(); i++){
        if(inBounding_box(bounding_boxB[i], bounding_boxA)){
            return true;
        }
    }

    

    return false;
}}

void shrink(vector<pair<double, double>>& points, double scale, int iPoint_based){
    if(scale == 1.0){
        return;
    }

    pair<double, double> left_most_point = points[0];

    double pace_x = (1.0 - scale) * points[iPoint_based].first;
    double pace_y = (1.0 - scale) * points[iPoint_based].second;

    for(int i = 0; i < points.size(); i++){
        points[i].first = points[i].first * scale + pace_x;
        points[i].second = points[i].second * scale + pace_y;
    }
}

int main(){
    srand(time(NULL));
    
    cout << fixed << setprecision(11);

    uniform_int_distribution<int> zone(1, 3);
    uniform_int_distribution<int> polygon_vertex(3, 9);
    uniform_int_distribution<int> available_positions_dist(3238, 21709); 
    uniform_int_distribution<int> depth(10, 40);
    uniform_int_distribution<int> obstacles(0, 3);
    uniform_int_distribution<int> obstacles_vertex(2, 4);
    uniform_int_distribution<int> turbines_fixed(5, 75);
    uniform_int_distribution<int> turbines_per_zone(10, 100);

    int available_positions = available_positions_dist(rd);
    int num_zones = zone(rd);

    vector<double> scales;

    int min_points_zone = 550;

    vector<vector<pair<double, double>>> polygons;

    if(num_zones == 1){
        scales.push_back(1.0);
    } else if(num_zones == 2){
        int break_point;
        do {
            break_point = (rand() % available_positions) + 1;
        } while (break_point < min_points_zone || break_point > available_positions - min_points_zone);

        scales.push_back((double) break_point / (double) available_positions);
        scales.push_back((double) (available_positions - break_point) / (double) available_positions);
    } else {
        int break_point1, break_point2;
        do {
            break_point1 = (rand() % available_positions) + 1;
        } while(break_point1 < min_points_zone || break_point1 > available_positions - min_points_zone * 2);

        do {
            break_point2 = (rand() % (available_positions - break_point1)) + break_point1 + 1;
        } while(break_point2 < break_point1 + min_points_zone || break_point2 > available_positions - min_points_zone);

        scales.push_back((double) break_point1 / (double) available_positions);
        scales.push_back((double) (break_point2 - break_point1) / (double) available_positions);
        scales.push_back((double) (available_positions - break_point2) / (double) available_positions);
    }

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

    for(int i = 0; i < num_zones; i++){
        auto test = generate_polygon(polygon_vertex(rd));
        shrink(test, scales[i], rand() % test.size());
        polygons.push_back(test);
        for(int j = 0; j < test.size(); j++){
            cout << test[j].first << " " << test[j].second << endl;
        } cout << endl;
    }

    for (int i = 0; i < polygons.size(); i++){
        cout << doIntersect(polygons[i], polygons[(i + 1) % num_zones]) << " ";    
    } cout << endl;
}