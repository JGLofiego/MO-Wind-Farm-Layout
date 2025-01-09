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
int stop_criteria = 1000000;
string algorithm = "nsga2";
string instance = "A";
string root_folder = "./";


int main(int argc, char* argv[]){

    if(argc == 2){
        instance = argv[1];
    } else if (argc > 2){
        instance = argv[1];
        root_folder = argv[2];
    }

    string path;

    int num_neighbors = 25;
    int size_of_population = 100;

    get_instance_info(argc, argv);

    int sum = 0;
    for(auto elem : turbines_per_zone)
        sum += elem;

    cout << endl;
    cout << "Number of subproblems: " << size_of_population << endl;
    cout << "Number of neighbors: " << num_neighbors << endl;
    cout << "Number of fixed turbines: " << fixd.size() << endl;
    cout << "Number of mobile turbines: " << sum << endl;
    cout << "Wind: " << wind << endl;
    cout << "Angle: " << angle << endl << endl;

    cout << "Run time:" << endl;
    
    auto population = create_initial_population(size_of_population);
    nsga2(population);
}