#include "Grid.h"
#include <iostream>
#include <sstream>

// Constructor
Grid::Grid(int size, int minObjects, int maxObjects, std::vector<GridCellType> viableCellTypes)
    : gridSize(size), minObjects(minObjects), maxObjects(maxObjects) {
    gridCells.resize(gridSize, std::vector<GridCell*>(gridSize, nullptr));
    std::srand(std::time(nullptr)); // Seed for randomness
}

// Destructor
Grid::~Grid() {
    for (auto& row : gridCells) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

// Generate the grid
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Grid.h"

void Grid::generateGrid(const std::vector<GridCellType>& objectTypes) {
    srand(time(nullptr));

    // Step 1: Initialize grid and variables
    initializeGrid(); // Resets the grid and sets all cells to Empty
    Pos entryPos = getEntryPosition();
    Direction startDirection = getStartingDirection(entryPos);
    gridCells[entryPos.first][entryPos.second]->setType(GridCellType::Entry);

    std::set<Pos> occupiedPositions;
    occupiedPositions.insert(entryPos);

    int objectsPlaced = 0;
    Pos currentPos = entryPos;
    Direction currentDirection = startDirection;

    // Step 2: Object placement loop
    while (objectsPlaced < targetNumObjects) {
        // Step 2.1: Find open positions along the current path
        std::vector<Pos> openPositions = findOpenPositions(currentPos, currentDirection, occupiedPositions);
        if (openPositions.empty()) {
            // Continue simulation or restart grid generation if no valid positions
            if (isOutOfCenter(currentPos)) {
                generateGrid(objectTypes); // Restart grid generation
                return;
            }
            currentPos = getNextPosition(currentPos, currentDirection);
            continue;
        }

        // Step 2.2: Place an object at a random open position
        Pos selectedPos = openPositions[rand() % openPositions.size()];
        GridCellType randomType = objectTypes[rand() % objectTypes.size()];
        Orientation randomOrientation = getRandomOrientation(randomType);

        gridCells[selectedPos.first][selectedPos.second]->setType(randomType);
        gridCells[selectedPos.first][selectedPos.second]->setOrientation(randomOrientation);
        occupiedPositions.insert(selectedPos);
        objectsPlaced++;

        // Step 2.3: Update ball path based on placed object
        currentDirection = getNewDirection(randomType, currentDirection, randomOrientation);
        // TODO: Fix, dependent on if cell is teleporter
        currentPos = getNextPosition(selectedPos, currentDirection);
    }

    // Step 3: Simulate ball until it exits center grid area
    while (!isOutOfCenter(currentPos)) {
        currentPos = getNextPosition(currentPos, currentDirection);
    }
    gridCells[currentPos.first][currentPos.second]->setType(GridCellType::Exit);

    // Step 4: Generate ASCII representation
    std::cout << toASCII() << std::endl;
}

// Get a random position on the edge of the grid
Pos Grid::getEntryPosition() const {
    int side = std::rand() % 4;
    int pos = std::rand() % gridSize;

    switch (side) {
        case 0: return {0, pos};               // Top row
        case 1: return {gridSize - 1, pos};   // Bottom row
        case 2: return {pos, 0};              // Left column
        default: return {pos, gridSize - 1};  // Right column
    }
}

// Simulate ball path and return end position
Pos Grid::simulateBallPath(const Pos& start, Direction direction) {
    Pos current = start;

    while (isWithinActualGrid(current)) {
        switch (direction) {
            case Direction::Up:    --current.first; break;
            case Direction::Down:  ++current.first; break;
            case Direction::Left:  --current.second; break;
            case Direction::Right: ++current.second; break;
        }
    }

    return current; // End position when out of bounds
}

// Check if a position is within the grid bounds
bool Grid::isWithinActualGrid(const Pos& pos) const {
    return pos.first >= 1 && pos.first <= gridSize && pos.second >= 1 && pos.second <= gridSize;
}

// Convert the grid to an ASCII representation
std::string Grid::toASCII() const {
    std::ostringstream oss;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (gridCells[i][j] == nullptr) {
                oss << ". ";
            } else {
                switch (gridCells[i][j]->getType()) {
                    case GridCellType::Entry:              oss << "E "; break;
                    case GridCellType::Exit:               oss << "X "; break;
                    case GridCellType::Empty:              oss << ". "; break;
                    case GridCellType::InBallPath:         oss << "[] "; break;
                    case GridCellType::Bumper:             oss << "B "; break;
                    case GridCellType::Tunnel:             oss << "T "; break;
                    case GridCellType::Teleporter:         oss << "O "; break;
                    case GridCellType::ActivatedBumper:    oss << "A "; break;
                    case GridCellType::DirectionalBumper:  oss << "D "; break;
                    default:                               oss << "? "; break;
                }
            }
        }
        oss << "\n";
    }

    return oss.str();
}
