import SwiftUI

@available(iOS 16.0, *)
struct GameOverView: View {
    var correctAnswers: Int
    @Binding var isGameOver: Bool  // Binding to control navigation
    @Binding var currentLevelIndex: Int  // Binding to track the current level

    var body: some View {
        VStack(spacing: 20) {
            Text("Game Over")
                .font(.largeTitle)
                .fontWeight(.bold)

            Text("You got \(correctAnswers) answers correct!")
                .font(.headline)

            HStack {
                Button("Main Menu") {
                    isGameOver = false  // Navigate back to main menu
                }
                .padding()
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(10)

                Button("Start New Game") {
                    // Logic to start a new game
                    currentLevelIndex = (currentLevelIndex + 1) % levels.count  // Move to the next level
                    isGameOver = false  // Reset game over state
                }
                .padding()
                .background(Color.green)
                .foregroundColor(.white)
                .cornerRadius(10)
            }
        }
        .padding()
    }
} 
