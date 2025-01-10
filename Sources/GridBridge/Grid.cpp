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

// Check if a position is within the grid bounds
bool Grid::isWithinBounds(const Pos& pos) const {
    return (pos.first >= 0 && pos.first < gridSize) && (pos.second >= 0 && pos.second < gridSize);
}

// Find open positions along the ball's path
std::vector<Pos> Grid::findOpenPositions(const Pos& currentPos, Direction currentDirection, const std::set<Pos>& occupied) const{
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
Pos Grid::getNextPosition(const Pos& currentPos, Direction direction) const{
    Pos nextPos = currentPos;
    switch (direction) {
        case Direction::Up:    nextPos = {currentPos.first - 1, currentPos.second}; break;
        case Direction::Down:  nextPos = {currentPos.first + 1, currentPos.second}; break;
        case Direction::Left:  nextPos = {currentPos.first, currentPos.second - 1}; break;
        case Direction::Right: nextPos = {currentPos.first, currentPos.second + 1}; break;
        default:              return currentPos;
    }
    
    // Add bounds check
    if (!isWithinBounds(nextPos)) {
        return currentPos;
    }
    return nextPos;
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

// Generate the grid dynamically
void Grid::generateGrid(std::vector<GridCellType>& objectTypes, int attempt) {
    std::cout << "Grid::generateGrid - Starting (simplified)..." << std::endl;
    std::cout.flush();

    // Just create an empty grid with one entry point
    initializeGrid();
    
    // Place entry at (0,0)
    gridCells[0][0].type = GridCellType::Entry;
    
    // Place exit at (4,4)
    gridCells[4][4].type = GridCellType::Exit;
    
    std::cout << "Grid::generateGrid - Completed simplified version" << std::endl;
    std::cout.flush();
}

// Check if a position is out of the center region of the grid
bool Grid::isOutOfCenter(const Pos& pos) const {
    // Define the center region as the middle 60% of the grid
    int borderSize = gridSize * 0.2; // 20% border on each side
    
    // Check if position is in the border area
    return pos.first < borderSize || 
           pos.first >= gridSize - borderSize ||
           pos.second < borderSize || 
           pos.second >= gridSize - borderSize;
}
