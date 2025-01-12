#ifndef GRID_H
#define GRID_H

#include <vector>
#include <set>
#include <string>
#include <utility>
#include <random>
#include "GridCell.h"
#include <unordered_map>

// Type alias for position in the grid (row, column)
using Pos = std::pair<int, int>;

struct PosHash {
    std::size_t operator()(const Pos& pos) const {
        return std::hash<int>()(pos.first) ^ (std::hash<int>()(pos.second) << 1);
    }
};

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

    Pos getEntryPosition();

    Orientation getViableOrientation(GridCellType type);

    Direction getNewDirection(GridCellType type, Direction currentDirection, 
                        Orientation orientation, const Pos& pos) const;

private:
    mutable std::mt19937 rng;
    int getRandomInt(int min, int max) const;
    
    static const int MAX_GENERATION_ATTEMPTS = 50;
    // Helper functions
    void initializeGrid();
    void reset();
    std::string DirectionToString(Direction dir) const;
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
