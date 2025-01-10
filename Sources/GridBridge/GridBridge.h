#ifndef GRID_BRIDGE_H
#define GRID_BRIDGE_H

#ifdef __cplusplus
#include "Grid.h"
// Define the actual struct
struct Grid_t {
    Grid* grid;
    Grid_t(Grid* g) : grid(g) {}
};
extern "C" {
#else
// Opaque struct for C/Swift
struct Grid_t;
#endif

typedef struct Grid_t* GridHandle;

// Create and destroy grid
GridHandle create_grid(int size, int min_objects, int max_objects);
void destroy_grid(GridHandle grid);

// Generate grid and get cell info
void generate_grid(GridHandle grid);
int get_cell_type(GridHandle grid, int row, int col);
int get_cell_orientation(GridHandle grid, int row, int col);

// Test function
bool test_bridge(void);

#ifdef __cplusplus
}
#endif

#endif // GRID_BRIDGE_H 