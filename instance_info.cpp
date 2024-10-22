#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
#include "./modules/headers/generate_rSolution.h"
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

void get_instance_info(int argc, char* argv[]){
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
        throw invalid_argument("Invalid number of arguments");
        cout << "Invalid Number of Parameters" << endl;
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
}