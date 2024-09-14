#include "./modules/generate_initial_population/generate_random_solution/generate_rSolution.cpp"
#include "./modules/generate_initial_population/generate_population/population.cpp"
#include "modules/genetic_operators/mutation/mutation.cpp"
#include "modules/genetic_operators/crossover/crossover.cpp"
#include "metaheuristics/moead/moead.cpp"
#include "./modules/moead/generate_weight_vectors.cpp"
#include "./modules/moead/generate_neighborhood.cpp"
#include "./modules/moead/get_best_z_point.cpp"
#include "./modules/moead/tchebycheff.cpp"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

vector<Foundation> foundations;

float wind;
float power;
float thrust_coef = 1.0;
float angle;

int main(){
    cout << fixed << setprecision(5);

    ifstream file;
    Foundation t;

    string _, strX, strY, strCost;
    string zone = "1";

    string strWind = "0.0";
    string strPow, strTC;

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

    wind = 25.0;
    angle = 30.0;

    file.open("../wtg/NREL-10-179.txt");

    while(file.good() && stof(strWind) != wind){
        file >> strWind >> strPow >> strTC;

        if(stof(strWind) > wind){
            power = (power + stof(strPow))/2.0;
            thrust_coef= (thrust_coef + stof(strTC))/2.0;
            break;
        }
        
        power = stof(strPow);
        thrust_coef = stof(strTC);
    }

    file.close();

    srand(time(0));

    int num_turb = 10;

    vector<Solution> population = create_initial_population(9, num_turb);

    for(Solution sol : population){
        for (int i = 0; i < sol.turbines.size(); i++){
            cout << sol.turbines[i].x << " " << sol.turbines[i].y << endl;
        }
        cout << endl;
    }
}