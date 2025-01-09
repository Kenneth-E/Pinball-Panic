#include "GridBridge.h"

extern "C" {
    GridHandle create_grid(int size, int min_objects, int max_objects) {
        std::vector<GridCellType> objects = {
            GridCellType::Bumper, 
            GridCellType::DirectionalBumper, 
            GridCellType::Tunnel,
            GridCellType::Teleporter,
            GridCellType::ActivatedBumper
        };
        Grid* grid = new Grid(size, min_objects, max_objects, objects);
        return new Grid_t(grid);
    }

    void destroy_grid(GridHandle handle) {
        delete handle->grid;
        delete handle;
    }

    void generate_grid(GridHandle handle) {
        std::vector<GridCellType> objects = {
            GridCellType::Bumper, 
            GridCellType::DirectionalBumper, 
            GridCellType::Tunnel,
            GridCellType::Teleporter,
            GridCellType::ActivatedBumper
        };
        handle->grid->generateGrid(objects);
    }

    int get_cell_type(GridHandle handle, int row, int col) {
        return static_cast<int>(handle->grid->gridCells[row][col].type);
    }

    int get_cell_orientation(GridHandle handle, int row, int col) {
        return static_cast<int>(handle->grid->gridCells[row][col].orientation);
    }
} 