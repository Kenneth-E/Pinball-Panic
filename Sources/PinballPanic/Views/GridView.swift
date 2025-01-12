import SwiftUI

struct GridView: View {
    private let gridSize: Int = 10  // Can be changed
    @State private var grid: [[CellType]]
    private let gridBridge: GridBridge
    
    init(size: Int = 10, 
         minObjects: Int = 10, 
         maxObjects: Int = 13,
         objectTypes: [GridCellType] = [.bumper, .tunnel, .teleporter, .directionalBumper]) {
        
        self.grid = Array(repeating: Array(repeating: .empty, count: size), count: size)
        self.gridBridge = GridBridge(size: Int32(size), 
                                   minObjects: Int32(minObjects), 
                                   maxObjects: Int32(maxObjects),
                                   objectTypes: objectTypes)
    }
    
    enum CellType {
        case empty, entry, exit, bumper(GridOrientation), tunnel(GridOrientation), 
             teleporter, directionalBumper(GridOrientation), activatedBumper(GridOrientation)
        
        init(from gridCellType: GridCellType, orientation: GridOrientation) {
            switch gridCellType {
            case .empty: self = .empty
            case .entry: self = .entry
            case .exit: self = .exit
            case .bumper: self = .bumper(orientation)
            case .tunnel: self = .tunnel(orientation)
            case .teleporter: self = .teleporter
            case .directionalBumper: self = .directionalBumper(orientation)
            case .activatedBumper: self = .activatedBumper(orientation)
            case .inBallPath: self = .empty
            }
        }
        
        var symbol: String {
            switch self {
            case .empty: return " "
            case .entry: return "E"
            case .exit: return "X"
            case .bumper(let o): return o == .upRight ? "╱" : "╲"
            case .tunnel(let o): return o == .horizontal ? "=" : "││"
            case .teleporter: return "*"
            case .directionalBumper(let o): 
                switch o {
                case .topRight: return "◹"
                case .topLeft: return "◸"
                case .bottomRight: return "◿"
                case .bottomLeft: return "◺"
                default: return "D"
                }
            case .activatedBumper(let o): return o == .upRight ? "⧄" : "⧅"
            }
        }
        
        var color: Color {
            switch self {
            case .empty: return .gray
            case .entry: return .green
            case .exit: return .red
            case .bumper: return .blue
            case .tunnel: return .purple
            case .teleporter: return .orange
            case .directionalBumper: return .yellow
            case .activatedBumper: return .pink
            }
        }
    }
    
    var body: some View {
        VStack(spacing: 20) {
            Text("Pinball Panic")
                .font(.title)
            
            gridView
                .frame(width: 300, height: 300)
                .border(Color.black, width: 2)
            
            Button("Generate New Grid") {
                regenerateGrid()
            }
            .padding()
        }
        .padding(20)
        .onAppear {
            regenerateGrid()
        }
    }
    
    private var gridView: some View {
        VStack(spacing: 1) {
            ForEach(0..<gridSize, id: \.self) { row in
                HStack(spacing: 1) {
                    ForEach(0..<gridSize, id: \.self) { col in
                        CellView(type: grid[row][col])
                    }
                }
            }
        }
    }
    
    struct CellView: View {
        let type: CellType
        
        var body: some View {
            Text(type.symbol)
                .frame(width: 25, height: 25)
                .background(type.color.opacity(0.3))
                .border(Color.black, width: 1)
                .font(.system(size: 18))
        }
    }
    
    private func regenerateGrid() {
        // Reset the grid state
        grid = Array(repeating: Array(repeating: .empty, count: gridSize), count: gridSize)
        
        // Generate new grid
        gridBridge.generateGrid()
        
        // Update grid data
        for row in 0..<gridSize {
            for col in 0..<gridSize {
                let type = gridBridge.getCellType(row: Int32(row), col: Int32(col))
                let orientation = gridBridge.getCellOrientation(row: Int32(row), col: Int32(col))
                grid[row][col] = CellType(from: type, orientation: orientation)
                print("Cell [\(row),\(col)]: \(grid[row][col])")  // Debug print
            }
            print("")  // New line after each row
        }
    }
} 