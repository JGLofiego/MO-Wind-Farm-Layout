#include "./headers/main.h"


#include <iostream>
#include <string>
using namespace std;

int walk_length = 8;
float percent_neighbors = 1.0;
string folder_name_adaptative_walk;
string folder_name_random_walk;

BoundedParetoSet * pareto = new BoundedParetoSet();

int main(int argc, char* argv[]){

    FILE * f;

    f = fopen("output.out", "w");


    int num_neighbors = 25;

    get_instance_info(argc, argv);

    int size_of_population = 100;

    for(int i = 0; i < 1; i++){


        auto population = create_initial_population(size_of_population);        

        auto ep = nsga2(population);

        for(Solution sol: ep){
            Solution * s = new Solution(sol);
            pareto->adicionarSol(s);
            delete s;
        }

        fprintf(f, "Iteration number %d printing Grid", i);

        pareto->printAllSolutions(f);

    }


    fclose(f);
}