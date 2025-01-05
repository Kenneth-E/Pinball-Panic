#include "Bumper.h"
#include <iostream>

// Constructor
Bumper::Bumper(const std::string& name, Orientation orientation)
    : name(name), orientation(orientation), directionMap(DirectionGenerator::generateDirections(orientation)) {}

// Get the name of the bumper
std::string Bumper::getName() const {
    return name;
}

// Get the orientation of the bumper
Orientation Bumper::getOrientation() const {
    return orientation;
}

// Get the direction map
DirectionMap Bumper::getDirectionMap() const {
    return directionMap;
}

// Print the direction map
void Bumper::printDirectionMap() const {
    for (const auto& pair : directionMap) {
        std::cout << static_cast<int>(pair.first) << " -> " 
                  << static_cast<int>(pair.second) << "\n";
    }
}