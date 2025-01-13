#include "GridBridge.h"
#include <iostream>

extern "C" {
    void* Grid_Create(int size, int minObjects, int maxObjects, const int* objectTypes, int objectTypesCount) {
        std::vector<GridCellType> types;
        for (int i = 0; i < objectTypesCount; i++) {
            types.push_back(static_cast<GridCellType>(objectTypes[i]));
        }
        return new Grid(size, minObjects, maxObjects, types);
    }

    void destroy_grid(GridHandle handle) {
        std::cout << "C++: Destroying grid..." << std::endl;
        delete handle->grid;
        delete handle;
    }

    void generate_grid(GridHandle handle) {
        std::cout << "C++: Starting grid generation..." << std::endl;
        std::cout.flush();
        
        if (!handle || !handle->grid) {
            std::cout << "C++: Error - null grid!" << std::endl;
            std::cout.flush();
            return;
        }
        
        try {
            std::vector<GridCellType> objects = {
                GridCellType::Bumper,
                GridCellType::DirectionalBumper,
                GridCellType::Tunnel,
                GridCellType::Teleporter,
                GridCellType::ActivatedBumper
            };
            
            handle->grid->generateGrid(objects, 0);
            
        } catch (const std::exception& e) {
            std::cout << "C++: Exception caught: " << e.what() << std::endl;
            std::cout.flush();
        }
    }

    void Grid_GenerateGrid(void* grid) {
        if (!grid) {
            std::cout << "C++: Error - null grid in Grid_GenerateGrid!" << std::endl;
            return;
        }
        
        try {
            Grid* actualGrid = static_cast<Grid*>(grid);
            std::vector<GridCellType> objects = {
                GridCellType::Bumper,
                GridCellType::DirectionalBumper,
                GridCellType::Tunnel,
                GridCellType::Teleporter,
                GridCellType::ActivatedBumper
            };
            actualGrid->generateGrid(objects, 0);
        } catch (const std::exception& e) {
            std::cout << "C++: Exception in Grid_GenerateGrid: " << e.what() << std::endl;
        }
    }

    int get_cell_type(GridHandle handle, int row, int col) {
        if (!handle || !handle->grid) {
            std::cout << "C++: Null grid in get_cell_type" << std::endl;
            return 0;
        }
        
        Grid* grid = handle->grid;
        if (row < 0 || row >= grid->gridSize || col < 0 || col >= grid->gridSize) {
            std::cout << "C++: Out of bounds access in get_cell_type: " << row << "," << col << std::endl;
            return 0;
        }
        
        return static_cast<int>(grid->gridCells[row][col].type);
    }

    int get_cell_orientation(GridHandle handle, int row, int col) {
        if (!handle || !handle->grid) {
            std::cout << "C++: Null grid in get_cell_orientation" << std::endl;
            return 0;
        }
        
        Grid* grid = handle->grid;
        if (row < 0 || row >= grid->gridSize || col < 0 || col >= grid->gridSize) {
            std::cout << "C++: Out of bounds access in get_cell_orientation: " << row << "," << col << std::endl;
            return 0;
        }
        
        return static_cast<int>(grid->gridCells[row][col].orientation);
    }

    bool test_bridge(void) {
        std::cout << "C++: Test function called" << std::endl;
        std::cout.flush();
        return true;
    }

    void Grid_Destroy(void* grid) {
        std::cout << "C++: Destroying grid..." << std::endl;
        if (grid) {
            delete static_cast<Grid*>(grid);
        }
    }

    int Grid_GetCellType(void* grid, int row, int col) {
        if (!grid) {
            std::cout << "C++: Null grid in Grid_GetCellType" << std::endl;
            return 0;
        }
        
        Grid* actualGrid = static_cast<Grid*>(grid);
        if (row < 0 || row >= actualGrid->gridSize || col < 0 || col >= actualGrid->gridSize) {
            std::cout << "C++: Out of bounds access in Grid_GetCellType: " << row << "," << col << std::endl;
            return 0;
        }
        
        return static_cast<int>(actualGrid->gridCells[row][col].type);
    }

    int Grid_GetCellOrientation(void* grid, int row, int col) {
        if (!grid) {
            std::cout << "C++: Null grid in Grid_GetCellOrientation" << std::endl;
            return 0;
        }
        
        Grid* actualGrid = static_cast<Grid*>(grid);
        if (row < 0 || row >= actualGrid->gridSize || col < 0 || col >= actualGrid->gridSize) {
            std::cout << "C++: Out of bounds access in Grid_GetCellOrientation: " << row << "," << col << std::endl;
            return 0;
        }
        
        return static_cast<int>(actualGrid->gridCells[row][col].orientation);
    }

    int Grid_GetTeleporterIndex(void* grid, int row, int col) {
        if (!grid) return 0;
        Grid* actualGrid = static_cast<Grid*>(grid);
        return actualGrid->gridCells[row][col].teleporterIndex;
    }
} 