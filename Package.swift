// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "PinballPanic",
    platforms: [.macOS(.v13)],
    products: [
        .executable(name: "PinballPanic", targets: ["PinballPanic"]),
    ],
    targets: [
        .executableTarget(
            name: "PinballPanic",
            dependencies: ["GridBridge"]
        ),
        .target(
            name: "GridBridge",
            cxxSettings: [
                .headerSearchPath(".")
            ]
        )
    ],
    cxxLanguageStandard: .cxx17
) 