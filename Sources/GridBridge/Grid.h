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
    std::set<Pos> openPositions;  // New member to track open positions
    std::set<Pos> occupiedPositions;  // New member to track occupied positions

    // Constructor declaration only
    Grid(int size, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes);

    // Destructor
    ~Grid() = default;

    // Generates the grid dynamically
    void generateGrid(std::vector<GridCellType>& objectTypes, int attempt = 0);

    std::string toASCII() const;

    Pos getEntryPosition() const;

    Orientation getViableOrientation(GridCellType type) const;

    Direction getNewDirection(GridCellType type, Direction currentDirection, 
                        Orientation orientation, const Pos& pos) const;

private:
    static const int MAX_GENERATION_ATTEMPTS = 50;
    // Helper functions
    void initializeGrid();
    Direction getStartingDirection(const Pos& entryPos) const;
    bool isWithinBounds(const Pos& pos) const;
    std::vector<Pos> findOpenPositions(const Pos& currentPos, Direction currentDirection);
    Pos getNextPosition(const Pos& currentPos, Direction direction) const;
    bool isWithinCenter(const Pos& pos) const;
    void initializeOpenPositions();
    void updateOpenPositions(const Pos& currentPos, Direction currentDirection);
    void removePosition(const Pos& pos);  // Helper to remove a position from openPositions
};

#endif // GRID_H
