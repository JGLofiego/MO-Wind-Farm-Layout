#include <iostream>
#include <vector>
#include <time.h>
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

    srand(time(0));

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

// É possível executar o programa para testar a função generate_solution
// Caso seja executado sem parâmetros adicionais, serão 50 turbinas em um grid 20 x 20
// Caso tenha 1 ou 2 parâmetros adicionais, serão arg1 numero de turbinas em um grid 20 x 20
// Caso tenha 3 ou mais parâmetros adicionais, serão arg1 numero de turbinas em um grid arg2 x arg3
int main(int argc, char** argv){
    int num_turb = 50;
    int upperBoundX = 20;
    int upperBoundY = 20;
    
    if(argc > 3){
        num_turb = atoi(argv[1]);
        upperBoundX = atoi(argv[2]);
        upperBoundY = atoi(argv[3]);
    } else if (argc > 1){
        num_turb = atoi(argv[1]);
    }

    vector<vector<bool>> solution = generate_solution(num_turb, upperBoundX, upperBoundY);

    // Printa no console a matriz solução
    for(int i = 0; i < solution.size(); i++){
        for(int j = 0; j < solution[i].size(); j++){
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }

}