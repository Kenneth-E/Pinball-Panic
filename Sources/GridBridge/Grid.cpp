#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include "Grid.h"
#include "DirectionMaps.h"

// Constructor implementation
Grid::Grid(int size, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes)
    : gridSize(size)
    , minObjects(minObjects)
    , maxObjects(maxObjects) {
    std::cout << "Grid constructor - Start" << std::endl;
    std::cout.flush();
    
    try {
        gridCells.resize(gridSize, std::vector<GridCell>(gridSize));
        std::cout << "Grid constructor - Resized grid to " << size << "x" << size << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Grid constructor - Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Grid constructor - Unknown exception" << std::endl;
    }
    std::cout.flush();
}

// Get the starting direction based on entry position
Direction Grid::getStartingDirection(const Pos& entryPos) const{
    if (entryPos.first == 0) return Direction::Down;   // Top edge
    if (entryPos.first == gridSize - 1) return Direction::Up; // Bottom edge
    if (entryPos.second == 0) return Direction::Right; // Left edge
    return Direction::Left;                            // Right edge
}

// Check if a position is within the center region of the grid
bool Grid::isWithinCenter(const Pos& pos) const {
    return (pos.first > 0 && pos.first < gridSize - 1) && (pos.second > 0 && pos.second < gridSize - 1);
}

// Check if a position is within the grid bounds
bool Grid::isWithinBounds(const Pos& pos) const {
    return (pos.first >= 0 && pos.first <= gridSize - 1) && (pos.second >= 0 && pos.second <= gridSize - 1);
}

// Find open positions along the ball's path
std::vector<Pos> Grid::findOpenPositions(const Pos& currentPos, Direction currentDirection) {
    std::vector<Pos> openPositionsInDirection;
    std::cout << "Finding open positions from (" << currentPos.first << "," << currentPos.second 
              << ") going direction " << static_cast<int>(currentDirection) << std::endl;
    
    Pos nextPos = getNextPosition(currentPos, currentDirection);
    
    // Stop if first position is invalid
    if (nextPos == currentPos) {
        return openPositionsInDirection;
    }

    while (isWithinBounds(nextPos)) {
        std::cout << "Checking position (" << nextPos.first << "," << nextPos.second << ")" << std::endl;
        
        if (openPositions.find(nextPos) != openPositions.end()) {
            std::cout << "Position is not occupied" << std::endl;
            if (gridCells[nextPos.first][nextPos.second].type == GridCellType::Empty) {
                std::cout << "Position is empty, adding to open positions" << std::endl;
                openPositionsInDirection.push_back(nextPos);
            }
        } else {
            std::cout << "Position is occupied" << std::endl;
        }
        
        Pos prevPos = nextPos;
        nextPos = getNextPosition(nextPos, currentDirection);
        
        // Break if we're not moving anymore
        if (prevPos == nextPos) break;
    }
    
    std::cout << "Found " << openPositionsInDirection.size() << " open positions" << std::endl;
    return openPositionsInDirection;
}

// Calculate the next position based on the current direction
Pos Grid::getNextPosition(const Pos& currentPos, Direction direction) const {
    Pos nextPos = currentPos;
    switch (direction) {
        case Direction::Up:    nextPos = {currentPos.first - 1, currentPos.second}; break;    // Move up (decrease row)
        case Direction::Down:  nextPos = {currentPos.first + 1, currentPos.second}; break;    // Move down (increase row)
        case Direction::Left:  nextPos = {currentPos.first, currentPos.second - 1}; break;    // Move left (decrease column)
        case Direction::Right: nextPos = {currentPos.first, currentPos.second + 1}; break;    // Move right (increase column)
        default:              return currentPos;
    }
    
    if (!isWithinBounds(nextPos)) {
        return currentPos;
    }
    return nextPos;
}

