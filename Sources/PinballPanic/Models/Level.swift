import Foundation

struct Level {
    var gridSize: Int
    var minObjects: Int
    var maxObjects: Int
    var viableObjectTypes: [GridCellType]
}

// Define levels
let levels: [Level] = [
    Level(gridSize: 5, minObjects: 1, maxObjects: 1, viableObjectTypes: [.bumper]),
    Level(gridSize: 5, minObjects: 2, maxObjects: 2, viableObjectTypes: [.bumper]),
    Level(gridSize: 6, minObjects: 3, maxObjects: 4, viableObjectTypes: [.bumper]),
    // tunnel introduced
    Level(gridSize: 6, minObjects: 3, maxObjects: 4, viableObjectTypes: [.bumper, .tunnel]),
    Level(gridSize: 7, minObjects: 4, maxObjects: 6, viableObjectTypes: [.bumper, .tunnel]),
    // teleporter introduced
    Level(gridSize: 10, minObjects: 6, maxObjects: 7, viableObjectTypes: [.bumper, .tunnel, .teleporter]),
    Level(gridSize: 10, minObjects: 7, maxObjects: 8, viableObjectTypes: [.bumper, .tunnel, .teleporter]),
    // activated bumper introduced
    Level(gridSize: 10, minObjects: 7, maxObjects: 9, viableObjectTypes: [.bumper, .tunnel, .teleporter, .activatedBumper]),
    Level(gridSize: 10, minObjects: 8, maxObjects: 10, viableObjectTypes: [.bumper, .tunnel, .teleporter, .activatedBumper]),
    // directional bumper introduced
    Level(gridSize: 10, minObjects: 10, maxObjects: 12, viableObjectTypes: [.bumper, .tunnel, .teleporter, .activatedBumper, .directionalBumper]),
    Level(gridSize: 10, minObjects: 11, maxObjects: 13, viableObjectTypes: [.bumper, .tunnel, .teleporter, .activatedBumper, .directionalBumper]),
] 
