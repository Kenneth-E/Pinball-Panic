#ifndef DIRECTION_MAPS_H
#define DIRECTION_MAPS_H

#include <unordered_map>
#include "GridCell.h"

namespace DirectionMaps {
    static const std::unordered_map<GridCellType, 
        std::unordered_map<Orientation, 
        std::unordered_map<Direction, Direction>>> directionMaps = {
            {GridCellType::Bumper, {
                {Orientation::UpRight, {{Direction::Up, Direction::Right}, {Direction::Right, Direction::Up}, {Direction::Left, Direction::Down}, {Direction::Down, Direction::Left}}},
                {Orientation::DownRight, {{Direction::Down, Direction::Right}, {Direction::Right, Direction::Down}, {Direction::Left, Direction::Up}, {Direction::Up, Direction::Left}}}
            }},
            {GridCellType::ActivatedBumper, {
                {Orientation::UpRight, {{Direction::Up, Direction::Right}, {Direction::Right, Direction::Up}, {Direction::Left, Direction::Down}, {Direction::Down, Direction::Left}}},
                {Orientation::DownRight, {{Direction::Down, Direction::Right}, {Direction::Right, Direction::Down}, {Direction::Left, Direction::Up}, {Direction::Up, Direction::Left}}}
            }},
            {GridCellType::DirectionalBumper, {
                {Orientation::TopLeft, {{Direction::Up, Direction::Right}, {Direction::Down, Direction::Down}, {Direction::Left, Direction::Down}, {Direction::Right, Direction::Right}}},
                {Orientation::TopRight, {{Direction::Up, Direction::Left}, {Direction::Right, Direction::Down}, {Direction::Left, Direction::Left}, {Direction::Down, Direction::Down}}},
                {Orientation::BottomLeft, {{Direction::Down, Direction::Right}, {Direction::Left, Direction::Up}, {Direction::Up, Direction::Up}, {Direction::Right, Direction::Right}}},
                {Orientation::BottomRight, {{Direction::Down, Direction::Left}, {Direction::Right, Direction::Up}, {Direction::Left, Direction::Left}, {Direction::Up, Direction::Up}}}
            }},
            {GridCellType::Tunnel, {
                {Orientation::Horizontal, {{Direction::Up, Direction::Down}, {Direction::Down, Direction::Up}, {Direction::Left, Direction::Left}, {Direction::Right, Direction::Right}}},
                {Orientation::Vertical, {{Direction::Left, Direction::Right}, {Direction::Right, Direction::Left}, {Direction::Up, Direction::Up}, {Direction::Down, Direction::Down}}}
            }},
            {GridCellType::Teleporter, {
                {Orientation::None, {{Direction::Up, Direction::Up}, {Direction::Down, Direction::Down}, {Direction::Left, Direction::Left}, {Direction::Right, Direction::Right}}}
            }}
    };
}

#endif // DIRECTION_MAPS_H 