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

std::string GridCellTypeToString(GridCellType type) {
    switch (type) {
        case GridCellType::Empty: return "Empty";
        case GridCellType::InBallPath: return "InBallPath";
        case GridCellType::Teleporter: return "Teleporter";
        case GridCellType::Bumper: return "Bumper";
        case GridCellType::Tunnel: return "Tunnel";
        case GridCellType::ActivatedBumper: return "ActivatedBumper";
        case GridCellType::DirectionalBumper: return "DirectionalBumper";
        default: throw std::invalid_argument("Unknown grid cell type");
    }
}