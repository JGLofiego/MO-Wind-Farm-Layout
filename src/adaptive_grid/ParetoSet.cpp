#ifndef PARETOSET_CPP
#define PARETOSET_CPP

#include <list>
#include <map>
#include <math.h>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "../../headers/adaptative_grid/param.h"
#include "../../headers/adaptative_grid/Grid.h"
#include "../../headers/global_modules/generate_initial_population/generate_rSolution.h"
#include "../../headers/adaptative_grid/ParetoSet.h"

double getObj(Solution *s, int obj){
    if(obj == 0){
        return s->fitness.first;
    }

    return s->fitness.second;
}

bool dominatesP(Solution &s1, Solution &s2){
    return (s1.fitness.first >= s2.fitness.first && s1.fitness.second >= s2.fitness.second) &&
           (s1.fitness.first >  s2.fitness.first || s2.fitness.second >  s2.fitness.second);
}

bool equals(Solution &s1, Solution &s2){
    return s1.fitness.first == s2.fitness.first && s1.fitness.second == s2.fitness.second;
}

void printSolucao(FILE* f, Solution *s){
    fprintf(f, "(%.10lf, %.10lf)\n", s->fitness.first, s->fitness.second);
}

void printLayout(ofstream & file, Solution *s){
    for (int i = 0; i < s->turbines.size(); i++){
        for(int j = 0; j < s->turbines[i].size(); j++){
            file << s->turbines[i][j].x << " " << s->turbines[i][j].y << endl;
        }
    }
    file << "\n";
}

int ParetoSet::calcularGridPos(Solution &s) {
    int bit = 0;
    int gridPos = 0;
    for (int obj = 0; obj < NUMOBJETIVOS; obj++) {
        double inicio = rangeAtual[obj].min, fim = rangeAtual[obj].max, meio = (inicio + fim) / 2.0;
        for (int k = 0; k < PROFUNDIDADEGRID; k++) {
            if (getObj(&s, obj) >= meio) {
                gridPos |= (1 << bit);
                inicio = meio;
            } else {
                fim = meio;
            }
            meio = (inicio + fim) / 2.0;
            bit++;
        }
    }
    return gridPos;
}

void ParetoSet::updateGrid() {
    g.clearGrid();
    list<Solution *>::iterator it = sol.begin();
    reiniciarRanges();
    while (it != sol.end()) {
        for (int k = 0; k < NUMOBJETIVOS; k++) {
            rangeAtual[k].min = rangeNovo[k].min = min(rangeAtual[k].min, getObj(*it, k));
            rangeAtual[k].max = rangeNovo[k].max = max(rangeAtual[k].max, getObj(*it, k));
        }
        it++;
    }

    it = sol.begin();
    while (it != sol.end()) {
        g.addGrid(calcularGridPos(**it));
        it++;
    }
}

void ParetoSet::reiniciarRanges() {
    #define INF 1e9
    for (int k = 0; k < NUMOBJETIVOS; k++) {
        rangeAtual[k].min = rangeNovo[k].min = INF;
        rangeAtual[k].max = rangeNovo[k].max = -INF;
    }
    #undef INF
}

ParetoSet::ParetoSet() {
    reiniciarRanges();
    memset(frequencia, 0, sizeof(frequencia));
}

ParetoSet::~ParetoSet() {
    clear();
}

int ParetoSet::getPositionCount(Solution &s) {
    return g.getPositionCount(calcularGridPos(s));
}

int ParetoSet::getPositionCount(int p) {
    return g.getPositionCount(p);
}

list<Solution *> ParetoSet::getElementos() {
    return sol;
}

bool ParetoSet::adicionarSol(Solution *s) {
    ASS ( assert( confereGrid() ); )
    list<Solution *>::iterator i = sol.begin();
    list<list<Solution *>::iterator> remover;
    while (i != sol.end()) {
        if (dominatesP(*s, **i)) {
            remover.push_back(i);
        }
        if (dominatesP(**i, *s) || equals(**i, *s)) {
            return false;
        }
        i++;
    }

    list<list<Solution *>::iterator>::iterator j = remover.begin();
    while (j != remover.end()) {
        g.removeGrid(calcularGridPos(***j));
        delete (**j);
        sol.erase(*j);
        j++;
    }

    Solution *t = new Solution;
    *t = *s;
    sol.push_front(t);
    g.addGrid(calcularGridPos(*t));

    for (int k = 0; k < NUMOBJETIVOS; k++) {
        rangeNovo[k].min = min(rangeNovo[k].min, getObj(t, k));
        rangeNovo[k].max = max(rangeNovo[k].max, getObj(t, k));
    }

    for (int k = 0; k < NUMOBJETIVOS; k++) {
        if (fabs(rangeNovo[k].min - rangeAtual[k].min) > 0.1 * rangeAtual[k].min ||
            fabs(rangeNovo[k].max - rangeAtual[k].max) > 0.1 * rangeAtual[k].max) {
            updateGrid();
            break;
        }
    }

    ASS ( assert( confereGrid() ); )
    return true;
}

void ParetoSet::printAllSolutions(string path) {
    ofstream file(path);
    file << fixed << setprecision(10);
    if (file.is_open()) {
        list<Solution *>::iterator i = sol.begin();
        Solution *s;
        while (i != sol.end()) {
            s = *i;
            file << abs(s->fitness.first) << " " << s->fitness.second << endl;
            i++;
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo para escrita: " << path << endl;
    }
}

void ParetoSet::printAllSolutionsLayout(string path) {
    ofstream file(path);
    file << fixed << setprecision(10);
    if (file.is_open()) {
        list<Solution *>::iterator i = sol.begin();
        Solution *s;
        while (i != sol.end()) {
            s = *i;
            printLayout(file, s);
            i++;
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo para escrita: " << path << endl;
    }
}

int ParetoSet::getSize() {
    return sol.size();
}

Solution *ParetoSet::getSolucao(int p) {
    int c = 0;
    list<Solution *>::iterator i = sol.begin();
    while (i != sol.end()) {
        if (c == p) return *i;
        i++;
        c++;
    }
    return NULL;
}

void ParetoSet::clear() {
    list<Solution *>::iterator i = sol.begin(), j;
    while (i != sol.end()) {
        j = i;
        i++;
        delete (*j);
    }
    sol.clear();
    g.clearGrid();
}

bool ParetoSet::confereGrid() {
    unsigned s = 0;
    for (int i = 0; i < g.getSize(); i++) s += g.getPositionCount(i);
    return s == sol.size();
}


#endif