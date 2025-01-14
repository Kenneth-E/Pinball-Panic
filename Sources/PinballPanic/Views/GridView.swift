import SwiftUI

struct GridView: View {
    private let gridSize: Int = 10  // Can be changed
    @State private var grid: [[CellType]]
    private let gridBridge: GridBridge
    @State private var targetPosition: Pos?  // Track the user's selected position
    @State private var exitPosition: Pos?  // Track the exit position
    @State private var remainingTime: Int = 30  // Set the initial countdown time (in seconds)
    @State private var isGameOver: Bool = false  // Track game over state
    @State private var correctAnswers: Int = 0  // Track the number of correct answers
    @State private var currentLevelIndex: Int = 0  // Track the current level
    
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
             teleporter(Int),
             directionalBumper(GridOrientation), activatedBumper(GridOrientation)
        
        init(from gridCellType: GridCellType, orientation: GridOrientation, teleporterIndex: Int = 0) {
            switch gridCellType {
            case .empty: self = .empty
            case .entry: self = .entry
            case .exit: self = .exit
            case .bumper: self = .bumper(orientation)
            case .tunnel: self = .tunnel(orientation)
            case .teleporter: self = .teleporter(teleporterIndex)
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
            case .teleporter(let index): 
                let symbols = ["①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨"]
                return index < symbols.count ? symbols[index] : "*"
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
            Text("Time Remaining: \(remainingTime) seconds")
                .font(.headline)
            
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
            startTimer()
        }
        
        if isGameOver {
            GameOverView(correctAnswers: correctAnswers, isGameOver: $isGameOver, currentLevelIndex: $currentLevelIndex)
        }
    }
    
    private var gridView: some View {
        VStack(spacing: 1) {
            ForEach(0..<gridSize, id: \.self) { row in
                HStack(spacing: 1) {
                    ForEach(0..<gridSize, id: \.self) { col in
                        CellView(type: grid[row][col])
                            .onTapGesture {
                                targetPosition = (Int32(row), Int32(col))  // Set the target position
                                checkAnswer(targetPosition: targetPosition!)  // Call the function to highlight the path
                            }
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
        grid = Array(repeating: Array(repeating: .empty, count: gridSize), count: gridSize)
        
        gridBridge.generateGrid()
        
        for row in 0..<gridSize {
            for col in 0..<gridSize {
                let type = gridBridge.getCellType(row: Int32(row), col: Int32(col))
                let orientation = gridBridge.getCellOrientation(row: Int32(row), col: Int32(col))
                let teleporterIndex = type == .teleporter ? gridBridge.getTeleporterIndex(row: Int32(row), col: Int32(col)) : 0
                grid[row][col] = CellType(from: type, orientation: orientation, teleporterIndex: teleporterIndex)
                if type == .exit {
                    exitPosition = (Int32(row), Int32(col))
                }
            }
        }
    }

    private func checkAnswer(targetPosition: Pos) {
        // Check if the answer is correct
        if targetPosition == exitPosition! {
            print("Correct!")
            // Reset the timer for the next round
            correctAnswers += 1
            remainingTime += 5  // Add 5 seconds to the timer for correct answers
            regenerateGrid()  // Regenerate the grid
        } else {
            print("Incorrect!")
            // Handle incorrect answer logic (e.g., stop the game, show a message)
            isGameOver = true
        }
    }

    private func startTimer() {
        Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) { timer in
            if remainingTime > 0 {
                remainingTime -= 1
            } else {
                timer.invalidate()  // Stop the timer when it reaches zero
                print("Time's up!")
                isGameOver = true  // Set game over state
            }
        }
    }
} 
