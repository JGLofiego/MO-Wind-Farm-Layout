#ifndef BEST_Z_POINT_META_H
#define BEST_Z_POINT_META_H

using namespace std;

extern vector<int> turbines_per_zone;
extern float wind;
extern float power, powerFxd;
extern float thrust_coef;
extern float tcFxd;
extern vector<Turbine> fixd;

pair<double, double> get_z_point_metafeatures();

#endif 