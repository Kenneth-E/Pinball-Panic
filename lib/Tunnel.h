#ifndef TUNNEL_H
#define TUNNEL_H

#include "GridCell.h"

class Tunnel : public GridCell {
public:
    Tunnel(const Pos& pos, Orientation orient = Orientation::None)
        : GridCell(pos, orient) {}

    DirectionMap getDirectionMap() const override {
        return {
            {Direction::Up, Direction::Down},
            {Direction::Down, Direction::Up},
            {Direction::Left, Direction::Right},
            {Direction::Right, Direction::Left}
        };
    }

    std::string getType() const override {
        return "T";
    }
};

#endif // TUNNEL_H
