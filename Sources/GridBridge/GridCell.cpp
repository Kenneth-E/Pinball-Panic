#include "GridCell.h"

// Converts Orientation to a string
std::string orientationToString(Orientation orientation) {
    switch (orientation) {
        case Orientation::DownRight: return "DownRight";
        case Orientation::UpRight: return "UpRight";
        case Orientation::Vertical: return "Vertical";
        case Orientation::Horizontal: return "Horizontal";
        case Orientation::TopRight: return "TopRight";
        case Orientation::TopLeft: return "TopLeft";
        case Orientation::BottomRight: return "BottomRight";
        case Orientation::BottomLeft: return "BottomLeft";
        case Orientation::None: return "None";
        default: throw std::invalid_argument("Unknown orientation");
    }
}