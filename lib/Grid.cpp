#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include "Grid.h"
#include "DirectionMaps.h"

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
            // Fetch the cell type and orientation
            GridCellType cellType = gridCells[i][j].type;
            Orientation cellOrientation = gridCells[i][j].orientation;
            switch (cellType) {

                case GridCellType::Entry:              
                    oss << "E "; break;

                case GridCellType::Exit:               
                    oss << "X "; break;

                case GridCellType::Empty:              
                    oss << ". "; break;

                case GridCellType::InBallPath:         
                    oss << ". "; break;

                case GridCellType::Bumper: 
                    if (cellOrientation == Orientation::UpRight) {
                        oss << "/ ";
                    } else if (cellOrientation == Orientation::DownRight) {
                        oss << "\ ";
                    }
                    break;

                case GridCellType::Tunnel:
                    if (gridCells[i][j].orientation == Orientation::Horizontal) {
                        oss << "= ";
                    } else if (gridCells[i][j].orientation == Orientation::Vertical) {
                        oss << "||";
                    }
                    break;

                case GridCellType::Teleporter:
                    oss << "* "; break;

                case GridCellType::ActivatedBumper:
                    if (cellOrientation == Orientation::UpRight) {
                        oss << "a/ ";
                    } else if (cellOrientation == Orientation::DownRight) {
                        oss << "a\ ";
                    }
                    break;

                case GridCellType::DirectionalBumper:
                    if (cellOrientation == Orientation::TopRight) {
                        oss << "TR ";
                    } else if (cellOrientation == Orientation::TopLeft) {
                        oss << "TL ";
                    } else if (cellOrientation == Orientation::BottomRight) {
                        oss << "BR ";
                    } else if (cellOrientation == Orientation::BottomLeft) {
                        oss << "BL ";
                    }

                default:                               
                    oss << "? "; break;
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
Orientation Grid::getViableOrientation(GridCellType type) {
    std::vector<Orientation> viableOrientations;
    switch (type) {
        case GridCellType::Tunnel: 
            viableOrientations = {Orientation::Horizontal, Orientation::Vertical};
            break;
        case GridCellType::DirectionalBumper: 
            viableOrientations = {Orientation::TopLeft, Orientation::TopRight, Orientation::BottomLeft, Orientation::BottomRight};
            break;
        case GridCellType::Bumper: 
            viableOrientations = {Orientation::UpRight, Orientation::DownRight};
            break;
        default:
            viableOrientations = {Orientation::None};
    }
    return viableOrientations[std::rand() % viableOrientations.size()];
}

Direction Grid::getNewDirection(GridCellType type, Direction currentDirection, Orientation orientation, Pos currentPos) {
    auto typeIt = DirectionMaps::directionMaps.find(type);
    if (typeIt != DirectionMaps::directionMaps.end()) {
        auto orientIt = typeIt->second.find(orientation);
        if (orientIt != typeIt->second.end()) {
            auto dirIt = orientIt->second.find(currentDirection);
            if (dirIt != orientIt->second.end()) {
                return dirIt->second;
            }
        }
    }
    return currentDirection;
}

// Generate the grid dynamically
void Grid::generateGrid(std::vector<GridCellType>& objectTypes) {
    // TODO: ensure only one teleporter pair is in the grid

    // Initialize the grid and get the entry position
    initializeGrid();
    entryPos = getEntryPosition();
    // Get the starting direction
    Direction startDirection = getStartingDirection(entryPos);

    // Set the entry position as occupied
    std::set<Pos> occupiedPositions;
    occupiedPositions.insert(entryPos);

    // Initialize the number of objects placed and the current position and direction
    int objectsPlaced = 0;
    Pos currentPos = entryPos;
    Direction currentDirection = startDirection;

    while (objectsPlaced < minObjects) {
        // Find open positions
        std::vector<Pos> openPositions = findOpenPositions(currentPos, currentDirection, occupiedPositions);

        // If there are no open positions, generate a new grid
        if (openPositions.empty()) {
            generateGrid(objectTypes);
            return;
        }

        // Select a random open position
        Pos selectedPos = openPositions[std::rand() % openPositions.size()];

        // Select a random object type
        GridCellType randomType = objectTypes[std::rand() % objectTypes.size()];

        // Select a random viable orientation for the selected object type
        Orientation randomOrientation = getViableOrientation(randomType);

        // Set the type and orientation of the selected position
        gridCells[selectedPos.first][selectedPos.second].type = randomType;
        gridCells[selectedPos.first][selectedPos.second].orientation = randomOrientation;

        // Add the selected position to the occupied positions
        occupiedPositions.insert(selectedPos);

        // Increment the number of objects placed
        ++objectsPlaced;

        currentDirection = getNewDirection(randomType, currentDirection, randomOrientation, selectedPos);
        if (randomType == GridCellType::Teleporter) {
            // Generate a new teleporter position
            std::vector<Pos> openPositions = findOpenPositions(currentPos, currentDirection, occupiedPositions);
            Pos newTeleporterPos = openPositions[std::rand() % openPositions.size()];
            gridCells[newTeleporterPos.first][newTeleporterPos.second].type = GridCellType::Teleporter;
            gridCells[newTeleporterPos.first][newTeleporterPos.second].orientation = Orientation::None;
            occupiedPositions.insert(newTeleporterPos);
            ++objectsPlaced;

            // Set the current position to the new teleporter position
            currentPos = newTeleporterPos;
        }
        else {
            // Set the current position to the selected position
            currentPos = selectedPos;
        }
    }

    // Simulate path of ball until it exits the grid and add the exit position to the grid
    while (!isOutOfCenter(currentPos)) {
        currentPos = getNextPosition(currentPos, currentDirection);
    }
    gridCells[currentPos.first][currentPos.second].type = GridCellType::Exit;
}
