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

void moveY(vector<pair<double, double>>& polygon, int iPolygonPoint, double y){
    double pace = y - polygon[iPolygonPoint].second;

    for(int i = 0; i < polygon.size(); i++){
        polygon[i].second += pace;
    }
}

void moveX(vector<pair<double, double>>& polygon, int iPolygonPoint, double x){
    double pace = x - polygon[iPolygonPoint].first;

    for(int i = 0; i < polygon.size(); i++){
        polygon[i].first += pace;
    }
}

int find_pointX(vector<pair<double, double>>& points, double val){
    for(int i = 0; i < points.size(); i++){
        if(points[i].first == val){
            return i;
        }
    }

    return -1;
}

int find_pointY(vector<pair<double, double>>& points, double val){
    for(int i = 0; i < points.size(); i++){
        if(points[i].second == val){
            return i;
        }
    }

    return -1;
}

bool isInBoundaries(vector<pair<double, double>>& bounding_box){
    if((bounding_box[0].first >= 100000 && bounding_box[0].first <= 150000) &&
       (bounding_box[3].first >= 100000 && bounding_box[0].first <= 150000) &&
       (bounding_box[0].second >= 100000 && bounding_box[0].second <= 150000) &&
       (bounding_box[3].second >= 100000 && bounding_box[03].second <= 150000)){
        return true;
       }
    return false;
}

bool re_position(vector<pair<double, double>>& polygonA, vector<pair<double, double>>& polygonB){
    auto boundingBoxA = bounding_box(polygonA);
    auto boundingBoxB = bounding_box(polygonB);
    double last_x, last_y;

    int rand_side = rand() % 4;

    for(int i = 0; i < 4; i++){
        if(rand_side == 0){
            moveX(polygonB, 0, boundingBoxA[3].first);
            auto new_bounding_box = bounding_box(polygonB);
            if(isInBoundaries(new_bounding_box)){
                return true;
            }
            moveX(polygonB, 0, boundingBoxB[0].first);
        } else if(rand_side == 1){
            int lowest_y_point = find_pointY(polygonB, boundingBoxB[0].second);
            moveY(polygonB, lowest_y_point, boundingBoxA[3].second);
            auto new_bounding_box = bounding_box(polygonB);
            if(isInBoundaries(new_bounding_box)){
                return true;
            }
            moveY(polygonB, lowest_y_point, boundingBoxB[0].second);
        } else if(rand_side == 2){
            int highest_x_point = find_pointX(polygonB, boundingBoxB[3].first);
            moveX(polygonB, highest_x_point, boundingBoxA[0].first);
            auto new_bounding_box = bounding_box(polygonB);
            if(isInBoundaries(new_bounding_box)){
                return true;
            }
            moveX(polygonB, highest_x_point, boundingBoxB[3].first);
        } else if(rand_side == 3){
            int highest_y_point = find_pointY(polygonB, boundingBoxB[3].second);
            moveY(polygonB, highest_y_point, boundingBoxA[0].second);
            auto new_bounding_box = bounding_box(polygonB);
            if(isInBoundaries(new_bounding_box)){
                return true;
            }
            moveY(polygonB, highest_y_point, boundingBoxB[3].second);
        }
        rand_side = (rand_side + 1) % 4;
    }
    
    return false;
}

bool hasIntersections(vector<vector<pair<double, double>>>& polygons){

    if(polygons.size() == 1){
        return false;
    }

    for (int i = 0; i < polygons.size(); i++){
        if(doIntersect(polygons[i], polygons[(i + 1) % polygons.size()])){
            return true;
        }
    }

    return false;
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

    for(int i = 0; i < num_zones; i++){
        auto test = generate_polygon(polygon_vertex(rd));
        shrink(test, scales[i], rand() % test.size());
        polygons.push_back(test);
    }

    while(hasIntersections(polygons)){
        for (int i = 0; i < polygons.size(); i++){
            if(doIntersect(polygons[i], polygons[(i + 1) % num_zones])){
                if(!re_position(polygons[i], polygons[(i + 1) % num_zones])){
                    cout << "ERROR, IT WAS NOT POSSIBLE TO REPOSITION CONFLICTED ZONES" << endl;
                }
            }
        }
    }

    for(int i = 0; i < num_zones; i++){
        for(int j = 0; j < polygons[i].size(); j++){
            cout << polygons[i][j].first << " " << polygons[i][j].second << endl;
        } cout << endl;
    }
}