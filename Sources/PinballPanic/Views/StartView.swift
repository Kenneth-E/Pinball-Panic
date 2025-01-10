import SwiftUI

struct StartView: View {
    @State private var navigateToGame = false
    
    var body: some View {
        NavigationStack {
            VStack(spacing: 40) {
                Text("Pinball Panic")
                    .font(.system(size: 48, weight: .bold))
                    .foregroundColor(.blue)
                
                Image(systemName: "poweroutlet.type.f.fill") // Placeholder icon, you can change this
                    .font(.system(size: 100))
                    .foregroundColor(.orange)
                
                NavigationLink(destination: GridView()) {
                    Text("Start Game")
                        .font(.title)
                        .foregroundColor(.white)
                        .padding()
                        .background(Color.blue)
                        .cornerRadius(10)
                }
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .background(Color(white: 0.9))
        }
    }
} 