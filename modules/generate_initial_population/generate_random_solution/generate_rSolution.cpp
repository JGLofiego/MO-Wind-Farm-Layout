#include <vector>
#include <cstdlib>
#include "generate_rSolution.h"
using namespace std;

// Função para gerar uma solução aleatória, retorna uma matriz booleana a qual false = sem turbina, e true = turbina
Solution generate_solution(int num_turb, int upperBoundX, int upperBoundY){

    // inicializa um vector de int com todas as possiveis posições de um grid upperboundX x upperBoundY 
    int mul = upperBoundX * upperBoundY;
    vector<int> pos(mul);
    vector<int> pos_na;

    for (int i = 0; i < pos.size(); i++){
        // Cada posição i do vector é igual ao próprio i
        pos[i] = i;
    }

    // inicializa o vetor solução

    vector<bool> solution_grid(mul, false);

    int rand_int;
    int elmn;

    for(int i = 0; i < num_turb; i++){
        // Gera um número aleatório do tamanho do vector de posições disponíveis
        rand_int = rand() % pos.size();

        // Verifica o número no vector e descobre a posição da matriz seguindo a logica m[i][j] = i * maxJ + j
        // numero / upperBoundX = linha a qual número deveria estar
        // numero % upperBoundX = coluna a qual o número deveria estar
        elmn = pos[rand_int];
        //solution_grid[elmn / upperBoundX][elmn % upperBoundX] = true;
        solution_grid[elmn] = true;

        // armazena a posicao que agora esta ocupada com a turbina no vetor de posicoes nao disponiveis
        pos_na.push_back(elmn);

        // apaga o elemento do array de posições disponíveis, evitando possíveis repetições
        pos.erase(pos.begin() + rand_int);
    }

    //Filling the Solution

    double cost = 0.0; 
    double netpower = 0.0;

    Solution rSolution;
    rSolution.grid = solution_grid;
    rSolution.available_positions = pos;
    rSolution.n_available_positions = pos_na;
    rSolution.fitness = make_pair(cost, netpower);

    return rSolution;
}