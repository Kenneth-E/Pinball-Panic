#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <string>

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
    Empty = 0,
    Entry = 1,
    Exit = 2,
    InBallPath = 3,
    Bumper = 4,
    Tunnel = 5,
    Teleporter = 6,
    ActivatedBumper = 7,
    DirectionalBumper = 8
};

// Simple struct representing a cell in the grid
struct GridCell {
    GridCellType type = GridCellType::Empty;
    Direction direction = Direction::None;
    Orientation orientation = Orientation::None;
};

#endif // GRID_CELL_H
