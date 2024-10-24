#ifndef GLOBAL_Z_POINT_H
#define GLOBAL_Z_POINT_H

using namespace std;

extern vector<int> turbines_per_zone;
extern float wind;
extern float power, powerFxd;
extern float thrust_coef;
extern float tcFxd;
extern vector<Turbine> fixd;

pair<double, double> get_global_z_point();

#endif 