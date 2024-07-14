#include <iostream>
#include <vector>
#include <time.h>
#include "generate_rSolution.h"
using namespace std;


// Função para gerar uma solução aleatória, retorna uma matriz booleana a qual false = sem turbina, e true = turbina
vector<vector<bool>> generate_solution(int num_turb, int upperBoundX, int upperBoundY){

    // inicializa um vector de int com todas as possiveis posições de um grid upperboundX x upperBoundY 
    int mul = upperBoundX * upperBoundY;
    vector<int> pos(mul);
    for (int i = 0; i < pos.size(); i++){
        // Cada posição i do vector é igual ao próprio i
        pos[i] = i;
    }

    // inicializa a matriz solução
    vector<vector<bool>> solution(upperBoundY, vector<bool>(upperBoundX, false));

    int rand_int;
    int elmn;

    for(int i = 0; i < num_turb; i++){
        // Gera um número aleatório do tamanho do vector de posições disponíveis
        rand_int = rand() % pos.size();

        // Verifica o número no vector e descobre a posição da matriz seguindo a logica m[i][j] = i * maxJ + j
        // numero / upperBoundX = linha a qual número deveria estar
        // numero % upperBoundX = coluna a qual o número deveria estar
        elmn = pos[rand_int];
        solution[elmn / upperBoundX][elmn % upperBoundX] = true;

        // apaga o elemento do array de posições disponíveis, evitando possíveis repetições
        pos.erase(pos.begin() + rand_int);
    }

    return solution;
}