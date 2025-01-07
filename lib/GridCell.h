#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <string>
#include <stdexcept>
#include <utility> // for std::pair

// Represents the position of the cell in the grid
using Pos = std::pair<int, int>;

// Represents the direction map for a cell in the grid
using DirectionMap = std::unordered_map<Direction, Direction>;

// Enum for Direction
enum class Direction {
    Up,
    Down,
    Left,
    Right,
    None
};

// Enum for Orientation
enum class Orientation {
    DownRight,
    UpRight,
    Vertical,
    Horizontal,
    TopRight,
    TopLeft,
    BottomRight,
    BottomLeft,
    None
};

// Enum for GridCellType
enum class GridCellType {
    Entry,
    Exit,
    Empty,
    InBallPath,
    Bumper,
    Tunnel,
    Teleporter,
    ActivatedBumper,
    DirectionalBumper
};

// Class representing a single cell in the grid
class GridCell {
protected:
    Pos position;
    Orientation orientation;

public:
    GridCell(const Pos& pos, Orientation orient = Orientation::None)
        : position(pos), orientation(orient) {}

    virtual ~GridCell() = default;

    virtual DirectionMap getDirectionMap() const = 0; // Pure virtual function
    virtual std::string getType() const = 0;         // Return type as string for ASCII representation

    void setPosition(const Pos& pos) { position = pos; }
    void setOrientation(Orientation orient) { orientation = orient; }

    Pos getPosition() const { return position; }
    Orientation getOrientation() const { return orientation; }
};

#endif // GRID_CELL_H
