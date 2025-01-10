import SwiftUI

struct GridView: View {
    @State private var grid: [[CellType]] = Array(repeating: Array(repeating: .empty, count: 5), count: 5)
    private let gridBridge: GridBridge
    
    init() {
        print("GridView: Initializing...")
        self.gridBridge = GridBridge(size: 5, minObjects: 2, maxObjects: 3)
        print("GridView: Initialization complete")
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
            default: self = .empty
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
                .border(Color.black, width: 2)
            
            Button("Generate New Grid") {
                generateGrid()
            }
            .padding()
        }
        .padding(20)
        .frame(minWidth: 400, minHeight: 400)
        .onAppear {
            generateGrid()
        }
    }
    
    private var gridView: some View {
        VStack(spacing: 1) {
            ForEach(0..<5, id: \.self) { row in
                HStack(spacing: 1) {
                    ForEach(0..<5, id: \.self) { col in
                        CellView(type: grid[row][col])
                    }
                }
            }
        }
        .padding()
    }
    
    struct CellView: View {
        let type: CellType
        
        var body: some View {
            Text(type.symbol)
                .frame(width: 50, height: 50)
                .background(type.color.opacity(0.3))
                .border(Color.black, width: 1)
                .font(.system(size: 24))
        }
    }
    
    private func generateGrid() {
        print("Generating grid...")  // Debug print
        gridBridge.generateGrid()
        
        print("Updating grid data...")  // Debug print
        for row in 0..<5 {
            for col in 0..<5 {
                let type = gridBridge.getCellType(row: Int32(row), col: Int32(col))
                let orientation = gridBridge.getCellOrientation(row: Int32(row), col: Int32(col))
                grid[row][col] = CellType(from: type, orientation: orientation)
            }
        }
        print("Grid generation complete")  // Debug print
    }
} 