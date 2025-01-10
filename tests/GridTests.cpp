#define CATCH_CONFIG_MAIN
#include <vector>
#include <utility>
#include <set>
#include "catch.hpp"
#include "../Sources/GridBridge/GridCell.h"
#include "../Sources/GridBridge/DirectionMaps.h"
#include "../Sources/GridBridge/Grid.h"

TEST_CASE("Grid initialization", "[grid]") {
    std::vector<GridCellType> objectTypes = {
        GridCellType::Bumper,
        GridCellType::Tunnel
    };
    Grid grid(5, 2, 3, objectTypes);
    // NOTE: seems like a useless test
    REQUIRE(grid.gridSize == 5);
    REQUIRE(grid.minObjects == 2);
    REQUIRE(grid.maxObjects == 3);
}

TEST_CASE("Entry position is valid", "[grid]") {
    std::vector<GridCellType> objectTypes = {GridCellType::Bumper};
    Grid grid(5, 2, 3, objectTypes);
    
    Pos entryPos = grid.getEntryPosition();
    bool isValidEntry = 
        (entryPos.first == 0 || entryPos.first == 4 || 
         entryPos.second == 0 || entryPos.second == 4);
    
    REQUIRE(isValidEntry);
}

TEST_CASE("Orientation assignment is valid", "[grid]") {
    std::vector<GridCellType> objectTypes = {GridCellType::Bumper};
    Grid grid(5, 2, 3, objectTypes);
    
    SECTION("Bumper orientations") {
        auto orientation = grid.getViableOrientation(GridCellType::Bumper);
        REQUIRE((orientation == Orientation::UpRight || 
                orientation == Orientation::DownRight));
    }
    
    SECTION("Tunnel orientations") {
        auto orientation = grid.getViableOrientation(GridCellType::Tunnel);
        REQUIRE((orientation == Orientation::Horizontal || 
                orientation == Orientation::Vertical));
    }

    SECTION("Activated bumper orientations") {
        auto orientation = grid.getViableOrientation(GridCellType::ActivatedBumper);
        REQUIRE((orientation == Orientation::UpRight || 
                orientation == Orientation::DownRight));
    }

    SECTION("Directional bumper orientations") {
        auto orientation = grid.getViableOrientation(GridCellType::DirectionalBumper);
        REQUIRE((orientation == Orientation::TopLeft || 
                orientation == Orientation::TopRight || 
                orientation == Orientation::BottomLeft || 
                orientation == Orientation::BottomRight));
    }

    SECTION("Teleporter orientations") {
        auto orientation = grid.getViableOrientation(GridCellType::Teleporter);
        REQUIRE(orientation == Orientation::None);
    }
}; 