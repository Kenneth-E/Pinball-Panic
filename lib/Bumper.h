#ifndef BUMPER_H
#define BUMPER_H

#include "DirectionGenerator.h"
#include <string>

class Bumper {
private:
    std::string name;
    Orientation orientation;
    DirectionMap directionMap;

public:
    // Constructor
    Bumper(const std::string& name, Orientation orientation);

    // Get the name of the bumper
    std::string getName() const;

    // Get the orientation of the bumper
    Orientation getOrientation() const;

    // Get the direction map
    DirectionMap getDirectionMap() const;

    // Print the direction map
    void printDirectionMap() const;
};

#endif // BUMPER_H