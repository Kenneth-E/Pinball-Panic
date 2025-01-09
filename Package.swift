// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "PinballPanic",
    platforms: [.macOS(.v13)],
    targets: [
        .executableTarget(
            name: "PinballPanic",
            path: "Sources/PinballPanic",
            linkerSettings: [
                .linkedLibrary("GridBridge"),
                .unsafeFlags(["-L", "./build", "-Xlinker", "-rpath", "-Xlinker", "@executable_path/../build"])
            ]
        )
    ]
) 