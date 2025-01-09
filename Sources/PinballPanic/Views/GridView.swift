import SwiftUI

struct GridView: View {
    @State private var grid: [[CellType]] = Array(repeating: Array(repeating: .empty, count: 10), count: 10)
    private let gridBridge = GridBridge(size: 10, minObjects: 5, maxObjects: 10)
    
    enum CellType {
        case empty, entry, exit, bumper, tunnel, teleporter, directionalBumper, activatedBumper
        
        init(from gridCellType: GridCellType, orientation: GridOrientation) {
            switch gridCellType {
            case .empty: self = .empty
            case .entry: self = .entry
            case .exit: self = .exit
            case .bumper: self = .bumper
            case .tunnel: self = .tunnel
            case .teleporter: self = .teleporter
            case .directionalBumper: self = .directionalBumper
            case .activatedBumper: self = .activatedBumper
            default: self = .empty
            }
        }
        
        var symbol: String {
            switch self {
            case .empty: return "."
            case .entry: return "E"
            case .exit: return "X"
            case .bumper: return "/"
            case .tunnel: return "="
            case .teleporter: return "*"
            case .directionalBumper: return "D"
            case .activatedBumper: return "A"
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
        VStack {
            gridView
            Button("Generate New Grid") {
                generateGrid()
            }
            .padding()
        }
        .onAppear {
            generateGrid()
        }
    }
    
    private var gridView: some View {
        VStack(spacing: 1) {
            ForEach(0..<10, id: \.self) { row in
                HStack(spacing: 1) {
                    ForEach(0..<10, id: \.self) { col in
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
                .frame(width: 30, height: 30)
                .background(type.color.opacity(0.3))
                .border(Color.black, width: 0.5)
        }
    }
    
    private func generateGrid() {
        gridBridge.generateGrid()
        
        // Update Swift grid from C++ grid
        for row in 0..<10 {
            for col in 0..<10 {
                let type = gridBridge.getCellType(row: Int32(row), col: Int32(col))
                let orientation = gridBridge.getCellOrientation(row: Int32(row), col: Int32(col))
                grid[row][col] = CellType(from: type, orientation: orientation)
            }
        }
    }
} 