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
            publicHeadersPath: "include",
            cxxSettings: [
                .headerSearchPath("."),
                .headerSearchPath("include")
            ]
        ),
        .executableTarget(
            name: "GridTests",
            dependencies: ["GridBridge"],
            path: "Tests",
            cxxSettings: [
                .headerSearchPath("../Sources/GridBridge"),
                .headerSearchPath(".")
            ]
        )
    ],
    cxxLanguageStandard: .cxx17
) 