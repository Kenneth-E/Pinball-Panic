cmake_minimum_required(VERSION 3.15)
project(PinballPanic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "@executable_path")

# Create the C++ library
add_library(GridBridge SHARED
    lib/Grid.cpp
    lib/GridCell.cpp
    lib/GridBridge.cpp
)

target_include_directories(GridBridge PUBLIC lib)

# Set output name to match what Swift expects
set_target_properties(GridBridge PROPERTIES
    PREFIX "lib"
    OUTPUT_NAME "GridBridge"
    SUFFIX ".dylib"
) 