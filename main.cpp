#include "./modules/generate_initial_population/generate_random_solution/generate_rSolution.cpp"
#include "./modules/generate_initial_population/generate_population/population.cpp"

#include "modules/genetic_operators/mutation/mutation.cpp"
#include "modules/genetic_operators/crossover/crossover.cpp"

#include "metaheuristics/general_modules/isEqual.cpp"
#include "metaheuristics/general_modules/solution_validator.cpp"

#include "metaheuristics/moead/moead.cpp"
#include "./modules/moead/generate_weight_vectors.cpp"
#include "./modules/moead/generate_neighborhood.cpp"
#include "./modules/moead/get_best_z_point.cpp"
#include "./modules/moead/tchebycheff.cpp"

#include "metaheuristics/nsga2/nsga2.cpp"
#include "./modules/nsga2/binary_tournament.cpp"
#include "./modules/nsga2/crowding_distance.cpp"
#include "./modules/nsga2/non_dominated_sorting.cpp"

#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
using namespace std;

vector<vector<Foundation>> foundations(3);
vector<Turbine> fixd;

int num_zones;
int id = 0;
float wind;
float power, powerFxd;
float thrust_coef = 1.0;
float tcFxd = 1.0;
float angle;
int num_turb = 10;

int main(int argc, char* argv[]){
    cout << fixed << setprecision(12);

    default_random_engine re{(unsigned)time(nullptr)};

    uniform_real_distribution<double> dist(0.0, 1.0);

    srand(time(nullptr));

    string pathSite = "../site/A/";
    string pathWtg = "../wtg/";
    string pathWind = "../wind/RVO_HKN.txt";

    ifstream file;
    Foundation t;
    Turbine turb;

    string _, strX, strY, strCost;
    string zone;

    string strWind = "0.0";
    string strPow, strTC;

    if(argc == 1);
    else if(argc == 2){
        num_turb = atoi(argv[1]);
    } else if(argc >= 5){
        num_turb = atoi(argv[1]);
        pathSite = (string) argv[2];
        pathWtg = (string) argv[3];
        pathWind = (string) argv[4];
    } else {
        cout << "Invalid Number of Parameters" << endl;
        return 1;
    }

    file.open(pathWind);

    double rand_double = dist(re);
    double accChance = 0.0;
    double aux;

    while(file.good()){
        file >> angle >> wind >> aux;
        if(accChance + aux > rand_double){
            break;
        }
        accChance += aux;
    }

    file.close();

    file.open(pathSite + "availablePositions.txt");

    while(file.good() ){
        file >> strX >> strY >> _ >> strCost >> zone;
        t.x = stold(strX);
        t.y = stold(strY);
        t.cost = stold(strCost);

        foundations[stoi(zone) - 1].push_back(t);
    }

    num_zones = stoi(zone);

    file.close();

    foundations.pop_back();

    file.open(pathWtg + "NREL-10-179.txt");

    while(file.good() && stof(strWind) != wind){
        file >> strWind >> strPow >> strTC;

        if(stof(strWind) > wind){
            powerFxd = (power + stof(strPow))/2.0;
            tcFxd = (tcFxd + stof(strTC))/2.0;
            break;
        }
        
        powerFxd = stof(strPow);
        tcFxd = stof(strTC);
    }

    file.close();

    file.open(pathWtg + "NREL-15-240.txt");

    strWind = "0.0";

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

    file.open(pathSite + "fixed_wf.txt");

    turb.diameter = 179;
    turb.power = powerFxd;
    turb.thrust_coef = tcFxd;

    while(file.good()){
        file >> strX >> strY >> _ >> strCost >> zone;
        turb.id = id;
        turb.x = stof(strX);
        turb.y = stof(strY);

        fixd.push_back(turb);
        id++;
    }

    fixd.pop_back();

    file.close();

    // for(int i = 0; i < fixd.size(); i++){
    //     cout << fixd[i].id << " " << fixd[i].x << " " << fixd[i].y << endl;
    // }

    auto start = chrono::high_resolution_clock::now();    

    vector<Solution> population = create_initial_population(500, num_turb);
    vector<Solution> moeadResult = moead(population);
    
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::minutes>(end - start);

    cout << "Run time: " << duration.count() << " minutos" << endl;

    // vector<Solution> nsga2Result = nsga2(population);

    // vector<Solution> filhos;

    // Solution filho1 = crossover(population[0], population[1]);
    // Solution filho2 = crossover(population[1], population[0]);

    // filhos.push_back(filho1);
    // filhos.push_back(filho2);




    // for(Solution sol: population){
    //     for(int i = 0; i < num_zones; i++){
    //         for(int j = 0; j < sol.turbines[i].size(); j++){
    //             cout << sol.turbines[i][j].x << " " << sol.turbines[i][j].y << endl;
    //         }
    //     }
    // vector<Solution> moeadResult = moead(population);

    // vector<Solution> population = create_initial_population(16, num_turb);

    // vector<Solution> moeadResult = moead(population, population.size());


    // cout  << angle << " " << wind << endl;
    // for(Solution sol: population){
    //     for(int i = 0; i < num_zones; i++){
    //         for(int j = 0; j < sol.turbines[i].size(); j++){
    //             cout << sol.turbines[i][j].x << " " << sol.turbines[i][j].y << endl;
    //         }
    //     }

    //     for(int i = 0; i < fixd.size(); i++){
    //         cout << fixd[i].x << " " << fixd[i].y << endl;
    //     }
        
    //     cout << "cost_and_power " << sol.fitness.first << " " << sol.fitness.second << endl;

    //     cout << endl;
    // }

    // for(Solution sol: filhos){
    //     for(int i = 0; i < num_zones; i++){
    //         for(int j = 0; j < sol.turbines[i].size(); j++){
    //             cout << sol.turbines[i][j].x << " " << sol.turbines[i][j].y << endl;
    //         }
    //     }

    //     for(int i = 0; i < fixd.size(); i++){
    //         cout << fixd[i].x << " " << fixd[i].y << endl;
    //     }
        
    //     cout << "cost_and_power " << sol.fitness.first << " " << sol.fitness.second << endl;

    //     cout << endl;
    // }

}