#ifndef GRID_H
#define GRID_H

#include "./param.h"
#include <cstring>

class Grid {
private:
    const static int tam = 1 << (NUMOBJETIVOS * PROFUNDIDADEGRID);
    int grid[1 << (NUMOBJETIVOS * PROFUNDIDADEGRID)];

public:
    // Construtor
    Grid();  // Declaração do construtor, sem a implementação

    // Retorna a contagem de posições no grid
    int getPositionCount(int p);

    // Adiciona uma posição no grid
    void addGrid(int p);

    // Remove uma posição do grid
    void removeGrid(int p);

    // Limpa o grid
    void clearGrid();

    // Retorna o tamanho do grid
    int getSize();
};

#endif // GRID_H
