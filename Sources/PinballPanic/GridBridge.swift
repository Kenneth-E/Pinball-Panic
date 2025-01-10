import Foundation

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
    private var handle: OpaquePointer?
    
    init(size: Int32, minObjects: Int32, maxObjects: Int32) {
        print("Swift: Testing bridge...")
        let testResult = test_bridge()
        print("Swift: Bridge test result: \(testResult)")
        
        print("Swift: Creating GridBridge...")
        handle = create_grid(size, minObjects, maxObjects)
        print("Swift: GridBridge created, handle: \(handle != nil)")
    }
    
    deinit {
        print("Swift: Destroying GridBridge...")
        if let handle = handle {
            destroy_grid(handle)
        }
    }
    
    func generateGrid() {
        print("Swift: Calling generateGrid...")
        guard let handle = handle else {
            print("Swift: Error - handle is nil!")
            return
        }
        generate_grid(handle)
        print("Swift: generateGrid call complete")
    }
    
    func getCellType(row: Int32, col: Int32) -> GridCellType {
        guard let handle = handle else {
            print("Swift: Error - handle is nil in getCellType!")
            return .empty
        }
        let rawValue = get_cell_type(handle, row, col)
        return GridCellType(rawValue: Int(rawValue)) ?? .empty
    }
    
    func getCellOrientation(row: Int32, col: Int32) -> GridOrientation {
        guard let handle = handle else {
            print("Swift: Error - handle is nil in getCellOrientation!")
            return .none
        }
        let rawValue = get_cell_orientation(handle, row, col)
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