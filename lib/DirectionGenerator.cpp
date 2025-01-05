#include "DirectionGenerator.h"
#include <stdexcept>

// Converts Orientation to string
std::string orientationToString(Orientation orientation) {
    switch (orientation) {
        case Orientation::DownRight:
            return "DownRight";
        case Orientation::UpRight:
            return "UpRight";
        case Orientation::Horizontal:
            return "Horizontal";
        case Orientation::Vertical:
            return "Vertical";
        default:
            throw std::invalid_argument("Unknown orientation");
    }
}

// Generates a DirectionMap based on the given orientation
DirectionMap DirectionGenerator::generateDirections(Orientation orientation) {
    if (orientation == Orientation::DownRight) {
        return {
            {Direction::Right, Direction::Down},
            {Direction::Up, Direction::Left},
            {Direction::Left, Direction::Up},
            {Direction::Down, Direction::Right}
        };
    } else if (orientation == Orientation::UpRight) {
        return {
            {Direction::Right, Direction::Up},
            {Direction::Down, Direction::Left},
            {Direction::Left, Direction::Down},
            {Direction::Up, Direction::Right}
        };
    } else if (orientation == Orientation::Horizontal) {
        return {
            {Direction::Right, Direction::Right},
            {Direction::Up, Direction::Down},
            {Direction::Left, Direction::Left},
            {Direction::Down, Direction::Up}
        };
    } else if (orientation == Orientation::Vertical) {
        return {
            {Direction::Right, Direction::Left},
            {Direction::Down, Direction::Down},
            {Direction::Left, Direction::Right},
            {Direction::Up, Direction::Up}
        };
    } else {
        throw std::invalid_argument("Invalid orientation");
    }
}