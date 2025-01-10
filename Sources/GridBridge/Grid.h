#ifndef GRID_H
#define GRID_H

#include <vector>
#include <set>
#include <string>
#include <utility>
#include "GridCell.h"

// Type alias for position in the grid (row, column)
using Pos = std::pair<int, int>;

class Grid {
public:
    int gridSize;                                   
    int minObjects;                                 
    int maxObjects;                                 
    Pos entryPos;
    std::vector<GridCellType> objectTypes;          
    std::vector<std::vector<GridCell>> gridCells;   

    // Constructor declaration only
    Grid(int size, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes);

    // Destructor
    ~Grid() = default;

    // Generates the grid dynamically
    void generateGrid(std::vector<GridCellType>& objectTypes, int attempt = 0);

    std::string toASCII() const;

private:
    static const int MAX_GENERATION_ATTEMPTS = 50;
    // Helper functions
    void initializeGrid();
    Pos getEntryPosition() const;
    Direction getStartingDirection(const Pos& entryPos) const;
    bool isWithinBounds(const Pos& pos) const;
    Direction getNewDirection(GridCellType type, Direction currentDirection, 
                            Orientation orientation, const Pos& pos) const;
    std::vector<Pos> findOpenPositions(const Pos& currentPos, Direction currentDirection, 
                                     const std::set<Pos>& occupied) const;
    Orientation getViableOrientation(GridCellType type) const;
    Pos getNextPosition(const Pos& currentPos, Direction direction) const;
    bool isOutOfCenter(const Pos& pos) const;
};

#endif // GRID_H
