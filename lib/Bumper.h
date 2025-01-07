#ifndef BUMPER_H
#define BUMPER_H

#include "GridCell.h"

class Bumper : public GridCell {
public:
    Bumper(const Pos& pos, Orientation orient = Orientation::None)
        : GridCell(pos, orient) {}

    DirectionMap getDirectionMap() const override {
        return {
            {Direction::Up, Direction::Right},
            {Direction::Down, Direction::Left},
            {Direction::Left, Direction::Down},
            {Direction::Right, Direction::Up}
        };
    }

    std::string getType() const override {
        return "B";
    }
};

#endif // BUMPER_H
