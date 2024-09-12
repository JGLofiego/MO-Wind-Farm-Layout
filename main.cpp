#include "modules/genetic_operators/mutation/mutation.cpp"
#include "modules/genetic_operators/crossover/crossover.cpp"
#include "metaheuristics/moead/moead.cpp"
#include "./modules/moead/generate_weight_vectors.cpp"
#include "./modules/moead/generate_neighborhood.cpp"
#include "./modules/moead/get_best_z_point.cpp"
#include "./modules/moead/tchebycheff.cpp"
#include "./modules/generate_initial_population/generate_random_solution/generate_rSolution.cpp"
#include "./modules/generate_initial_population/generate_population/population.cpp"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

int main(){
    cout << fixed << setprecision(5);

    ifstream file;
    Foundation t;
    vector<Foundation> *foundations = new vector<Foundation>();

    string _, strX, strY, strCost;
    string zone = "1";
    vector<double> *costs = new vector<double>();

    string strWindSpd, strPow, strTC;
    float windSpd, pow;
    float tc = 1.0;

    file.open("../site/A/availablePositions.txt");

    while(file.good() && zone == "1" ){
        file >> strX >> strY >> _ >> strCost >> zone;
        t.x = stold(strX);
        t.y = stold(strY);

        foundations->push_back(t);
        costs->push_back(stod(strCost));
    }

    file.close();

    costs->pop_back();
    foundations->pop_back();

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

    // Solution solucao = generate_solution(num_turb, windSpd, pow, tc, angle, costs, foundations);

    // for (int i = 0; i < solucao.turbines.size(); i++){
    //     cout << "Turbina x:" << solucao.turbines[i].x << " Turbina Y:  " << solucao.turbines[i].y<< endl;
    // }

    // cout << "Custo da solucao: " << solucao.fitness.first << " Potencia energetica: " << solucao.fitness.second << endl;

    vector<Solution> EP = moead(num_turb, windSpd, pow, tc, angle, costs, foundations);

    // vector<Solution> population = create_initial_population(10, 15, windSpd, pow, tc, angle, costs, foundations);

    // for(int i = 0; i < population.size(); i++){
    //     cout << population[i].fitness.first << " " << population[i].fitness.second << endl;
    // }

    // Solution solucao1 = generate_solution(10, windSpd, pow, tc, angle, costs, foundations);
    // Solution solucao2 = generate_solution(10, windSpd, pow, tc, angle, costs, foundations);
    
    // cout << "Solucao 1: " << solucao1.fitness.first << " " << solucao1.fitness.second << endl;
    // cout << "Solucao 2: " << solucao2.fitness.first << " " << solucao2.fitness.second << endl;

    // Solution filho = crossover(solucao1, solucao2);

    // cout << "Solucao filho: " << filho.fitness.first << " " << filho.fitness.second << " " << filho.turbines.size() << endl;

    // for(int i = 0; i < filho.turbines.size(); i++){
    //     cout << filho.turbines[i].id << endl;
    // }
}