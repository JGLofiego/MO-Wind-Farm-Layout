#ifndef GENERATE_RSOLUTION_H
#define GENERATE_RSOLUTION_H

#include <vector>
#include <utility>
#include "turbine.h"
using namespace std;

struct Solution {
    vector<int> grid; //Represents the terrain of the wind farm in a 1D vector. '0' means there is no turbine in that position. Otherwise, there is. 
    vector<int> available_positions; //Available positions of the wind farm 
    vector<Turbine> turbines; // The Structure that is going to store the turbines off solution
    vector<float> *costs; //Cost of site based on the index 
    pair<double, double> fitness;  // The representation of the fitness evaluation, the first one is the cost while the second one is the netpower
};

Solution generate_solution(int num_turb, int upperBoundX, int upperBoundY);

double calculate_cost(Solution& sol);

double calculate_interference(Turbine& t_initial, Turbine& t_interfered, float& angle);

double calculate_power(Solution& sol, float& freeWind, float& angle);

#endif