#include <iomanip>
#include "modules/headers/generate_rSolution.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
#include <map>
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

map<string, vector<int>> turbines_instace = {
    {"A", {26, 8}},
    {"B", {99}},
    {"C", {60, 30}},
    {"D", {170}},
    {"E", {7, 94, 36}},
    {"F", {132, 26}},
    {"G", {140}},
    {"H", {158, 30}},
    {"I", {313}},
    {"J", {136, 74, 25}}
};

vector<int> turbines_per_zone;

extern int walk_length, num_neighbors;

void get_instance_info(int argc, char* argv[]){
    cout << fixed << setprecision(12);

    default_random_engine re{(unsigned)time(nullptr)};
    uniform_real_distribution<double> dist(0.0, 1.0);

    srand(time(nullptr));
    
    string instance = "A";
    string pathFolders = "..";
    string windFile = "RVO_HKN.txt";

    ifstream file;
    Foundation t;
    Turbine turb;

    string _, strX, strY, strCost;
    string zone;

    string strWind = "0.0";
    string strPow, strTC;

    if(argc == 2){
        instance = (string) argv[1];
    } else if(argc == 3){
        instance = (string) argv[1];
        walk_length = atoi(argv[2]);
    } else if(argc == 4){
        instance = (string) argv[1];
        walk_length = atoi(argv[2]);
        num_neighbors = atoi(argv[3]);
    } else if(argc == 5){
        instance = (string) argv[1];
        walk_length = atoi(argv[2]);
        num_neighbors = atoi(argv[3]);
        pathFolders = (string) argv[4];
    } else if(argc > 6){
        instance = (string) argv[1];
        walk_length = atoi(argv[2]);
        num_neighbors = atoi(argv[3]);
        pathFolders = (string) argv[4];
        windFile = (string) argv[5];
    };

    turbines_per_zone = turbines_instace[instance];

    file.open(pathFolders + "/wind/" + windFile);

    if(file.fail()){
        cout << "ERROR: Invalid wind file" << endl;
        throw invalid_argument("Invalid wind file");
    }

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

    file.open(pathFolders + "/site/" + instance + "/availablePositions.txt");

    if(file.fail()){
        cout << "ERROR: Invalid instance" << endl;
        throw invalid_argument("Invalid instance");
    }

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

    file.open(pathFolders + "/wtg/" + "NREL-10-179.txt");

    if(file.fail()){
        cout << "ERROR: '/wtg' not found" << endl;
        throw invalid_argument("'/wtg' not found");
    }

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

    file.open(pathFolders + "/wtg/" + "NREL-15-240.txt");

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

    file.open(pathFolders + "/site/" + instance + "/fixed_wf.txt");

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