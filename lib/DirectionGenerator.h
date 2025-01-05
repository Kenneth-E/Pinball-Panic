#ifndef DIRECTION_GENERATOR_H
#define DIRECTION_GENERATOR_H

#include <unordered_map>
#include <string>

// Enum for Orientation
enum class Orientation {
    DownRight,
    UpRight,
    Horizontal,
    Vertical
};

// Converts Orientation to a string
std::string orientationToString(Orientation orientation);

// Enum for Direction
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

// Alias for Direction Map
using DirectionMap = std::unordered_map<Direction, Direction>;

// Generic DirectionGenerator class
class DirectionGenerator {
public:
    // Generates a DirectionMap based on the given orientation
    static DirectionMap generateDirections(Orientation orientation);
};

#endif // DIRECTION_GENERATOR_H