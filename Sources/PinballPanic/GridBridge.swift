import Foundation

typealias Pos = (Int32, Int32)

enum GridCellType: Int {
    case empty = 0
    case entry = 1
    case exit = 2
    case inBallPath = 3
    case bumper = 4
    case tunnel = 5
    case teleporter = 6
    case activatedBumper = 7
    case directionalBumper = 8
}

enum GridOrientation: Int {
    case downRight = 0
    case upRight = 1
    case vertical = 2
    case horizontal = 3
    case topRight = 4
    case topLeft = 5
    case bottomRight = 6
    case bottomLeft = 7
    case none = 8
}

class GridBridge {
    private var grid: OpaquePointer
    
    init(size: Int32 = 10, 
         minObjects: Int32 = 4, 
         maxObjects: Int32 = 6,
         objectTypes: [GridCellType] = [.bumper, .tunnel, .teleporter, .directionalBumper]) {
        
        // Convert Swift array to vector
        let objectTypesVector = objectTypes.map { Int32($0.rawValue) }
        grid = Grid_Create(size, minObjects, maxObjects, objectTypesVector, Int32(objectTypesVector.count))
    }
    
    deinit {
        print("Swift: Destroying GridBridge...")
        Grid_Destroy(grid)
    }
    
    func generateGrid() {
        print("Swift: Calling generateGrid...")
        Grid_GenerateGrid(grid)
        print("Swift: generateGrid call complete")
    }
    
    func getCellType(row: Int32, col: Int32) -> GridCellType {
        let rawValue = Grid_GetCellType(grid, row, col)
        return GridCellType(rawValue: Int(rawValue)) ?? .empty
    }
    
    func getCellOrientation(row: Int32, col: Int32) -> GridOrientation {
        let rawValue = Grid_GetCellOrientation(grid, row, col)
        return GridOrientation(rawValue: Int(rawValue)) ?? .none
    }
}

private let gridBridgeLib = "libGridBridge.dylib"

@_silgen_name("create_grid")
private func create_grid(_ size: Int32, _ min_objects: Int32, _ max_objects: Int32) -> OpaquePointer?

@_silgen_name("destroy_grid")
private func destroy_grid(_ handle: OpaquePointer)

@_silgen_name("generate_grid")
private func generate_grid(_ handle: OpaquePointer)

@_silgen_name("get_cell_type")
private func get_cell_type(_ handle: OpaquePointer, _ row: Int32, _ col: Int32) -> Int32

@_silgen_name("get_cell_orientation")
private func get_cell_orientation(_ handle: OpaquePointer, _ row: Int32, _ col: Int32) -> Int32

@_silgen_name("test_bridge")
private func test_bridge() -> Bool 

@_silgen_name("Grid_Destroy")
private func Grid_Destroy(_ grid: OpaquePointer) 

@_silgen_name("Grid_Create")
private func Grid_Create(_ size: Int32, _ minObjects: Int32, _ maxObjects: Int32, 
                        _ objectTypes: [Int32], _ objectTypesCount: Int32) -> OpaquePointer 

@_silgen_name("Grid_GenerateGrid")
private func Grid_GenerateGrid(_ grid: OpaquePointer) 

@_silgen_name("Grid_GetCellType")
private func Grid_GetCellType(_ grid: OpaquePointer, _ row: Int32, _ col: Int32) -> Int32

@_silgen_name("Grid_GetCellOrientation")
private func Grid_GetCellOrientation(_ grid: OpaquePointer, _ row: Int32, _ col: Int32) -> Int32 