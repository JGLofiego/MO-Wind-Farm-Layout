#include "./headers/main.h"


#include <iostream>
#include <string>
using namespace std;

int walk_length = 8;
float percent_neighbors = 1.0;
string folder_name_adaptative_walk;
string folder_name_random_walk;
int countRevalue = 0;

BoundedParetoSet * pareto = new BoundedParetoSet();
FILE * f;

int main(int argc, char* argv[]){

    string instance = "A";

    string algorithm = "nsga2";

    if(argc > 1){
        instance = argv[1];
    }

    string path = instance + "_" + algorithm + "_log.txt";

    f = fopen(path.c_str(), "w");

    int num_neighbors = 25;

    get_instance_info(argc, argv);

    int size_of_population = 100;

    auto population = create_initial_population(size_of_population);        

    auto ep = nsga2(population);

    fclose(f);

    path = instance + "_" + algorithm + "_final_log.txt";

    f = fopen(path.c_str(), "w");

    fprintf(f, "==============   FINAL   ==============\n");
    
    pareto->printAllSolutions(f);

    fclose(f);

    path = instance + "_" + algorithm + "_layout.txt";

    f = fopen(path.c_str(), "w");

    pareto->printAllSolutionsLayout(f);

    fclose(f);
}