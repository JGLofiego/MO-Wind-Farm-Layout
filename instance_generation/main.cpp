#include <string>
#include <random>
#include <iostream>
#include <time.h>
using namespace std;

int main(){

    default_random_engine rd{(unsigned)time(NULL)};
    mt19937 gen(rd());

    uniform_int_distribution<int> zone(1, 3);
    uniform_int_distribution<int> polygon_vertex(10, 40);
    uniform_int_distribution<int> available_positions(3238, 21709);
    uniform_int_distribution<int> depth(10, 40);
    uniform_int_distribution<int> obstacles(0, 3);
    uniform_int_distribution<int> obstacles_vertex(2, 4);
    uniform_int_distribution<int> turbines_fixed(5, 75);
    uniform_int_distribution<int> turbines_per_zone(10, 100);

    for(int i = 0; i < zone(rd); i++){
        cout << polygon_vertex(rd) << " " << available_positions(rd) << " " << obstacles(rd);
        cout << " " << turbines_per_zone(rd) << endl;
    }
}