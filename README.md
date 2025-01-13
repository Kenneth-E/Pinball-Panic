# Pinball-Panic

// TODO: add author

C++ and Swift implementation of Pinball Panic game

## Requirements

- Xcode 15.0+
- Swift 5.9+
- CMake 3.26+
- C++ 20+

## Build

```
cmake -Bbuild -H.
cmake --build build
```

## Run

```
swift run
```

## Notes

- The grid is generated in the C++ code and passed to Swift
- The grid is displayed in the SwiftUI view
- The grid is generated again when the "Generate New Grid" button is pressed

## TODO

Gameplay:
- add timer
- implemment answer submission + scoring

Mobile navigation:
- rules page
- credits page
- game over screen
- pause menu

# BUGS

