#ifndef TUNNEL_H
#define TUNNEL_H

#include "DirectionGenerator.h"
#include <string>

class Tunnel {
private:
    std::string name;
    Orientation orientation;
    DirectionMap directionMap;

public:
    // Constructor
    Tunnel(const std::string& name, Orientation orientation);

    // Get the name of the bumper
    std::string getName() const;

    // Get the orientation of the bumper
    Orientation getOrientation() const;

    // Get the direction map
    DirectionMap getDirectionMap() const;

    // Print the direction map
    void printDirectionMap() const;
};

#endif // TUNNEL_H