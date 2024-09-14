#include "./modules/generate_initial_population/generate_random_solution/generate_rSolution.cpp"
#include "./modules/generate_initial_population/generate_population/population.cpp"
#include "modules/genetic_operators/mutation/mutation.cpp"
#include "modules/genetic_operators/crossover/crossover.cpp"
// #include "metaheuristics/moead/moead.cpp"
// #include "./modules/moead/generate_weight_vectors.cpp"
// #include "./modules/moead/generate_neighborhood.cpp"
// #include "./modules/moead/get_best_z_point.cpp"
// #include "./modules/moead/tchebycheff.cpp"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

vector<Foundation> foundations;

int main(){
    cout << fixed << setprecision(5);

    ifstream file;
    Foundation t;

    string _, strX, strY, strCost;
    string zone = "1";

    string strWindSpd, strPow, strTC;
    float windSpd, pow;
    float tc = 1.0;

    file.open("../site/A/availablePositions.txt");

    while(file.good() && zone == "1" ){
        file >> strX >> strY >> _ >> strCost >> zone;
        t.x = stold(strX);
        t.y = stold(strY);
        t.cost = stold(strCost);

        foundations.push_back(t);
    }

    file.close();

    foundations.pop_back();

    float wind = 25.0;
    float angle = 30.0;

    file.open("../wtg/NREL-10-179.txt");

    while(file.good() && windSpd != wind){
        file >> strWindSpd >> strPow >> strTC;

        if(stof(strWindSpd) > wind){
            windSpd = (windSpd + stof(strWindSpd))/2.0;
            pow = (pow + stof(strPow))/2.0;
            tc = (tc + stof(strTC))/2.0;
            break;
        }
        
        windSpd = stof(strWindSpd);
        pow = stof(strPow);
        tc = stof(strTC);

    }

    file.close();

    srand(time(0));

    int num_turb = 10;

    Solution sol = generate_solution(10, windSpd, pow, tc, angle);

    for (int i = 0; i < sol.turbines.size(); i++){
        cout << sol.turbines[i].x << " " << sol.turbines[i].y << endl;
    } cout << endl;

    // cout << sol.fitness.first << " " << sol.fitness.second << endl;
}