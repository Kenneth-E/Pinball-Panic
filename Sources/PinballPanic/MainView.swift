import SwiftUI


@available(iOS 16.0, *)
struct MainView: View {
    @State private var isGameActive: Bool = false
    @State private var currentLevelIndex: Int = 0  // Track the current level

    var body: some View {
        ZStack {
            // Background or main menu content
            VStack {
                Text("Pinball Panic")
                    .font(.largeTitle)
                    .padding()

                Button("Start Game") {
                    isGameActive = true  // Start the game
                }
                .padding()
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(10)
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(Color(white: 1))

            // GameView displayed on top
            if isGameActive {
                GridView()
                    .transition(.move(edge: .bottom))  // Optional transition effect
            }
        }
    }
}

// Entry point for the application
@available(iOS 16.0, *)
@main
struct PinballPanicApp: App {
    var body: some Scene {
        WindowGroup {
            MainView()  // Start with MainView
        }
    }
} 
