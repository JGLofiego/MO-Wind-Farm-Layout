#include <vector>
#include <cstdlib>
// #include "../../headers/main.h"
#include "../../headers/turbine.h"
#include "../../headers/generate_rSolution.h"
#include <time.h>
#include <cmath>
#include <iostream>
using namespace std;

const double PI = 3.14159265358979323846;

float power_produced(double& wind, Turbine& turbine){
    return 0.6125 * turbine.power * turbine.thrust_coef * (wind * wind * wind);
}

double calculate_cost(Solution& sol){
    double acc = 0;

    for(int z = 0; z < num_zones; z++){
        for(int i = 0; i < sol.turbines[z].size(); i++){
            acc += foundations[sol.turbines[z][i].zone][sol.turbines[z][i].index].cost;//Acumulador recebe o custo da posição em que turbina se encontra
        }
    }

    if(acc > 0){
        acc = acc * (-1);
    }

    sol.fitness.first = acc;

    return acc;
}

double calculate_interference(Turbine& t_initial, Turbine& t_interfered){

    // Se a turbina for a mesma, então interferência 0
    if(t_initial.id == t_interfered.id){
        return 0;
    }
    
    double toRadians = angle * PI / 180.0;

    // Componente horizontal e vertical do vento
    float xWind = cos(toRadians);
    float yWind = sin(toRadians);


    // Vetor com direção da turbina inicial até a turbina possivelmente interferida 
    float xVector = t_interfered.x - t_initial.x;
    float yVector = t_interfered.y - t_initial.y;

    // Calcula o escalar tal que multiplicado pela direção do vento, resulta no ponto da turbina interferida
    // projetado no vetor da direção do vento
    float scalar = (xVector * xWind + yVector * yWind) / (xWind * xWind + yWind * yWind);

    // Caso esse escalar seja negativo, portanto a turbina está atrás em relação ao vento
    if(scalar <= 0){
        return 0;
    }

    // Ponto projetado na direção do vento
    float xWake = t_initial.x + scalar * xWind;
    float yWake = t_initial.y + scalar * yWind;

    // Distância do ponto inicial da turbina para o ponto projetado
    float wakeDistance = sqrt((xWake - t_initial.x) * (xWake - t_initial.x) + (yWake - t_initial.y) * (yWake - t_initial.y));
    // Distância do ponto da turbina interferida para o ponto projetado no wake effect
    float distBtwnCenter = sqrt((xWake - t_interfered.x) * (xWake - t_interfered.x) + (yWake - t_interfered.y) * (yWake - t_interfered.y));

    // Diametro do wake effect no ponto
    float wakeDiameter = t_initial.diameter + 2 * 0.04 * wakeDistance;

    // Se o raio do wake effect + o raio da turbina for menor ou igual a distância entre os centros
    // Então a turbina não sofre interferência do wake effect
    if((wakeDiameter + t_interfered.diameter)/2 <= distBtwnCenter){
        return 0;
    }

    double result = (1 - sqrt(1 - t_interfered.thrust_coef)) * (t_interfered.diameter / wakeDiameter * t_interfered.diameter / wakeDiameter);

    // ********** Teste da interferência entre turbinas **********
    // cout << "Interferencia que a turbina " << t_initial.id << " causa na turbina "
    // << t_interfered.id << " eh : " << result << endl;

    return result;
}

double calculate_power(Solution& sol){
    double power = 0;
    double deficit, windResulted, result;

    for(int z = 0; z < num_zones; z++){
        for(int i = 0; i < sol.turbines[z].size(); i++){
            deficit = 0;

            for(int j = 0; j < num_zones; j++){
                for(int k = 0; k < sol.turbines[z].size(); k++){
                    result = calculate_interference(sol.turbines[z][i], sol.turbines[j][k]);
                    deficit += result * result;
                }
            }

            for( Turbine turbina: fixd){
                result = calculate_interference(sol.turbines[z][i], turbina);
                deficit += result * result;
            }

            windResulted = wind * (1 - sqrt(deficit));

            // ********** Teste da potência produzida **********
            // cout << "Velocidade do vento em "<< sol.turbines[i].id << " : " <<
            //  wind << " produz " << power_produced(wind, sol.turbines[i]) << endl;

            power += power_produced(windResulted, sol.turbines[z][i]);
        }
    }

    for (int i = 0; i < fixd.size(); i++){
        deficit = 0.0;

        for(int j = 0; j < fixd.size(); j++){
            result = calculate_interference(fixd[i], fixd[j]);
            deficit += result * result;
        }

        for(int j = 0; j < num_zones; j++){
            for(int k = 0; k < num_zones; k++){
                result = calculate_interference(fixd[i], sol.turbines[j][k]);
                deficit += result * result;
            }
        }

        windResulted = wind * (1 - sqrt(deficit));

        power += power_produced(windResulted, fixd[i]);
    }

    sol.fitness.second = power;
    return power;
}

// Função para gerar uma solução aleatória, retorna uma matriz booleana a qual false = sem turbina, e true = turbina
Solution generate_solution(int num_turb){
    // inicializa um vector de int com todas as possiveis posições de um grid upperboundX x upperBoundY 
    vector<vector<int>> pos(num_zones);
    
    for(int i = 0; i < num_zones; i++){
        pos[i].resize(foundations[i].size());
    }

    vector<vector<Turbine>> turbines(num_zones);
    
    for(int i = 0; i < num_zones; i++){
        turbines[i].resize(num_turb);
    }

    Turbine t;


    for(int z = 0; z < num_zones; z++){
        for (int i = 0; i < pos[z].size(); i++){
            // Cada posição i do vector é igual ao próprio i
            pos[z][i] = i;
        }
    }

    // inicializa o vetor solução

    vector<int> solution_grid(foundations[0].size() + foundations[1].size() + foundations[2].size(), 0);

    int rand_int;
    int elmn;

    t.diameter = 240;

    for(int z = 0; z < num_zones; z++){
        for(int i = 0; i < num_turb; i++){
            // Gera um número aleatório do tamanho do vector de posições disponíveis
            rand_int = rand() % pos[z].size();

            elmn = pos[z][rand_int];

            //Coloca informações da turbina, depois adiciona a turbina no vector
            t.id = id;
            // solution_grid[elmn] = t.id;
            t.index = elmn;
            t.x = foundations[z][elmn].x;
            t.y = foundations[z][elmn].y;
            t.power = power;
            t.thrust_coef = thrust_coef;
            t.zone = z;
            turbines[z][i] = t;

            // // apaga o elemento do array de posições disponíveis, evitando possíveis repetições
            pos[z].erase(pos[z].begin() + rand_int);

            id++;
        }
    }

    //Filling the Solution

    // ************* Pegar os valores de custo por terreno *************
    Solution rSolution;
    
    rSolution.grid = solution_grid;
    rSolution.turbines = turbines;

    rSolution.fitness.first = calculate_cost(rSolution);
    rSolution.fitness.second = calculate_power(rSolution);

    return rSolution;
}