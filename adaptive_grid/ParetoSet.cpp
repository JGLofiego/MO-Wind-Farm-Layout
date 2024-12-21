#ifndef PARETOSET_CPP
#define PARETOSET_CPP

#include <list>
#include <map>
#include <math.h>
#include "param.h"
#include "Grid.cpp"
#include "../modules/headers/generate_rSolution.h"
#include <cstdio>

using namespace std;

typedef struct {
	double min, max;
} range;

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

class ParetoSet {
	protected:
	list<Solution *> sol;
	range rangeNovo[2], rangeAtual[2];
	int frequencia[NUMEROVERTICES][NUMEROVERTICES];
	Grid g;

	int calcularGridPos(Solution &s) {
		int bit = 0;
		int gridPos = 0;
		for (int obj=0;obj<NUMOBJETIVOS;obj++) {
			double inicio = rangeAtual[obj].min, fim = rangeAtual[obj].max, meio = (inicio+fim)/2.0;
			for (int k=0;k<PROFUNDIDADEGRID;k++) {
				if (getObj(&s, obj) >= meio) {
					gridPos |= (1 << bit);
					inicio = meio;
				} else {
					fim = meio;
				}
				meio = (inicio+fim)/2.0;
				bit++;
			}
		}

		return gridPos;
	}
	void updateGrid() {
		g.clearGrid();

		list<Solution *>::iterator it = sol.begin();
		reiniciarRanges();
		while (it != sol.end()) {
			for (int k=0;k<NUMOBJETIVOS;k++) {
				rangeAtual[k].min = rangeNovo[k].min = min(rangeAtual[k].min, getObj(*it, k));
				rangeAtual[k].max = rangeNovo[k].max = max(rangeAtual[k].max, getObj(*it, k));
			}
			it++;
		}

		it = sol.begin();
		while (it != sol.end()) {
			g.addGrid( calcularGridPos(**it) );
			it++;
		}
	}

	void reiniciarRanges() {
		#define INF 1e9
		for (int k=0;k<NUMOBJETIVOS;k++) {
			rangeAtual[k].min = rangeNovo[k].min = INF;
			rangeAtual[k].max = rangeNovo[k].max = -INF;
		}
		#undef INF
	}


	public:
	ParetoSet() {
		reiniciarRanges();
		memset(frequencia,0,sizeof(frequencia));
	}
	virtual ~ParetoSet() {
		clear();
	}

	int getPositionCount(Solution &s) {
		return g.getPositionCount( calcularGridPos(s) );
	}

	int getPositionCount(int p) {
		return g.getPositionCount( p );
	}

	list<Solution *> getElementos() {
		return sol;
	}

	/* Complexidade: O(n) */
	virtual bool adicionarSol(Solution *s) {
	    ASS ( assert( confereGrid() ); )
		/* nem testa as solucoes piores */
		//if (s->getObj(0) >= ranges[0].max && s->getObj(1) >= ranges[1].max) {
			//fprintf(stderr,"Nem testei!\n");
			//return false;
		//}

		/* percorre o vetor de solucoes e de valores e, caso exista solucao dominada, retira e retorna true. caso contrario, retorna false */
		list<Solution *>::iterator i = sol.begin();
		list< list<Solution *>::iterator > remover;
		while (i != sol.end()) {
			if (dominatesP(*s, **i)) {
				remover.push_back(i);
				//printf("Dominada -> (%.3lf,%.3lf) por (%.3lf,%.3lf)!\n",(**i).getObj(0),(**i).getObj(1),s->getObj(0),s->getObj(1));
			}
			if (dominatesP(**i, *s)|| equals(**i, *s))
				return false;
			i++;
		}

		list< list<Solution *>::iterator >::iterator j = remover.begin();
		while (j != remover.end()) {
		    // remove do grid
			g.removeGrid( calcularGridPos(***j) );
			delete( **j );
			// remove do conjunto pareto
			sol.erase( *j );
			j++;
		}

		Solution *t = new Solution;
		*t = *s;
		// adiciona ao conjunto pareto
		sol.push_front( t );
		// adiciona ao grid
		g.addGrid( calcularGridPos(*t) );

		for(int k=0;k<NUMOBJETIVOS;k++) {
			rangeNovo[k].min = min(rangeNovo[k].min,getObj(t, k));
			rangeNovo[k].max = max(rangeNovo[k].max,getObj(t, k));
		}

		// se houve uma mudanca grande nos ranges (maior que 10% valor), atualizar o grid
		for (int k=0;k<NUMOBJETIVOS;k++) {
			if (fabs(rangeNovo[k].min-rangeAtual[k].min) > 0.1*rangeAtual[k].min || fabs(rangeNovo[k].max-rangeAtual[k].max) > 0.1*rangeAtual[k].max) {
				//fprintf(stderr,"Atualizando grid!\n");
				updateGrid();
				break;
			}
		}

        ASS ( assert( confereGrid() ); )
		return true;
	}

	void printSet(FILE *f) {
		list<Solution *>::iterator i = sol.begin();
		Solution *s;

		fprintf(f,"Ranges = [%.2lf,%.2lf] e [%.2lf,%.2lf]\n",rangeAtual[0].min,rangeAtual[0].max,rangeAtual[1].min,rangeAtual[1].max);
		while (i != sol.end()) {
			s = *i;
			fprintf(f,"(%.10lf,%.10lf) -> %d\n",getObj(s, 0),getObj(s, 1),calcularGridPos(*s));
			i++;
		}
	}
	void printSetPoints(FILE *f) {
		list<Solution *>::iterator i = sol.begin();
		Solution *s;
		while (i != sol.end()) {
			s = *i;
			fprintf(f,"%.10lf %.10lf\n",getObj(s, 0),getObj(s, 1));
			i++;
		}
	}

	void printAllSolutions(FILE *f) {
		list<Solution *>::iterator i = sol.begin();
		Solution *s;
		while (i != sol.end()) {
			s = *i;
			fprintf (f, "\n\n\n");
			printSolucao(f, s);
			i++;
		}
	}

	void printOnePoint(list<Solution *>::iterator i, FILE *f) {
		Solution *s;
		s = *i;
		fprintf(f,"%.10lf %.10lf\n",getObj(s, 0),getObj(s, 1));
	}

	int getSize() {
		return sol.size();
	}

	Solution *getSolucao(int p) {
		int c = 0;
		list<Solution *>::iterator i = sol.begin();
		while (i != sol.end()) {
			if (c == p) return *i;
			i++;
			c++;
		}
		return NULL;
	}



	void clear() {
		list<Solution *>::iterator i = sol.begin(), j;
		while (i != sol.end()) {
			j = i;
			i++;
			delete (*j);
		}
		sol.clear();
		g.clearGrid();
	}

	bool confereGrid() {
	    unsigned s = 0;
	    for (int i=0;i<g.getSize();i++) s += g.getPositionCount(i);
	    return s == sol.size();
	}
};

#endif