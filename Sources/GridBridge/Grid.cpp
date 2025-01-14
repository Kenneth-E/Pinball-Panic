#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <random>
#include "Grid.h"
#include "GridCell.h"
#include "DirectionMaps.h"

// Constructor implementation
Grid::Grid(int size, int minObjects, int maxObjects, const std::vector<GridCellType>& objectTypes)
    : gridSize(size)
    , minObjects(minObjects)
    , maxObjects(maxObjects)
    , rng(std::random_device{}()) {
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

// Helper to get random number in range
int Grid::getRandomInt(int min, int max) const{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

std::string Grid::DirectionToString(Direction dir) const {
    switch (dir) {
        case Direction::Up:    return "Up";
        case Direction::Down:  return "Down";
        case Direction::Left:  return "Left";
        case Direction::Right: return "Right";
        default:              return "Unknown";
    }
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
              << ") going direction " << DirectionToString(currentDirection) << std::endl;
    
    Pos nextPos = getNextPosition(currentPos, currentDirection);
    
    // Stop if first position is invalid
    if (nextPos == currentPos) {
        return openPositionsInDirection;
    }

    while (isWithinCenter(nextPos)) {
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
Pos Grid::getEntryPosition() {
    int side = getRandomInt(0, 3);
    int pos = getRandomInt(1, gridSize - 2);

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
                    break;

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
        case GridCellType::ActivatedBumper: 
            viableOrientations = {Orientation::UpRight, Orientation::DownRight};
            break;
        default:
            viableOrientations = {Orientation::None};
    }
    return viableOrientations[getRandomInt(0, viableOrientations.size() - 1)];
}

Direction Grid::getNewDirection(GridCellType type, Direction currentDirection, 
                              Orientation orientation, const Pos& pos) {
    if (type == GridCellType::ActivatedBumper) {
        if (!gridCells[pos.first][pos.second].hasBeenActivated) {
            gridCells[pos.first][pos.second].hasBeenActivated = true;
            return currentDirection;
        }
        
        const auto& bumperMap = DirectionMaps::directionMaps.at(GridCellType::Bumper);
        auto orientIt = bumperMap.find(orientation);
        if (orientIt != bumperMap.end()) {
            auto dirIt = orientIt->second.find(currentDirection);
            if (dirIt != orientIt->second.end()) {
                return dirIt->second;
            }
        }
        return currentDirection;
    }
    
    // Handle other object types normally
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
    
    // Add all valid positions within center of grid to openPositions
    for (int i = 1; i < gridSize - 1; i++) {
        for (int j = 1; j < gridSize - 1; j++) {
            openPositions.insert({i, j});
        }
    }
}

void Grid::removePosition(const Pos& pos) {
    std::cout << "Removing position (" << pos.first << "," << pos.second << ")" << std::endl;
    openPositions.erase(pos);
    occupiedPositions.insert(pos);
}

void Grid::reset() {
    // Clear all grid cells
    initializeGrid();
    
    // Reset positions
    entryPos = {0, 0};
    
    // Clear open/occupied positions
    openPositions.clear();
    occupiedPositions.clear();
    
    // Reset all cells to empty
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            gridCells[i][j].type = GridCellType::Empty;
            gridCells[i][j].direction = Direction::None;
            gridCells[i][j].orientation = Orientation::None;
        }
    }
}

bool Grid::isPotentialNewObjectValid(Pos nextPos, Pos potentialPos, Direction currentDirection) const{
    // Check if any of the coordinates between nextPos and potentialPos are occupied
    if (currentDirection == Direction::Up) {
        for (int i = nextPos.first - 1; i >= potentialPos.first; i--) {
            if (gridCells[i][nextPos.second].type != GridCellType::Empty 
                && gridCells[i][nextPos.second].type != GridCellType::InBallPath) {
                return false;
            }
        }
    }
    else if (currentDirection == Direction::Down) {
        for (int i = nextPos.first + 1; i <= potentialPos.first; i++) {
            if (gridCells[i][nextPos.second].type != GridCellType::Empty 
                && gridCells[i][nextPos.second].type != GridCellType::InBallPath) {
                return false;
            }
        }
    }
    else if (currentDirection == Direction::Left) {
        for (int i = nextPos.second - 1; i >= potentialPos.second; i--) {
            if (gridCells[nextPos.first][i].type != GridCellType::Empty 
                && gridCells[nextPos.first][i].type != GridCellType::InBallPath) {
                return false;
            }
        }
    }
    else if (currentDirection == Direction::Right) {
        for (int i = nextPos.second + 1; i <= potentialPos.second; i++) {
            if (gridCells[nextPos.first][i].type != GridCellType::Empty 
                && gridCells[nextPos.first][i].type != GridCellType::InBallPath) {
                return false;
            }
        }
    }
    return true;
}

// Replace the single TeleporterPair with a vector
struct TeleporterPair {
    Pos first;
    Pos second;
    int index;  // Add index for identification
};

int Grid::getNextAvailableTeleporterIndex() {
    static std::set<int> usedIndices;
    static const int MAX_INDICES = 9;  // Maximum number of unique symbols
    
    // Clear indices if we've used them all
    if (usedIndices.size() >= MAX_INDICES) {
        usedIndices.clear();
    }
    
    // Generate random index until we find an unused one
    int index;
    do {
        index = getRandomInt(0, MAX_INDICES - 1);
    } while (usedIndices.find(index) != usedIndices.end());
    
    usedIndices.insert(index);
    return index;
}

void Grid::generateGrid(std::vector<GridCellType>& objectTypes, int attempt) {
    reset();
    std::cout << "\n=== Starting Grid Generation ===" << std::endl;
    
    // Initial setup
    initializeGrid();
    initializeOpenPositions();
    
    // Place entry
    Pos entryPos = getEntryPosition();
    gridCells[entryPos.first][entryPos.second].type = GridCellType::Entry;
    
    // Initialize ball path
    Direction currentDirection = getStartingDirection(entryPos);
    Pos currentPos = entryPos;
    int objectsPlaced = 0;

    // Use vector for multiple teleporter pairs
    std::vector<TeleporterPair> teleporterPairs;

    // Teleporter index
    int teleporterIndex = 0;
    
    // TODO: create a seperate function to handle teleporter placement
    // Place initial object in the ball's path
    Pos nextPos = getNextPosition(currentPos, currentDirection);
    std::vector<Pos> initialOpenPositions = findOpenPositions(currentPos, currentDirection);
    if (!initialOpenPositions.empty()) {
        int randomIndex = getRandomInt(0, initialOpenPositions.size() - 1);
        Pos selectedPos = initialOpenPositions[randomIndex];
        
        GridCellType randomType = objectTypes[getRandomInt(0, objectTypes.size() - 1)];
        Orientation randomOrientation = getViableOrientation(randomType);
        
        if (randomType == GridCellType::Teleporter) {
            int newIndex = getNextAvailableTeleporterIndex();  // Get random unused index
            
            // Place first teleporter
            gridCells[selectedPos.first][selectedPos.second].type = GridCellType::Teleporter;
            gridCells[selectedPos.first][selectedPos.second].teleporterIndex = newIndex;
            removePosition(selectedPos);
            
            // Find position for partner teleporter
            std::vector<Pos> remainingPositions(openPositions.begin(), openPositions.end());
            if (!remainingPositions.empty()) {
                int partnerIndex = getRandomInt(0, remainingPositions.size() - 1);
                Pos partnerPos = remainingPositions[partnerIndex];
                
                // Place partner teleporter with same index
                gridCells[partnerPos.first][partnerPos.second].type = GridCellType::Teleporter;
                gridCells[partnerPos.first][partnerPos.second].teleporterIndex = newIndex;
                removePosition(partnerPos);
                
                teleporterPairs.push_back({selectedPos, partnerPos, newIndex});
                objectsPlaced += 2;
                std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << selectedPos.first << "," << selectedPos.second << ")" << std::endl;
                std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << partnerPos.first << "," << partnerPos.second << ")" << std::endl;
            } else {
                std::cout << "No remaining positions for initial teleporter pair, regenerating" << std::endl;
                generateGrid(objectTypes, attempt + 1);
                return;
            }
        } else {
            // Place non-teleporter object
            gridCells[selectedPos.first][selectedPos.second].type = randomType;
            gridCells[selectedPos.first][selectedPos.second].orientation = randomOrientation;
            removePosition(selectedPos);
            objectsPlaced++;
            std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << selectedPos.first << "," << selectedPos.second << ")" << std::endl;
        }
    }
    
    int mainLoopCount = 0;
    
    while (true) {
        // handle infinite loop
        mainLoopCount++;
        if (mainLoopCount > 1000) {
            std::cout << "Main loop count exceeded 1000, regenerating" << std::endl;
            generateGrid(objectTypes, attempt + 1);
            return;
        }
        
        Direction nextDirection = currentDirection;
        Pos nextPos = getNextPosition(currentPos, currentDirection);
        
        // check if the ball is at the exit
        if (!isWithinCenter(nextPos)) {
            gridCells[nextPos.first][nextPos.second].type = GridCellType::Exit;
            break;
        }
        
        // Mark ball path
        if (gridCells[nextPos.first][nextPos.second].type == GridCellType::Empty) {
            gridCells[nextPos.first][nextPos.second].type = GridCellType::InBallPath;
            removePosition(nextPos);
        }
        
        // check if the ball is at an object
        if (gridCells[nextPos.first][nextPos.second].type != GridCellType::Empty && 
            gridCells[nextPos.first][nextPos.second].type != GridCellType::InBallPath) {
            
            GridCellType cellType = gridCells[nextPos.first][nextPos.second].type;
            Orientation cellOrientation = gridCells[nextPos.first][nextPos.second].orientation;
            
            // Handle teleporter interaction
            if (cellType == GridCellType::Teleporter) {
                // Find matching teleporter pair
                for (const auto& pair : teleporterPairs) {
                    if (nextPos == pair.first) {
                        nextPos = pair.second;
                        break;
                    } else if (nextPos == pair.second) {
                        nextPos = pair.first;
                        break;
                    }
                }
            }
            
            nextDirection = getNewDirection(cellType, currentDirection, cellOrientation, nextPos);
            
            if (objectsPlaced < minObjects) {
                std::vector<Pos> openPositionsInDirection = findOpenPositions(nextPos, nextDirection);
                if (!openPositionsInDirection.empty()) {
                    int randomIndex = getRandomInt(0, openPositionsInDirection.size() - 1);
                    Pos selectedPos = openPositionsInDirection[randomIndex];

                    // check if there are any other objects in the direction of the ball
                    // if so, do not place this new object.
                    if (!isPotentialNewObjectValid(nextPos, selectedPos, nextDirection)) {
                        currentPos = nextPos;
                        currentDirection = nextDirection;
                        std::cout << "Skipping object placement due to obstacle" << std::endl;
                        continue;
                    }
    
                    GridCellType randomType = objectTypes[getRandomInt(0, objectTypes.size() - 1)];
                    Orientation randomOrientation = getViableOrientation(randomType);
                    
                    if (randomType == GridCellType::Teleporter) {
                        int newIndex = getNextAvailableTeleporterIndex();  // Get random unused index
                        
                        // Place first teleporter
                        gridCells[selectedPos.first][selectedPos.second].type = GridCellType::Teleporter;
                        gridCells[selectedPos.first][selectedPos.second].teleporterIndex = newIndex;
                        removePosition(selectedPos);
                        
                        std::vector<Pos> remainingPositions(openPositions.begin(), openPositions.end());
                        if (!remainingPositions.empty()) {
                            int partnerIndex = getRandomInt(0, remainingPositions.size() - 1);
                            Pos partnerPos = remainingPositions[partnerIndex];
                            
                            // Place partner teleporter with same index
                            gridCells[partnerPos.first][partnerPos.second].type = GridCellType::Teleporter;
                            gridCells[partnerPos.first][partnerPos.second].teleporterIndex = newIndex;
                            removePosition(partnerPos);
                            
                            teleporterPairs.push_back({selectedPos, partnerPos, newIndex});
                            objectsPlaced += 2;
                            std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << selectedPos.first << "," << selectedPos.second << ")" << std::endl;
                            std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << partnerPos.first << "," << partnerPos.second << ")" << std::endl;
                        }
                        else {
                            std::cout << "No remaining positions for teleporter pair" << std::endl;
                            // regenerate grid
                            generateGrid(objectTypes, attempt + 1);
                        }
                    } else {
                        gridCells[selectedPos.first][selectedPos.second].type = randomType;
                        gridCells[selectedPos.first][selectedPos.second].orientation = randomOrientation;
                        removePosition(selectedPos);
                        objectsPlaced++;
                        std::cout << "* Placed object " << GridCellTypeToString(randomType) << "at (" << selectedPos.first << "," << selectedPos.second << ")" << std::endl;
                    }
                }
            }
        }
        
        currentPos = nextPos;
        currentDirection = nextDirection;
    }
    // check if grid is valid
    if (objectsPlaced < minObjects) {
        std::cout << "Grid is invalid, not enough objects, regenerating" << std::endl;
        generateGrid(objectTypes, attempt + 1);
    }
    // std::cout << "Grid generation complete" << std::endl;
}
