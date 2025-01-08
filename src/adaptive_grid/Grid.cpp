#include "../../headers/adaptative_grid/Grid.h"
#include <cstring>

// Inicializa o grid com zeros
Grid::Grid() {
    clearGrid();  // Chama clearGrid no construtor para inicializar
}

// Retorna a contagem de posições no grid
int Grid::getPositionCount(int p) {
    if (p < 0 || p >= tam) return -1;
    return grid[p];
}

// Adiciona uma posição no grid
void Grid::addGrid(int p) {
    grid[p]++;
}

// Remove uma posição do grid
void Grid::removeGrid(int p) {
    grid[p]--;
}

// Limpa o grid (zera todas as posições)
void Grid::clearGrid() {
    memset(grid, 0, sizeof(grid[0]) * tam);  // Zera a memória do grid
}

// Retorna o tamanho do grid
int Grid::getSize() {
    return tam;
}
