#include "./headers/main.h"


#include <iostream>
#include <string>
using namespace std;

int walk_length = 8;
float percent_neighbors = 1.0;
string folder_name_adaptative_walk;
string folder_name_random_walk;

int main(int argc, char* argv[]){

    int num_neighbors = 200;

    get_instance_info(argc, argv);

    int size_of_population = 10;

    features_extraction(size_of_population, walk_length, num_neighbors * percent_neighbors);
}