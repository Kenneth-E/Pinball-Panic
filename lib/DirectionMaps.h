#ifndef DIRECTION_MAPS_H
#define DIRECTION_MAPS_H

#include <unordered_map>
#include "GridCell.h"

namespace DirectionMaps {
    static const std::unordered_map<GridCellType, 
        std::unordered_map<Orientation, 
        std::unordered_map<Direction, Direction>>> directionMaps = {
            {GridCellType::Bumper, {
                {Orientation::UpRight, {{Direction::Up, Direction::Right}, {Direction::Right, Direction::Down}}},
                {Orientation::DownRight, {{Direction::Down, Direction::Right}, {Direction::Right, Direction::Up}}}
            }},
            {GridCellType::ActivatedBumper, {
                {Orientation::UpRight, {{Direction::Up, Direction::Right}, {Direction::Right, Direction::Down}}},
                {Orientation::DownRight, {{Direction::Down, Direction::Right}, {Direction::Right, Direction::Up}}}
            }},
            {GridCellType::DirectionalBumper, {
                {Orientation::TopLeft, {{Direction::Up, Direction::Left}, {Direction::Left, Direction::Up}}},
                {Orientation::TopRight, {{Direction::Up, Direction::Right}, {Direction::Right, Direction::Up}}},
                {Orientation::BottomLeft, {{Direction::Down, Direction::Left}, {Direction::Left, Direction::Down}}},
                {Orientation::BottomRight, {{Direction::Down, Direction::Right}, {Direction::Right, Direction::Down}}}
            }},
            {GridCellType::Tunnel, {
                {Orientation::Horizontal, {{Direction::Up, Direction::Right}, {Direction::Down, Direction::Left}}},
                {Orientation::Vertical, {{Direction::Left, Direction::Down}, {Direction::Right, Direction::Up}}}
            }},
            {GridCellType::Teleporter, {
                {Orientation::None, {{Direction::Up, Direction::Up}, {Direction::Down, Direction::Down}, {Direction::Left, Direction::Left}, {Direction::Right, Direction::Right}}}
            }}
    };
}

#endif // DIRECTION_MAPS_H 