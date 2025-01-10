#include "GridBridge.h"
#include <iostream>

extern "C" {
    GridHandle create_grid(int size, int min_objects, int max_objects) {
        std::cout << "C++: Creating grid..." << std::endl;
        std::vector<GridCellType> objects = {
            GridCellType::Bumper, 
            GridCellType::DirectionalBumper, 
            GridCellType::Tunnel,
            GridCellType::Teleporter,
            GridCellType::ActivatedBumper
        };
        Grid* grid = new Grid(size, min_objects, max_objects, objects);
        std::cout << "C++: Grid created successfully" << std::endl;
        return new Grid_t(grid);
    }

    void destroy_grid(GridHandle handle) {
        std::cout << "C++: Destroying grid..." << std::endl;
        delete handle->grid;
        delete handle;
    }

    void generate_grid(GridHandle handle) {
        std::cout << "C++: Starting grid generation..." << std::endl;
        std::cout.flush();  // Force output to be displayed
        
        if (!handle) {
            std::cout << "C++: Error - null handle!" << std::endl;
            std::cout.flush();
            return;
        }
        
        if (!handle->grid) {
            std::cout << "C++: Error - null grid!" << std::endl;
            std::cout.flush();
            return;
        }
        
        try {
            std::cout << "C++: Creating object types vector..." << std::endl;
            std::cout.flush();
            
            std::vector<GridCellType> objects = {
                GridCellType::Bumper
            };
            
            std::cout << "C++: About to call grid->generateGrid..." << std::endl;
            std::cout.flush();
            
            handle->grid->generateGrid(objects, 0);
            
            std::cout << "C++: Grid generation complete" << std::endl;
            std::cout.flush();
        } catch (const std::exception& e) {
            std::cout << "C++: Exception caught: " << e.what() << std::endl;
            std::cout.flush();
        } catch (...) {
            std::cout << "C++: Unknown exception caught" << std::endl;
            std::cout.flush();
        }
    }

    int get_cell_type(GridHandle handle, int row, int col) {
        if (!handle || !handle->grid) return 0;
        return static_cast<int>(handle->grid->gridCells[row][col].type);
    }

    int get_cell_orientation(GridHandle handle, int row, int col) {
        if (!handle || !handle->grid) return 0;
        return static_cast<int>(handle->grid->gridCells[row][col].orientation);
    }

    bool test_bridge(void) {
        std::cout << "C++: Test function called" << std::endl;
        std::cout.flush();
        return true;
    }
} 