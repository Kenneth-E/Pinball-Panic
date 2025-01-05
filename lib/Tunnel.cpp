#include "Tunnel.h"
#include <iostream>

// Constructor
Tunnel::Tunnel(const std::string& name, Orientation orientation)
    : name(name), orientation(orientation), directionMap(DirectionGenerator::generateDirections(orientation)) {}

// Get the name of the bumper
std::string Tunnel::getName() const {
    return name;
}

// Get the orientation of the bumper
Orientation Tunnel::getOrientation() const {
    return orientation;
}

// Get the direction map
DirectionMap Tunnel::getDirectionMap() const {
    return directionMap;
}

// Print the direction map
void Tunnel::printDirectionMap() const {
    for (const auto& pair : directionMap) {
        std::cout << static_cast<int>(pair.first) << " -> " 
                  << static_cast<int>(pair.second) << "\n";
    }
}