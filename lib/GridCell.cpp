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

// Converts the GridCell to a string representation
std::string GridCell::toString() const {
    return typeDetails ? typeDetails->toString() : "Unknown";
}

// Checks if the cell is an activated bumper
bool GridCell::isActivatedBumper() const {
    return type == GridCellType::ActivatedBumper;
}

// Checks if the cell is a teleporter marker
bool GridCell::isTeleporterMarker() const {
    return type == GridCellType::TeleporterLevelMarker;
}
