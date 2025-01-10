#include "../lib/GridCell.h"
#include "../lib/Grid.h"
#include <iostream>

int main() {
    // Create a grid
    Grid grid(5, 10, 10, {GridCellType::Bumper, GridCellType::DirectionalBumper, GridCellType::Tunnel});

    // Print the grid
    std::cout << grid.toASCII() << std::endl;

    return 0;
}
