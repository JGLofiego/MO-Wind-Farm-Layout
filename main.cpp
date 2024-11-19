#include "./headers/main.h"


#include <iostream>
#include <string>
using namespace std;

int walk_length = 8, num_neighbors = 10;

int main(int argc, char* argv[]){

    get_instance_info(argc, argv);

    int size_of_population = 10;

    features_extraction(size_of_population, walk_length, num_neighbors);

    // metafeatures_extraction(landscapes_vector);
}