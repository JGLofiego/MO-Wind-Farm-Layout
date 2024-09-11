#include <vector>
#include <cstdlib>
#include "../../headers/main.h"
// #include "../../headers/turbine.h"
#include <cmath>
#include <iostream>
using namespace std;

const double PI = 3.14159265358979323846;

double calculate_cost(Solution& sol){
    double acc = 0;

    for(int i = 0; i < sol.turbines.size(); i++){
        //Acumulador recebe o custo da posição em que turbina se encontra 
        acc += (*sol.costs)[sol.turbines[i].index];
    }

    sol.fitness.first = acc;

    return acc;
}

double calculate_interference(Turbine& t_initial, Turbine& t_interfered, float& angle){

    double toRadians = angle * PI / 180.0;

    // Se a turbina for a mesma, então interferência 0
    if(t_initial.id == t_interfered.id){
        return 0;
    }

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

double calculate_power(Solution& sol, float& freeWind, float& angle){
    double power = 0;
    double deficit, wind, result;

    for(int i = 0; i < sol.turbines.size(); i++){
        deficit = 0;

        for(int j = 0; j < sol.turbines.size(); j++){
            result = calculate_interference(sol.turbines[i], sol.turbines[j], angle);
            deficit += result * result;
        }

        wind = freeWind * (1 - sqrt(deficit));

        // ********** Teste da potência produzida **********
        // cout << "Velocidade do vento em "<< sol.turbines[i].id << " : " <<
        //  wind << " produz " << power_produced(wind, sol.turbines[i]) << endl;

        power += power_produced(wind, sol.turbines[i]);
    }

    sol.fitness.second = power;
    return power;
}

// Função para gerar uma solução aleatória, retorna uma matriz booleana a qual false = sem turbina, e true = turbina
Solution generate_solution(int num_turb, int upperBoundX, int upperBoundY, float& wind, float& angle){

    // inicializa um vector de int com todas as possiveis posições de um grid upperboundX x upperBoundY 
    int mul = upperBoundX * upperBoundY;
    vector<int> pos(mul);
    vector<Turbine> turbines(num_turb);
    Turbine t;

    for (int i = 0; i < pos.size(); i++){
        // Cada posição i do vector é igual ao próprio i
        pos[i] = i;
    }

    // inicializa o vetor solução

    vector<int> solution_grid(mul, 0);

    int rand_int;
    int elmn;

    for(int i = 0; i < num_turb; i++){
        // Gera um número aleatório do tamanho do vector de posições disponíveis
        rand_int = rand() % pos.size();

        elmn = pos[rand_int];

        //Coloca informações da turbina, depois adiciona a turbina no vector
        t.id = i + 1;
        solution_grid[rand_int] = t.id;
        t.index = elmn;
        turbines[i] = t;

        // apaga o elemento do array de posições disponíveis, evitando possíveis repetições
        pos.erase(pos.begin() + rand_int);
    }

    //Filling the Solution

    // ************* Pegar os valores de custo por terreno *************
    vector<float> costs(num_turb, 0.0);

    Solution rSolution;
    rSolution.costs = &costs;

    double cost = calculate_cost(rSolution); 

    rSolution.grid = solution_grid;
    rSolution.available_positions = pos;
    rSolution.turbines = turbines;
    rSolution.fitness.first = calculate_cost(rSolution);
    rSolution.fitness.second = calculate_power(rSolution, wind, angle);

    return rSolution;
}

int main(){
    Turbine turbina1, turbina2, turbina3;
    float angle = 270.0;
    float freeWind = 10.0;

    Solution sol;

    turbina1.id = 1;
    turbina1.diameter = 179;
    turbina1.height = 119;
    turbina1.power = 9.06;
    turbina1.thrust_coef = 0.75;
    turbina1.x = 131742.14216100215;
    turbina1.y = 139742.14216100215;

    turbina2.id = 2;
    turbina2.diameter = 179;
    turbina2.height = 119;
    turbina2.power = 9.06;
    turbina2.thrust_coef = 0.75;
    turbina2.x = 131742.14216100215;
    turbina2.y = 134742.14216100215;

    turbina3.id = 3;
    turbina3.diameter = 179;
    turbina3.height = 119;
    turbina3.power = 9.06;
    turbina3.thrust_coef = 0.75;
    turbina3.x = 131742.14216100215;
    turbina3.y = 133742.14216100215;

    sol.turbines = vector<Turbine> {turbina1, turbina2, turbina3};
    calculate_power(sol, freeWind, angle);

    // double interferedWind = freeWind * (1 - sqrt(calculate_interference(turbina1, turbina2, angle)));

    cout << "Producao da solucao: " << sol.fitness.second << endl;
}