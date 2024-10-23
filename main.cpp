#include "./headers/main.h"


#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){

    get_instance_info(argc, argv);

    // for(int i = 0; i < fixd.size(); i++){
    //     cout << fixd[i].id << " " << fixd[i].x << " " << fixd[i].y << endl;
    // }

    // auto start = chrono::high_resolution_clock::now();   
    // wind = 12;
    // angle = 0.0;
    // vector<Solution> population = create_initial_population(500, 313);
    // vector<Solution> moeadResult = moead(population);

    // for(auto i : moeadResult){
    //     if(!isValid(i)){
    //         cout << "ERRO" << endl;
    //         break;
    //     }
    // }
    // wind = 12;
    // angle = 0.0;

    // Solution sol = generate_solution();

    // cout << "Fitness: " << sol.fitness.first << " " << sol.fitness.second << endl;

    // cout << "num_zones: " << num_zones << endl;

    // for(int i = 0; i < num_zones; i++){
    //     cout << "zone " << i + 1 << ": " << sol.turbines[i].size() << endl;
    // }

    // for (int i = 0; i < num_zones; i++){
    //     cout << sol.turbines[i].size() << endl;
    // }

    // vector<Solution> population = create_initial_population(500, 313);
    // vector<Solution> moeadResult = moead(population);

    // for(auto i : moeadResult){
    //     if(!isValid(i)){
    //         cout << "ERRO" << endl;
    //         break;
    //     }
    // }

    // auto end = chrono::high_resolution_clock::now();

    // auto duration = chrono::duration_cast<chrono::minutes>(end - start);

    // cout << "Run time: " << duration.count() << " minutos" << endl;

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


    auto landscapes_vector = landscapes_decomposition(10);

    // metafeatures_extraction(landscapes_vector);
}