#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 

#include "../headers/utils/features_csv.h"

using namespace std;

void build_csv(vector<double> &mo_features, vector<string> column_names, const string& filename) {

    ofstream file(filename);

    if (file.is_open()) {
        for (size_t i = 0; i < column_names.size(); ++i) {
            file << column_names[i];
            if (i != column_names.size() - 1) {
                file << ",";  
            }
        }
        file << "\n"; 

        file << fixed << setprecision(10);

        for (size_t i = 0; i < mo_features.size(); ++i) {
            file << mo_features[i];
            if (i != mo_features.size() - 1) {
                file << ","; 
            }
        }
        file << "\n";  

        file.close(); 
        cout << "Arquivo CSV " << filename << " gerado com sucesso!" << endl;
    } else {
        cerr << "Erro ao abrir o arquivo para escrita." << endl;
    }

}
