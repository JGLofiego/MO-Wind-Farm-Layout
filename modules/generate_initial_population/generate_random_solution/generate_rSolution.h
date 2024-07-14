#ifndef GENERATE_RSOLUTION_H
#define GENERATE_RSOLUTION_H

#include <vector>
#include <utility>
using namespace std;

struct Solution {
    vector<vector<bool>> grid; //Represents the terrain of the wind farm 
    vector<int> available_positions; //Available positions of the wind farm 
    vector<int> n_available_positions; //Positions ocupied by turbines 
    pair<double, double> fitness;  // The representation of the fitness evaluation, the first one is the cost while the second one is the netpower
};

Solution generate_solution(int num_turb, int upperBoundX, int upperBoundY);

#endif