// Get a random entry position on the edge of the grid, excluding the corners
Pos Grid::getEntryPosition() const {
    int side = std::rand() % 4;
    int pos = std::rand() % (gridSize - 2) + 1;

    switch (side) {
        case 0: return {0 , pos};               // Top edge
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
                    oss << " "; break;

                case GridCellType::InBallPath:         
                    oss << " "; break;

                case GridCellType::Bumper: 
                    if (cellOrientation == Orientation::UpRight) {
                        oss << "╱ ";
                    } else if (cellOrientation == Orientation::DownRight) {
                        oss << "╲ ";
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
                        oss << "⧄ ";
                    } else if (cellOrientation == Orientation::DownRight) {
                        oss << "⧅ ";
                    }
                    break;

                case GridCellType::DirectionalBumper:
                    if (cellOrientation == Orientation::TopRight) {
                        oss << "◹ ";
                    } else if (cellOrientation == Orientation::TopLeft) {
                        oss << "◸ ";
                    } else if (cellOrientation == Orientation::BottomRight) {
                        oss << "◿ ";
                    } else if (cellOrientation == Orientation::BottomLeft) {
                        oss << "◺ ";
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
    std::cout << "initializeGrid - Start" << std::endl;
    std::cout.flush();
    
    try {
        gridCells.clear();
        gridCells.resize(gridSize, std::vector<GridCell>(gridSize));
        std::cout << "initializeGrid - Grid reset complete" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "initializeGrid - Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "initializeGrid - Unknown exception" << std::endl;
    }
    std::cout.flush();
}

// Select random orientation dependent on the grid cell type
Orientation Grid::getViableOrientation(GridCellType type) const{
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

Direction Grid::getNewDirection(GridCellType type, Direction currentDirection, Orientation orientation, const Pos& currentPos) const {
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

void Grid::initializeOpenPositions() {
    openPositions.clear();
    occupiedPositions.clear();
    
    // Add all valid positions to openPositions
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            openPositions.insert({i, j});
        }
    }
}

void Grid::removePosition(const Pos& pos) {
    std::cout << "Removing position (" << pos.first << "," << pos.second << ")" << std::endl;
    openPositions.erase(pos);
    occupiedPositions.insert(pos);
}

void Grid::generateGrid(std::vector<GridCellType>& objectTypes, int attempt) {
    std::cout << "\n=== Starting Grid Generation ===" << std::endl;
    
    initializeGrid();
    initializeOpenPositions();
    std::cout << "Grid and open positions initialized" << std::endl;
    
    // Get entry position and mark it as occupied
    Pos entryPos = getEntryPosition();
    removePosition(entryPos);
    gridCells[entryPos.first][entryPos.second].type = GridCellType::Entry;
    std::cout << "Entry position set to: (" << entryPos.first << "," << entryPos.second << ")" << std::endl;
    
    Direction currentDirection = getStartingDirection(entryPos);
    Pos currentPos = entryPos;
    int objectsPlaced = 0;
    
    while (objectsPlaced < minObjects) {
        std::cout << "\n--- Placing Object " << objectsPlaced + 1 << " ---" << std::endl;
        
        // If there are no open positions, restart
        if (openPositions.empty()) {
            std::cout << "No open positions found - restarting grid generation" << std::endl;
            generateGrid(objectTypes);
            return;
        }
        
        // Select random position from available positions
        // in the direction of the current direction
        std::vector<Pos> openPositionsInDirection = findOpenPositions(currentPos, currentDirection);
        if (openPositionsInDirection.empty()) {
            std::cout << "No open positions found in the current direction - restarting grid generation" << std::endl;
            generateGrid(objectTypes, attempt + 1);
            return;
        }
        int randomIndex = std::rand() % openPositionsInDirection.size();
        Pos selectedPos = openPositionsInDirection[randomIndex];
        removePosition(selectedPos);
        
        // Place object at selected position
        GridCellType randomType = objectTypes[std::rand() % objectTypes.size()];
        Orientation randomOrientation = getViableOrientation(randomType);
        gridCells[selectedPos.first][selectedPos.second].type = randomType;
        gridCells[selectedPos.first][selectedPos.second].orientation = randomOrientation;
        
        // Update tracking variables
        currentDirection = getNewDirection(randomType, currentDirection, randomOrientation, selectedPos);
        currentPos = selectedPos;
        objectsPlaced++;
        
        // Handle teleporter pairs
        if (randomType == GridCellType::Teleporter) {
            if (!openPositions.empty()) {
                auto teleporterIt = openPositions.begin();
                Pos teleporterPos = *teleporterIt;
                removePosition(teleporterPos);
                
                gridCells[teleporterPos.first][teleporterPos.second].type = GridCellType::Teleporter;
                currentPos = teleporterPos;
                objectsPlaced++;
            }
            else {
                std::cout << "No open positions found for teleporter pair - restarting grid generation" << std::endl;
                generateGrid(objectTypes, attempt + 1);
                return;
            }
        }
    }
    
    // Place exit
    while (isWithinCenter(currentPos)) {
        currentPos = getNextPosition(currentPos, currentDirection);
    }
    gridCells[currentPos.first][currentPos.second].type = GridCellType::Exit;
    
    std::cout << "\n=== Grid Generation Complete ===" << std::endl;
}
