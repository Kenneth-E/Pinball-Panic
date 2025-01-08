#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Grid.h"

// Constructor
Grid::Grid(int size, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes)
    : gridSize(size), minObjects(minObjects), maxObjects(maxObjects) {
    gridCells.resize(gridSize, std::vector<GridCell>(gridSize));
}

// Get the starting direction based on entry position
Direction Grid::getStartingDirection(const Pos& entryPos) {
    if (entryPos.first == 0) return Direction::Down;   // Top edge
    if (entryPos.first == gridSize - 1) return Direction::Up; // Bottom edge
    if (entryPos.second == 0) return Direction::Right; // Left edge
    return Direction::Left;                            // Right edge
}

// Check if a position is within the grid bounds
bool Grid::isWithinBounds(Pos& pos) {
    return (pos.first >= 0 && pos.first < gridSize) && (pos.second >= 0 && pos.second < gridSize);
}

// Find open positions along the ball's path
std::vector<Pos> Grid::findOpenPositions(const Pos& currentPos, Direction currentDirection, const std::set<Pos>& occupied) {
    std::vector<Pos> openPositions;
    Pos nextPos = getNextPosition(currentPos, currentDirection);

    while (isWithinBounds(nextPos)) {
        if (occupied.find(nextPos) == occupied.end() &&
            gridCells[nextPos.first][nextPos.second].type == GridCellType::Empty) {
            openPositions.push_back(nextPos);
        }
        nextPos = getNextPosition(nextPos, currentDirection);
    }

    return openPositions;
}

// Calculate the next position based on the current direction
Pos Grid::getNextPosition(const Pos& currentPos, Direction direction) {
    switch (direction) {
        case Direction::Up:    return {currentPos.first - 1, currentPos.second};
        case Direction::Down:  return {currentPos.first + 1, currentPos.second};
        case Direction::Left:  return {currentPos.first, currentPos.second - 1};
        case Direction::Right: return {currentPos.first, currentPos.second + 1};
        default:               return currentPos; // No movement
    }
}

// Get a random entry position on the edge of the grid
Pos Grid::getEntryPosition() const {
    int side = std::rand() % 4;
    int pos = std::rand() % gridSize;

    switch (side) {
        case 0: return {0, pos};               // Top edge
        case 1: return {gridSize - 1, pos};    // Bottom edge
        case 2: return {pos, 0};              // Left edge
        default: return {pos, gridSize - 1};  // Right edge
    }
}

// Convert the grid to an ASCII representation
std::string Grid::toASCII() const {
    std::ostringstream oss;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (gridCells[i][j].type == GridCellType::Entry) {
                oss << "E ";
            } else {
                switch (gridCells[i][j].type) {
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

// Initialize the grid
void Grid::initializeGrid() {
    gridCells.clear();
    gridCells.resize(gridSize, std::vector<GridCell>(gridSize));
}

// Select random orientation dependent on the grid cell type
std::vector<Orientation> Grid::getViableOrientations(GridCellType type) {
    std::vector<Orientation> viableOrientations;
    switch (type) {
        // TODO: add rest of orientations
        case GridCellType::Bumper: viableOrientations.insert(viableOrientations.end(), {Orientation::UpRight, Orientation::DownRight});
        case GridCellType::ActivatedBumper: viableOrientations.insert(viableOrientations.end(), {Orientation::UpRight, Orientation::DownRight});
        case GridCellType::Teleporter: viableOrientations.insert(viableOrientations.end(), {Orientation::None});
    }
    return viableOrientations;
}

Direction Grid::getNewDirection(GridCellType type, Direction currentDirection, Orientation orientation, Pos currentPos) {
    // Access GridCell directly, not as a pointer
    const GridCell& cell = gridCells[currentPos.first][currentPos.second];
    
    // Use the cell's properties directly
    // TODO: Implement direction logic based on cell.type, cell.direction, and cell.orientation
    return currentDirection;
}

// Generate the grid dynamically
void Grid::generateGrid(std::vector<GridCellType>& objectTypes) {
    initializeGrid();
    entryPos = getEntryPosition();
    Direction startDirection = getStartingDirection(entryPos);

    std::set<Pos> occupiedPositions;
    occupiedPositions.insert(entryPos);

    int objectsPlaced = 0;
    Pos currentPos = entryPos;
    Direction currentDirection = startDirection;

    while (objectsPlaced < minObjects) {
        std::vector<Pos> openPositions = findOpenPositions(currentPos, currentDirection, occupiedPositions);

        if (openPositions.empty()) {
            generateGrid(objectTypes);
            return;
        }

        Pos selectedPos = openPositions[std::rand() % openPositions.size()];
        GridCellType randomType = objectTypes[std::rand() % objectTypes.size()];
        std::vector<Orientation> viableOrientations = getViableOrientations(randomType);
        Orientation randomOrientation = viableOrientations[std::rand() % viableOrientations.size()];

        gridCells[selectedPos.first][selectedPos.second].type = randomType;
        gridCells[selectedPos.first][selectedPos.second].orientation = randomOrientation;
        occupiedPositions.insert(selectedPos);
        ++objectsPlaced;

        currentDirection = getNewDirection(randomType, currentDirection, randomOrientation, selectedPos);
        // TODO: add case for teleporter
        currentPos = selectedPos;
    }

    while (!isOutOfCenter(currentPos)) {
        currentPos = getNextPosition(currentPos, currentDirection);
    }
    gridCells[currentPos.first][currentPos.second].type = GridCellType::Exit;

    std::cout << toASCII() << std::endl;
}
