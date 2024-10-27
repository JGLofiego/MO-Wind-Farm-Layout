#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 

#include "../headers/utils/features_csv.h"

using namespace std;

<<<<<<< HEAD
void build_csv(vector<double> &mo_features, vector<string> column_names, const string& filename) {
=======
void build_csv(vector<double> &mo_features, const string& filename) {

    vector<string> column_names = {
        "FV_avg_avg", "FV_avg_sd", "FV_sd_avg", "FV_sd_sd", "FV_r1_avg", 
        "FV_r1_sd", "FV_kr_avg", "FV_kr_sd", "FV_sk_avg", "FV_sk_sd",
        "FD_avg_avg", "FD_avg_sd", "FD_sd_avg", "FD_sd_sd", "FD_r1_avg", 
        "FD_r1_sd", "FD_kr_avg", "FD_kr_sd", "FD_sk_avg", "FD_sk_sd",
        "IN_avg_avg", "IN_avg_sd", "IN_sd_avg", "IN_sd_sd", "IN_r1_avg", 
        "IN_r1_sd", "IN_kr_avg", "IN_kr_sd", "IN_sk_avg", "IN_sk_sd",
    };
>>>>>>> 51e87f00273921e450c37188ecb63d611bb020ec

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
