#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <string>
#include <stdexcept>
#include <utility> // for std::pair

// Represents the position of the cell in the grid
using Pos = std::pair<int, int>;

// Enum for Direction
enum class Direction {
    Up,
    Down,
    Left,
    Right
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
    DirectionalBumper,
    BumperLevelMarker,
    TunnelLevelMarker,
    ActivatedBumperLevelMarker,
    TeleporterLevelMarker,
    DirectionalBumperLevelMarker
};

// Base class for GridCellType with virtual functions for specific cell behavior
class GridCellTypeBase {
public:
    virtual ~GridCellTypeBase() = default;
    virtual std::string toString() const = 0;
};

// Derived classes for specific GridCell types
class Entry : public GridCellTypeBase {
    Direction direction;
public:
    explicit Entry(Direction dir) : direction(dir) {}
    std::string toString() const override { return "Entry"; }
};

class Exit : public GridCellTypeBase {
    Direction direction;
public:
    explicit Exit(Direction dir) : direction(dir) {}
    std::string toString() const override { return "Exit"; }
};

// Add other derived classes (Bumper, Tunnel, Teleporter, etc.) similarly...

// Class representing a single cell in the grid
class GridCell {
    Pos position;
    GridCellType type;
    GridCellTypeBase* typeDetails;

public:
    // Constructor
    GridCell(Pos pos, GridCellType type, GridCellTypeBase* details = nullptr)
        : position(std::move(pos)), type(type), typeDetails(details) {}

    // Destructor
    ~GridCell() { delete typeDetails; }

    // Getters
    Pos getPosition() const { return position; }
    GridCellType getType() const { return type; }
    std::string toString() const;

    // Utility methods
    bool isActivatedBumper() const;
    bool isTeleporterMarker() const;
};

#endif // GRID_CELL_H
